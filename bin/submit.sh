#!/bin/bash
#===================================================================================================
# Submit a set of jobs to run over a given dataset, splitting the jobs according to the filesets.
#
# Version 1.0                                                                      November 14, 2008
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
     noStage=$9

jobId=`date +%j%m%d%k%M%S`
dataDir=`tail -1  $catalogDir/$book/$dataset/Filesets | cut -d' ' -f2`

# Prepare environment
echo " "
echo "  Process: dataset=$dataset, book=$book, catalog=$catalogDir"
#echo " "
workDir=/home/$USER/cms/condor
mkdir -p $workDir
cd $workDir
cp /home/$USER/cms/root/.rootlogon.C $workDir
cp $MIT_ANA_DIR/bin/run.sh           $workDir
cp $MIT_USER_DIR/macros/$runMacro    $workDir
script=$workDir/run.sh

# Create the directory for the results
mkdir -p $workDir/res/$outputName/$book/$dataset/

# Looping through each single fileset and submitting the condor jobs
echo "  Submitting jobs to condor"

if [ "$skim" == "noskim" ]
then
  filesets=$catalogDir/$book/$dataset/Filesets
else
  filesets=$catalogDir/$book/$dataset/$skim/Filesets
fi

for fileset in `cat $filesets | cut -d' ' -f1 `
do
  # check if the output already exists and whether it is complete
  rFile="$outputDir/$outputName/$book/$dataset"
  rFile=`ls $rFile/${outputName}_${dataset}_${skim}_${fileset}*.root 2> /dev/null`

  process=false
  if [ -f "$rFile" ]
  then
     echo "  File: $rFile exists already."
     dir=`dirname $rFile`
     file=`basename $rFile`
     # check whether the output file shows the expected number of events
     if [ "$noStage" == "1" ] 
     then
       root -l -b -q $MIT_ANA_DIR/macros/runSimpleFileCataloger.C+\(\"$dir\",\"$file\"\) >& /tmp/tmp.$$
       nEventsProcessed=`grep XX-CATALOG-XX /tmp/tmp.$$ | cut -d' ' -f3`
       nEventsInFileset=`grep ^$fileset     $catalogDir/$book/$dataset/Filesets | tr -s ' ' | cut -d' ' -f3`
       if [ "$nEventsProcessed" != "$nEventsInFileset" ]
       then
         echo " "
         echo " ERROR - "
         echo "   Processed  $nEventsProcessed  of  $nEventsInFileset  total"
         echo " "
         process=true
       fi
     fi
  else
    process=true
  fi

  if [ "$process" == "true" ]
  then

    logFile=`echo $book/$dataset/$fileset | tr '/' '+'`
    logFile=/tmp/$USER/$logFile
    mkdir -p /tmp/$USER
    rm    -f $logFile
    echo "   $script $runMacro $catalogDir $book $dataset $skim $fileset $outputName $outputDir $runTypeIndex"
  
cat > submit.cmd <<EOF
Universe                = vanilla
Requirements            = ((Arch == "X86_64") && (OpSys == "LINUX") && (Disk >= DiskUsage) && ((Memory * 1024) >= ImageSize) && (HasFileTransfer))
Notification            = Error
Executable              = $script
Arguments               = $runMacro $catalogDir $book $dataset $skim $fileset $outputName $outputDir $runTypeIndex
Rank                    = Mips
GetEnv                  = True
Initialdir              = $workDir
Input                   = /dev/null
Output                  = $workDir/res/$outputName/$book/$dataset/${skim}_${runTypeIndex}_${fileset}.out
Error                   = $workDir/res/$outputName/$book/$dataset/${skim}_${runTypeIndex}_${fileset}.err
Log                     = $logFile
should_transfer_files   = YES
when_to_transfer_output = ON_EXIT
Queue
EOF

    condor_submit submit.cmd >& /dev/null;
    rm submit.cmd
  fi

done

exit 0
