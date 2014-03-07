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
   nEvents=1000
if [ ".${10}" != "." ]
then
  nEvents=${10}
fi

h=`basename $0`
echo "Script:    $h"
echo "Arguments: $*"

# some basic printing
echo " ";
echo "${h}: Show who and where we are";
echo " start time    : "`date`
echo " user executing: "`id`;
echo " running on    : "`hostname`;
echo " executing in  : "`pwd`;
echo " submitted from: $HOSTNAME";
echo " ";
env

initialSeconds=`date +"%s"`

# initialize the CMSSW environment
echo " "; echo "${h}: Initialize CMSSW (in $CMSSW_BASE)"; echo " "

# make sure to setup what we need locally if we are not in the original area (when in condor)
workDir=`pwd`
ls -lhrt
if [ "$workDir" != "/home/$USER/cms/root" ]
then
  export VER=`echo CMSSW_*.tgz |cut -d. -f1`
  export SCRAM_ARCH="slc5_amd64_gcc462"
  source /cvmfs/cms.cern.ch/cmsset_default.sh
  scram project CMSSW ${VER}

  echo " untarring: CMSSW_5_3_14_patch2.tgz"
  tar fzx ${VER}.tgz
  echo " setting up environment"
  cd ${VER}/src
  eval `scram runtime -sh`
  cd -

  tar fzx external.tgz
  $CMSSW_BASE/src/MitAna/bin/setupExternal.sh

  # Copy and unpack up the MitPhysics/data
  if ! [ -d "$MIT_DATA" ]
  then
    echo "  copy: cp /mnt/hadoop/cms/store/user/paus/MitPhysics_data.tgz ./"
    cp /mnt/hadoop/cms/store/user/paus/MitPhysics_data.tgz ./
    echo "  untaring: tar fzx MitPhysics_data.tgz"
    time tar fzx MitPhysics_data.tgz
    MIT_DATA=./MitPhysics/data
    if ! [ -d "$MIT_DATA" ]
    then
      echo "  ERROR - could not find MitPhysics/data. EXIT"
      echo " " 
    fi
  fi
  echo "  found MitPhysics/data at: $MIT_DATA"
else
  echo " Everything is ready already. Let's go!"
fi

# take care of the certificate
if [ -e "./x509up_u`id -u`" ]
then
  export X509_USER_PROXY="./x509up_u`id -u`"
fi
echo " INFO -- using the x509 ticket: $X509_USER_PROXY"

# get ready to run
echo " "; echo "${h}: Starting root job now"; echo " ";
echo \
  root -b -l -q .rootlogon.C \
  ${runMacro}+\(\"$fileset\",\"$skim\",\"$dataset\",\"$book\",\"$catalogDir\"\,\"$outputName\",$nEvents\)

  root -b -l -q .rootlogon.C \
  ${runMacro}+\(\"$fileset\",\"$skim\",\"$dataset\",\"$book\",\"$catalogDir\"\,\"$outputName\",$nEvents\)

# get the return code from the root job
status=`echo $?`
echo "${h}: Status - $status"

# # store the result (should in the future be done by condor)
# echo " "; echo "${h}: Checking the work area before copy"; echo " "
# ls -lhrt ./
# echo " "; echo "${h}: Checking the remote area before copy (only $dataset file)"; echo " "
# mkdir -p $outputDir/$outputName/$book/$dataset
# ls -lhrt $outputDir/$outputName/$book/$dataset
# mv       ${outputName}_${dataset}_${skim}_${fileset}*.root \
#          $outputDir/$outputName/$book/$dataset
# 
# echo " "; echo "${h}: Checking the work area after copy"; echo " "
# ls -lhrt ./
# echo " "; echo "${h}: Checking the remote area ($outputDir/$outputName/$book/$dataset) after copy (only $dataset file)"; echo " "
# ls -lhrt $outputDir/$outputName/$book/$dataset

finalSeconds=`date +"%s"`
let duration=($finalSeconds-$initialSeconds)/60
echo " end time      : "`date`
echo " duration      : $duration min"

exit $status
