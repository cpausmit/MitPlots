#!/bin/bash
#===================================================================================================
#
# Script to process our complete analysis task. The environment has to be defined before. The
# newest addition is that the tar ball for the code and the other files needed for this production
# will be created here and not in the submit script. This will ensure that all input to the job
# is going to be fixed when this script runs for the first time. Makes the process much more
# redproducible and safe against changes that people make while their jobs are still running and
# possibly have to be resubmitted several times.
#
# There are two more environment variables that you can use to further the checks or debugging:
#
#  DEBUG - is set to anything it will tell you which jobs failed and tell you the err/out locations
#
#  CHECK_COMPLETE - if set to "1" it will confirm that all events were processed
#                   if set to "2" it will tell you the the duration of the completed jobs
#
#                                                                             Ch.Paus (Aug 15, 2010)
#===================================================================================================
# parameter $1 ($NEW) can have two special values:
#
#   new     - remove and start over
#   update  - remake all required files with current configuration and submit what is missing
#
# for all other values the remaing jobs are submitted with the existing setup
#
NEW="$1"
echo " Config: ${MIT_USER_DIR}/config/${MIT_PROD_CFG}.txt --> $NEW"

# make clean copy of the config
grep -v ^# ${MIT_USER_DIR}/config/${MIT_PROD_CFG}.txt > /tmp/process.$$

#--------------------------------------------------------------------------------------------------
# check whether this is a new task where we have to delete all existing output
#--------------------------------------------------------------------------------------------------
# remove the existing files
if [ "$NEW" == "new" ]
then
  echo " You are requesting this to be a new production task. All existing files will be cleared."
  echo " Wanna save existing task? Do like:  moveOutput.sh $MIT_PROD_CFG ${MIT_PROD_CFG}-last."
  read -p "Do you wish to continue? [N/y] " yn
  if [ "$yn" != "y" ] && [ "$yn" != "Y" ] 
  then
    echo " Nothing done. EXIT."
    exit
  else
    # setup relevant variables
    logsDir=$MIT_PROD_LOGS/$MIT_PROD_CFG
    globDir=$MIT_PROD_HIST/$MIT_PROD_CFG
    # remove the existing files
    echo " removing old files in: $globDir $logsDir"
    rm -rf $globDir $logsDir
  fi
fi

#--------------------------------------------------------------------------------------------------
# check whether this is an update where the input have to be remade
#--------------------------------------------------------------------------------------------------
# Now remake what needs remaking
if [ "$NEW" == "new" ] || [ "$NEW" == "update" ]
then
  # setup relevant variables
  logsDir=$MIT_PROD_LOGS/$MIT_PROD_CFG
  globDir=$MIT_PROD_HIST/$MIT_PROD_CFG
  
  # re-make all required directories
  echo " re-make the basic directory structure"
  mkdir -p $globDir $logsDir
  
  # create the global tar balls and files
  echo " generate tar balls and other files"
  cd $MIT_PROD_HIST/$MIT_PROD_CFG
  makeTgz.sh
  cp $MIT_ANA_DIR/bin/run.sh              $globDir
  cp $MIT_ANA_DIR/bin/runCrab.sh          $globDir
  cp $MIT_ANA_DIR/bin/runCrabJob.sh       $globDir
  cp /home/$USER/cms/root/.rootlogon.C    $globDir
  cp $MIT_USER_DIR/macros/$MIT_PROD_MACRO $globDir
  cp $MIT_ANA_DIR/macros/compile.C        $globDir
  # define our external path variable
  export EXTERNAL=/home/cmsprod/cms/external
  # compile the bare run macro
  root -l -b -q  compile.C"(\"$MIT_PROD_MACRO\")"
  if [ "$?" != "0" ]
  then
    echo "  ERROR -- compilation of the run Macro failed. EXIT!"
    exit 1
  fi
  
  # loop through the requested datasets and make directory structures/catalogs/files
  
  nLine=0
  for dset in `cat /tmp/process.$$|grep -v ^#|tr -s ' '|cut -d' ' -f 2`
  do
    nLine=$(($nLine+1))

    # find the line to this dataset and do further analysis
    # -- please do not ask why I do this in a bit convoluted way, I do not know how to do it
    line=`sed -n ${nLine}p /tmp/process.$$`

    # determine the input dataset
    BOOK_VERSION=`echo $line | tr -s ' ' | cut -d ' ' -f 1`
    DATASET=`     echo $line | tr -s ' ' | cut -d ' ' -f 2`
    SKIM=`        echo $line | tr -s ' ' | cut -d ' ' -f 3`

    # make directories
    logsDir=$MIT_PROD_LOGS/$MIT_PROD_CFG/$BOOK_VERSION/$DATASET
    mkdir -p $logsDir
    globDir=$MIT_PROD_HIST/$MIT_PROD_CFG
    mkdir -p $globDir
    workDir=$MIT_PROD_HIST/$MIT_PROD_CFG/$BOOK_VERSION/$DATASET
    mkdir -p $workDir

    # define all variables that need to be defined when running in queue
    export MIT_PROD_JSON=`   echo $line | tr -s ' ' | cut -d ' ' -f 8`
    export MIT_PROD_OVERLAP=`echo $line | tr -s ' ' | cut -d ' ' -f 7`
    #export MIT_PROD_SE="se01.cmsaf.mit.edu"
    export MIT_PROD_SE="t3serv006.mit.edu"
    export MIT_PROD_SDIR='/srm/v2/server?SFN=/mnt/hadoop/cms/store'
    export MIT_PROD_RDIR="user/paus/bambu"
    rm -rf $workDir/setup.sh
    touch  $workDir/setup.sh
    echo "export MIT_PROD_JSON='$MIT_PROD_JSON'"     >> $workDir/setup.sh
    echo "export MIT_PROD_OVERLAP=$MIT_PROD_OVERLAP" >> $workDir/setup.sh
    echo "export MIT_PROD_SE=$MIT_PROD_SE"           >> $workDir/setup.sh
    echo "export MIT_PROD_SDIR=$MIT_PROD_SDIR"       >> $workDir/setup.sh
    echo "export MIT_PROD_RDIR=$MIT_PROD_RDIR"       >> $workDir/setup.sh

    # create the catalog for this dataset
    cd $MIT_CATALOG/..
    echo "  making tar ball of the catalog: catalog/$BOOK_VERSION/$DATASET"
    echo "  -> tar fzc $workDir/catalog.tgz catalog/$BOOK_VERSION/$DATASET"
    tar fzc $workDir/catalog.tgz catalog/$BOOK_VERSION/$DATASET

    # generate arguments list from the catalog file
    rm -rf $workDir/arguments.list
    touch  $workDir/arguments.list
    if [ "$SKIM" == "noskim" ]
    then
      filesets=catalog/$BOOK_VERSION/$DATASET/Filesets
    else
      # needs to be reviewed if we work with skims
      filesets=catalog/$BOOK_VERSION/$DATASET/$SKIM/Filesets
    fi
    for fileset in `cat $filesets | cut -d' ' -f1 `
    do
      echo "$MIT_PROD_MACRO $MIT_CATALOG $BOOK $DATASET $SKIM $fileset $MIT_PROD_CFG $MIT_PROD_HIST \
            '' " > $workDir/arguments.list
    done
  done    
fi

#--------------------------------------------------------------------------------------------------
# ready for the submission step -- submit the task
#--------------------------------------------------------------------------------------------------
nLine=0
for dset in `cat /tmp/process.$$|grep -v ^#|tr -s ' '|cut -d' ' -f 2`
do

  nLine=$(($nLine+1))

  # find the line to this dataset and do further analysis
  line=`sed -n ${nLine}p /tmp/process.$$`

  # determine the input dataset
  BOOK_VERSION=`echo $line | tr -s ' ' | cut -d ' ' -f 1`
  DATASET=`     echo $line | tr -s ' ' | cut -d ' ' -f 2`
  SKIM=`        echo $line | tr -s ' ' | cut -d ' ' -f 3`

  BOOK=$BOOK_VERSION

  # find potential JSON file and the cut to remove overlaps
  export MIT_PROD_JSON=`   echo $line | tr -s ' ' | cut -d ' ' -f 8`
  export MIT_PROD_OVERLAP=`echo $line | tr -s ' ' | cut -d ' ' -f 7`
  #echo " JSON: $MIT_PROD_JSON  Overlap: $MIT_PROD_OVERLAP"

  # now submit the sucker
  #----------------------

  # standard condor submission
  if [ "$MIT_CRAB" == "" ]
  then
    submit.sh $MIT_PROD_MACRO $MIT_CATALOG $BOOK $DATASET $SKIM $MIT_PROD_CFG $MIT_PROD_HIST "" \
              $CHECK_COMPLETE

    ## exit          # for now just one prodcution

  # or using CRAB
  else
    if [ -z "$LCG_LOCATION" ]
    then
      source /afs/cern.ch/cms/LCG/LCG-2/UI/cms_ui_env.sh
    fi
    submitCrab.sh $MIT_PROD_MACRO $MIT_CATALOG $BOOK $DATASET $SKIM $MIT_PROD_CFG $MIT_PROD_HIST ""
    ## exit          # for now just one prodcution
  fi

  # make sure the submit worked
  if [ "$?" != "0" ]
  then
    echo "  ERROR -- submit failed. EXIT!"
    rm /tmp/process.$$
    exit 1
  fi

done

rm /tmp/process.$$

exit 0
