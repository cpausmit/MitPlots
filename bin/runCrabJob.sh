#!/bin/bash
#---------------------------------------------------------------------------------------------------
# Execute one job (works interactively and when executed in condor)
#---------------------------------------------------------------------------------------------------
  runMacro=$1
catalogDir=$2
      book=$3
   dataset=$4
      skim=$5
   fileset=$6
outputName=$7
 outputDir=$8
 runTypeId=$9
   nEvents=-1
if [ ".${10}" != "." ]
then
  nEvents=${10}
fi

nEvents=1000

h=`basename $0`
echo ""
echo " START runCrabJob.sh"
echo ""
echo " -=o=- -=o=- -=o=- -=o=- -=o=- -=o=- -=o=- -=o=- -=o=- -=o=- -=o=- -=o=- -=o=- -=o=- -=o=-";
echo " -=o=- -=o=- -=o=- -=o=- -=o=- -=o=- -=o=- -=o=- -=o=- -=o=- -=o=- -=o=- -=o=- -=o=- -=o=-";
echo ""

echo "Script:    $h"
echo "Arguments: ($*)"

# some basic printing
echo " ";
echo "${h}: Show who and where we are";
echo " start time    : "`date`
echo " user executing: "`id`;
echo " running on    : "`hostname`;
echo " executing in  : "`pwd`;
echo " submitted from: $HOSTNAME";
echo " ";
here=`pwd`
initialSeconds=`date +"%s"`

# initialize the CMSSW environment
echo " "; echo "${h}: Initialize CMSSW (in $CMSSW_BASE)"; echo " "
source ./setup.sh

# make sure to setup what we need locally if we are not in the original area (when in condor/crab)
workDir=`pwd`
ls -alhrt

echo "  untarring: ${CMSSW_VERSION}-src.tgz"
tar fzx ${CMSSW_VERSION}-src.tgz

echo "  untarring: external.tgz"
cd $CMSSW_BASE/..
tar fzx $workDir/external.tgz
$CMSSW_BASE/src/MitAna/bin/setupExternal.sh
export EXTERNAL=$CMSSW_BASE/../external
cd - >& /dev/null

echo "  untarring: json.tgz"
tar fzx json.tgz

echo "  untarring: catalog.tgz"
tar fzx catalog.tgz

# Copy and unpack the MitPhysics/data
echo "  copy: xrdcp root://xrootd.cmsaf.mit.edu//store/user/paus/MitPhysics_data.tgz $CMSSW_BASE/src/MitPhysics_data.tgz"
xrdcp root://xrootd.cmsaf.mit.edu//store/user/paus/MitPhysics_data.tgz $CMSSW_BASE/src/MitPhysics_data.tgz

cd $CMSSW_BASE/src
echo "  untaring: tar fzx MitPhysics_data.tgz"
time tar fzx MitPhysics_data.tgz
cd - >& /dev/null

export MIT_DATA="$CMSSW_BASE/src/MitPhysics/data"
if ! [ -d "$MIT_DATA" ]
then
  echo "  ERROR - could not find MitPhysics/data. EXIT"
  echo " " 
  exit 1
fi
echo "  found MitPhysics/data at: $MIT_DATA"
ls -lhrt $CMSSW_BASE/src/MitPhysics

# get ready to run
echo " ";
echo "${h}: Starting root job now";
echo " ";
echo "
  root -b -l -q .rootlogon.C \
  ./${runMacro}+\(\"$fileset\",\"$skim\",\"$dataset\",\"$book\",\"$catalogDir\"\,\"$outputName\",$nEvents\)
"

  root -b -l -q .rootlogon.C \
  ./${runMacro}+\(\"$fileset\",\"$skim\",\"$dataset\",\"$book\",\"$catalogDir\"\,\"$outputName\",$nEvents\)

# get the return code from the root job
status=`echo $?`
echo "${h}: Status - $status"

# take care of the output file
output=${outputName}_${dataset}_${skim}_${fileset}.root

echo " -- goto runtime_area: $RUNTIME_AREA"
cd $RUNTIME_AREA
ls -lhrt
echo "
python cmscp.py  --destination srm://${MIT_PROD_SE}:8443${MIT_PROD_SDIR}/${MIT_PROD_RDIR}/ \
                 --inputFileList $here/$output \
                 --middleware OSG \
                 --se_name ${MIT_PROD_SE} \
                 --for_lfn ${MIT_PROD_RDIR}    
"
python cmscp.py  --destination srm://${MIT_PROD_SE}:8443${MIT_PROD_SDIR}/${MIT_PROD_RDIR}/ \
                 --inputFileList $here/$output \
                 --middleware OSG \
                 --se_name ${MIT_PROD_SE} \
                 --for_lfn ${MIT_PROD_RDIR}
statusCopy=$?
echo ""
echo " Status of cmscp: $statusCopy"
echo ""


finalSeconds=`date +"%s"`
let duration=($finalSeconds-$initialSeconds)/60
echo " end time      : "`date`
echo " duration      : $duration min"

echo " -=o=- -=o=- -=o=- -=o=- -=o=- -=o=- -=o=- -=o=- -=o=- -=o=- -=o=- -=o=- -=o=- -=o=- -=o=-";
echo " -=o=- -=o=- -=o=- -=o=- -=o=- -=o=- -=o=- -=o=- -=o=- -=o=- -=o=- -=o=- -=o=- -=o=- -=o=-";
echo ""
echo " END with runCrabJob.sh";
echo ""

exit $status
