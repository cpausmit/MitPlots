#!/bin/bash
#===================================================================================================
# Submit a set of jobs to run over a given dataset, splitting the jobs according to the filesets.
#
# Version 1.0                                                                           Nov 14, 2008
#
# Several hooks for reprocessing, checking and debugging have been added. Look for environment
# variables DEBUG and the noStage variable that has been used. Ticket handling has been redone.
#
# Version 2.0                                                                           Mar 01, 2014
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
runMacroTrunc=`echo $runMacro | sed 's#.C$##'`

# Prepare environment
echo " "
echo "  Process: dataset=$dataset, book=$book, catalog=$catalogDir"

# Create the directory for the log and root results
logsDir=$MIT_PROD_LOGS/$outputName/$book/$dataset
mkdir -p $logsDir
globDir=$outputDir/$outputName
mkdir -p $globDir
workDir=$outputDir/$outputName/$book/$dataset
mkdir -p $workDir

# make general tgz for the production (this will only happen once, carefully cleanup before restarting)
cd $outputDir/$outputName
makeTgz.sh
cp $MIT_ANA_DIR/bin/run.sh             $globDir
cp /home/$USER/cms/root/.rootlogon.C   $globDir
if ! [ -e "$globDir/$runMacro" ]
then
  cp $MIT_USER_DIR/macros/$runMacro    $globDir
  cp $MIT_ANA_DIR/macros/compile.C     $globDir
  root -l -b -q  compile.C"(\"$runMacro\")"
  if [ "$?" != "0" ]
  then
    echo "  ERROR -- compilation of the run Macro failed. EXIT!"
    exit 1
  fi
fi
script=$globDir/run.sh

# make the specific input catalog, the script and macros to run (they are made for every dataset)
cd $catalogDir/..
if ! [ -e "$workDir/catalog.tgz" ]
then
  echo "  tar fzc $workDir/catalog.tgz catalog/$book/$dataset"
  tar fzc $workDir/catalog.tgz catalog/$book/$dataset
  cd $workDir
else
  echo "  use existing catalog: $workDir/catalog.tgz"
fi

# Make sure there is a globus tickets available
x509File=/tmp/x509up_u`id -u`

# Looping through each single fileset and submitting the condor jobs
echo ""
echo "  Submitting jobs to condor"

if [ "$skim" == "noskim" ]
then
  filesets=$catalogDir/$book/$dataset/Filesets
else
  filesets=$catalogDir/$book/$dataset/$skim/Filesets
fi

# Store condor status for later inspection
condor_q -global $USER -format "%s " Cmd -format "%s \n" Args > /tmp/condorQueue.$$
if [ "$?" != "0" ]
then
  echo ""
  echo " ERROR - condor_q command failed."
  echo ' --> condor_q -global $USER -format "%s " Cmd -format "%s \n" Args '
  echo ""
  echo "  EXIT"
  echo ""
  exit 1
fi


for fileset in `cat $filesets | cut -d' ' -f1 `
do

  # determine the expected output

  rFile="$workDir"
  rFile=`echo $rFile/${outputName}_${dataset}_${skim}_${fileset}*.root | cut -d' ' -f1 2> /dev/null`
  output="$logsDir/${skim}_${runTypeIndex}_${fileset}.out"

  # check if the output already exists and optional whether it is complete

  process=false
  if [ -f "$rFile" ]
  then
     # File exists now see whether more checks are asked for
     if [ "$noStage" == "1" ] 
     then
       # Check whether all events were processed
       dir=`dirname $rFile`
       file=`basename $rFile`
       duration=`tail -10 $output | grep duration | tr -s ' '`
       root -l -b -q $MIT_ANA_DIR/macros/runSimpleFileCataloger.C+\(\"$dir\",\"$file\"\) >& /tmp/tmp.$$
       # Get number of events processed from output file
       nEventsProcessed=`grep XX-CATALOG-XX /tmp/tmp.$$ | cut -d' ' -f3`
       # Get number of events contained in the original input file
       nEventsInFileset=`grep ^$fileset     $catalogDir/$book/$dataset/Filesets | tr -s ' ' | cut -d' ' -f3`
       # Compare whether we got what we asked for
       if [ "$nEventsProcessed" != "$nEventsInFileset" ]
       then
         echo " "
         echo " ERROR - "
         echo "   Processed  $nEventsProcessed  of  $nEventsInFileset  total"
         echo " "
         process=true
       else
         echo "   File: $rFile completed with  $nEventsProcessed  events processed ($duration)."
       fi
     elif [ "$noStage" == "2" ] 
     then
       # Show processing duration
       echo "   File: $rFile exists already. Processing $duration"
     else
       # Show that file was processed (fastest option and usually sufficient)
       echo "   File: $rFile exists already."
     fi
     # make sure to move on if completed
     if [ "$process" == "false" ] 
     then
       continue
     fi
  else
    process=true
  fi

  # check whether file is already submitted to condor

  pattern="$script $runMacro $catalogDir $book $dataset $skim $fileset $outputName $outputDir $runTypeIndex"
  pattern=`echo $pattern| sed 's/ *$//'`
  inQueue=`grep "$pattern" /tmp/condorQueue.$$`
  if [ "$inQueue" != "" ]
  then
    echo " Queued: $rFile"
    continue
  fi

  # did we concluded this file needs processing? if yes let's do it!

  if [ "$process" == "true" ]
  then

    echo "   $script $runMacro $catalogDir $book $dataset $skim $fileset $outputName $outputDir $runTypeIndex"

    # An exit hook to avoid reprocessing without loocking at the log first

    if [ "$DEBUG" != "" ]
    then
      echo "  FOR NOW NOT RE-SUBMITTING -- check error/output at:"
      echo "    cat $logsDir/${skim}_${runTypeIndex}_${fileset}*"
      continue
    fi
  
cat > submit.cmd <<EOF
Universe                = vanilla
Environment             = "HOSTNAME=$HOSTNAME HOME=$HOME MIT_DATA=$MIT_DATA MIT_PROD_JSON=$MIT_PROD_JSON MIT_PROD_OVERLAP=$MIT_PROD_OVERLAP"
Requirements            = (UidDomain == "cmsaf.mit.edu" || UidDomain == "mit.edu") && Arch == "X86_64" && Disk >= DiskUsage && (Memory * 1024) >= ImageSize && HasFileTransfer
Notification            = Error
Executable              = $script
Arguments               = $runMacro $catalogDir $book $dataset $skim $fileset $outputName $outputDir $runTypeIndex
Rank                    = Mips
GetEnv                  = False
Input                   = /dev/null
Output                  = $logsDir/${skim}_${runTypeIndex}_${fileset}.out
Error                   = $logsDir/${skim}_${runTypeIndex}_${fileset}.err
Log                     = $logsDir/${skim}_${runTypeIndex}_${fileset}.log
transfer_input_files    = $x509File,$globDir/${CMSSW_VERSION}.tgz,$globDir/external.tgz,catalog.tgz,$globDir/.rootlogon.C,$globDir/$runMacro,$globDir/${runMacroTrunc}_C.so,$globDir/${runMacroTrunc}_C.d
Initialdir              = $workDir
transfer_output_files   = ${outputName}_${dataset}_${skim}_${fileset}.root
should_transfer_files   = YES
when_to_transfer_output = ON_EXIT
+AccountingGroup        = "group_cmsuser.paus"
Queue
EOF

    condor_submit submit.cmd >& /dev/null;
    rm submit.cmd
  fi

done

rm -f /tmp/condorQueue.$$

exit 0
