#!/bin/bash
#===================================================================================================
# Submit the jobs for one complete dataset. The script does not assume that this is an entirely new
# submission but rather checks for the possibly existing output files and excludes them from furhter
# consideration.
#
# Version 1.0                                                                           Mar 13, 2014
#===================================================================================================
# Read the arguments
echo " "
echo "Starting data processing with arguments:"
echo "  --> $*"

    runMacro=$1
  catalogDir=$2
        book=$3
     dataset=$4
        skim=$5
  outputName=$6
   outputDir=$7
runTypeIndex=$8

runMacroTrunc=`echo $runMacro | sed 's#.C$##'`

# Prepare environment
#--------------------

echo " "
echo "  Process: dataset=$dataset, book=$book, catalog=$catalogDir"
echo " "

logsDir=$MIT_PROD_LOGS/$outputName/$book/$dataset
globDir=$outputDir/$outputName
workDir=$outputDir/$outputName/$book/$dataset

# Check for all required files
#-----------------------------

# Check the directory for the log and root results
if ! [ -d "$logsDir" ] || ! [ -d "$globDir" ] || ! [ -d "$workDir" ]
then
  echo " ERROR - one of the relevant production directories does not exist. EXIT."
  echo " -> $logsDir $globDir $workDir"
  exit 1
fi

# Check the relevant tar balls
if ! [ -e "$globDir/${CMSSW_VERSION}.tgz" ] || ! [ -e "$globDir/${CMSSW_VERSION}-src.tgz" ] ||\
   ! [ -e "$globDir/external.tgz" ] || ! [ -e "$globDir/json.tgz" ]
then
  echo " ERROR - one of the relevant production tar balls does not exist. EXIT."
  echo " -> $globDir/${CMSSW_VERSION}.tgz $globDir/${CMSSW_VERSION}-src.tgz"
  echo " -> $globDir/external.tgz $globDir/json.tgz "
  exit 1
else
  echo "  Global directory structures exist."
fi

# Check the relevant run files exist
if ! [ -e "$workDir/setup.sh" ] || \
   ! [ -e "$globDir/runCrab.sh" ] || ! [ -e "$globDir/runCrabJob.sh" ] || \
   ! [ -e "$globDir/.rootlogon.C" ] || ! [ -e "$globDir/$runMacro" ] || \
   ! [ -e "$globDir/${runMacroTrunc}_C.so" ] || ! [ -e "$globDir/${runMacroTrunc}_C.d" ]
then
  echo " ERROR - one of the relevant run files does not exist. EXIT."
  echo " -> $workDir/setup.sh $globDir/runCrab.sh $globDir/runCrabJob.sh"
  echo " -> $globDir/.rootlogon.C $globDir/$runMacro"
  echo " -> $globDir/${runMacroTrunc}_C.so $globDir/${runMacroTrunc}_C.d"
  exit 1
else
  echo "  Global run files exist."
fi

# Check the relevant catalog
if ! [ -e "$workDir/catalog.tgz" ]
then
  echo " ERROR - relevant catalog tar balls does not exist. EXIT."
  echo " -> $workDir/catalog.tgz"
  exit 1
else
  echo "  Catalog file exists. Untarring for submission."
  cd      $workDir
  tar fzx catalog.tgz
  cd - >& /dev/null
fi

# Looping through each single fileset and see whether it exists already
#----------------------------------------------------------------------

if [ "$skim" == "noskim" ]
then
  filesets=$workDir/catalog/$book/$dataset/Filesets
else
  # needs to be reviewed if we work with skims
  filesets=$workDir/catalog/$book/$dataset/$skim/Filesets
fi

# Make list of all existing output files
ls -s $workDir/${outputName}_${dataset}_${skim}_????.root 2> /dev/null \
      > /tmp/$USER_exisiting_${dataset}.$$

# Loop through all datasets and only list missing filesets
rm -rf $workDir/arguments.list
touch  $workDir/arguments.list
for fileset in `cat $filesets | cut -d' ' -f1 `
do
  rFile=${outputName}_${dataset}_${skim}_${fileset}.root
  exists=`grep $rFile /tmp/$USER_exisiting_${dataset}.$$`
  if [ "$exists" == "" ]
  then
    echo "$runMacro $catalogDir $book $dataset $skim $fileset $outputName $outputDir $runTypeIndex" \
         >> $workDir/arguments.list
  fi
done

# Cleanup
rm -rf /tmp/$USER_exisiting_${dataset}.$$

# Prepare the crab configuration file from our template
#------------------------------------------------------
nJobs=`wc -l $workDir/arguments.list | cut -d' ' -f1`
if [ "$nJobs" == "0" ]
then
  echo ""
  echo " All requested files are already available. EXIT!"  
  echo "  --> $workDir/"
  echo ""
  exit 0
fi

cat $CMSSW_BASE/src/MitAna/config/crab.cfg \
  | sed "s#XX-NJOBS-XX#$nJobs#g" \
  | sed "s#XX-LOCAL_DIR-XX#$workDir#g" \
  | sed "s#XX-CMSSW_VERS-XX#$CMSSW_VERSION#g" \
  | sed "s#XX-RUN_MACRO-XX#$runMacroTrunc#g" \
  | sed "s#XX-MITSE-XX#$MIT_PROD_SE#g" \
  | sed "s#XX-MITSPATH-XX#$MIT_PROD_SDIR#g" \
  | sed "s#XX-MITRDIR-XX#$MIT_PROD_RDIR#g" \
  > $globDir/crab_${dataset}.cfg

cat $globDir/crab_${dataset}.cfg 

# Submit the crab task
#---------------------
jobId=`date +%j%m%d%k%M%S`

echo ""
echo "  Submitting task with crab"
echo ""

cd $globDir
cp $CMSSW_BASE/src/MitAna/config/fake.py ./
echo "crab -create -cfg crab_${dataset}.cfg -USER.ui_working_dir=crab_$jobId_${dataset}"
      crab -create -cfg crab_${dataset}.cfg -USER.ui_working_dir=crab_$jobId_${dataset}
echo "crab -submit -continue crab_$jobId_${dataset}"
      crab -submit -continue crab_$jobId_${dataset}

# make sure to keep a convenient copy of the arguments list for later unpacking
cp $workDir/arguments.list crab_$jobId_${dataset}/share/

# cleanup crab config
rm  crab_${dataset}.cfg

exit 0
