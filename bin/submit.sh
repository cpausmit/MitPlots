#!/bin/bash
#===================================================================================================
# Now the submitter will use the full record of the jobs in terms of all input (tgz files) and
# even the file processed per datasetthat were created before (process.sh). The jobs runs out of a
# complete sandbox that it will carry with it. This allows for the jobs to flock smoothly over
# to our Tier-2 and the original files are all conveneintly storde with the production task.
#
# Version 3.0                                                                           Mar 13, 2014
#
# Several hooks for reprocessing, checking and debugging have been added. Look for environment
# variables DEBUG and the noStage variable that has been used. Ticket handling has been redone.
#
# Version 2.0                                                                           Mar 01, 2014
#
# Submit a set of jobs to run over a given dataset, splitting the jobs according to the filesets.
#
# Version 1.0                                                                           Nov 14, 2008
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
echo " "

logsDir=$MIT_PROD_LOGS/$outputName/$book/$dataset
globDir=$outputDir/$outputName
workDir=$outputDir/$outputName/$book/$dataset

# Check the directory for the log and root results
if ! [ -d "$logsDir" ] || ! [ -d "$globDir" ] || ! [ -d "$workDir" ]
then
  echo " ERROR - one of the relevant production directories does not exist. EXIT."
  echo " -> $logsDir $globDir $workDir"
  exit 1
fi

# Check the relevant tar balls
if ! [ -e "$globDir/${CMSSW_VERSION}.tgz" ] || ! [ -e "$globDir/external.tgz" ]
then
  echo " ERROR - one of the relevant production tar balls does not exist. EXIT."
  echo " -> $globDir/${CMSSW_VERSION}.tgz $globDir/external.tgz"
  exit 1
else
  echo "  Global directory structures exist."
fi

# Check the relevant run files exist
if ! [ -e "$globDir/run.sh" ] || \
   ! [ -e "$globDir/.rootlogon.C" ] || ! [ -e "$globDir/$runMacro" ] || \
   ! [ -e "$globDir/${runMacroTrunc}_C.so" ] || ! [ -e "$globDir/${runMacroTrunc}_C.d" ]
then
  echo " ERROR - one of the relevant run files does not exist. EXIT."
  echo " -> $globDir/run.sh $globDir/.rootlogon.C $globDir/$runMacro"
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

# set the script file
script=$globDir/run.sh

# Make sure there is a globus tickets available
x509File=/tmp/x509up_u`id -u`

# Looping through each single fileset and submitting the condor jobs
echo ""
echo "  Submitting jobs to condor"

if [ "$skim" == "noskim" ]
then
  filesets=$workDir/catalog/$book/$dataset/Filesets
else
  # needs to be reviewed if we work with skims
  filesets=$workDir/catalog/$book/$dataset/$skim/Filesets
fi

# Store condor status for later inspection
#echo "condor history"
condor_q -global $USER -format "%s " Cmd -format "%s \n" Args > /tmp/condorQueue.$$

# loop over the relevant filesets (hmmm... here we are using the old definitions)
#echo "start loop"
for fileset in `cat $filesets | cut -d' ' -f1 `
do

  # determine the expected output

  rFile="$workDir"
  rFile=`echo $rFile/${outputName}_${dataset}_${skim}_${fileset}*.root 2> /dev/null | cut -d' ' -f1`
  rFileSize=`ls -s $workDir/${outputName}_${dataset}_${skim}_${fileset}.root 2> /dev/null | cut -d' ' -f1`

  output="$logsDir/${skim}_${runTypeIndex}_${fileset}.out"

  # check if the output already exists and optional whether it is complete

  process=false
  if [ -f "$rFile" ] && (( $rFileSize > 5 ))
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
       nEventsInFileset=`grep ^$fileset $workDir/catalog/$book/$dataset/Filesets | tr -s ' ' | cut -d' ' -f3`
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
       duration=`tail -10 $output | grep duration | tr -s ' '`
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
    # some useful debugging sequences one can switch on
    #echo "$logsDir/${skim}_${runTypeIndex}_${fileset}.err"
    #grep 'SysError in <TFile::ReadBuffer>'  $logsDir/${skim}_${runTypeIndex}_${fileset}.err
    #grep "running on" $logsDir/${skim}_${runTypeIndex}_${fileset}.out
    #tail -10 $logsDir/${skim}_${runTypeIndex}_${fileset}.err
    continue
  fi

  # did we concluded this file needs processing? if yes let's do it!

  if [ "$process" == "true" ]
  then

    echo -n "   $script $runMacro $catalogDir $book $dataset $skim $fileset"
    echo    " $outputName $outputDir $runTypeIndex"

    # An exit hook to avoid reprocessing without loocking at the log first

    if [ "$DEBUG" != "" ]
    then
      echo "  FOR NOW NOT RE-SUBMITTING -- check error/output at:"
      echo "    cat $logsDir/${skim}_${runTypeIndex}_${fileset}*"
      continue
    fi

    cd $workDir

cat > submit.cmd <<EOF
Universe                = vanilla
Environment             = "HOSTNAME=$HOSTNAME HOME=$HOME MIT_DATA=$MIT_DATA MIT_PROD_JSON=$MIT_PROD_JSON MIT_PROD_OVERLAP=$MIT_PROD_OVERLAP"
# Only on Tier-2 #
#Requirements            = UidDomain == "cmsaf.mit.edu" && \
#                          Arch == "X86_64" && Disk >= DiskUsage && (Memory * 1024) >= ImageSize &&\
#                          HasFileTransfer
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
+AccountingGroup        = "group_cmsuser.$USER"
Queue
EOF

    condor_submit submit.cmd >& /dev/null

    # make sure it worked
    if [ "$?" != "0" ]
    then
      # show what happened and exit with error and leave the submit file
      condor_submit submit.cmd
      exit 1
    fi

    # it worked, so clean up
    rm submit.cmd

  fi

done

rm -f /tmp/condorQueue.$$

exit 0
