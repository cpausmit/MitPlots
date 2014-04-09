#!/bin/bash
#===================================================================================================
#
# Script to convert crab output into our standard output we receive from condor jobs.
#
#                                                                             Ch.Paus (Apr 08, 2014)
#===================================================================================================
DIR="$1"
# we can in principle only check on the environment that has been setup
PROD_CFG=$MIT_PROD_CFG
PROD_HIST=$MIT_PROD_HIST
PROD_LOGS=$MIT_PROD_LOGS
# find the full configuration
crabTask=`basename $DIR`
line=`head -1 $DIR/share/arguments.list`
#echo " Found: $line"
## runBoostedV.C /home/cmsprod/catalog t2mit/filefi/032 s12-ww-v7a noskim 0000 boostedv /home/paus/cms/hist
BOOK=`echo $line | tr -s ' ' | cut -d' ' -f3`
DATASET=`echo $line | tr -s ' ' | cut -d' ' -f4`
SKIM=`echo $line | tr -s ' ' | cut -d' ' -f5`
# check whether it is what we expect to find
TEST_CFG=`echo $line | tr -s ' ' | cut -d' ' -f7`
TEST_HIST=`echo $line | tr -s ' ' | cut -d' ' -f8`
if [ "$TEST_CFG" != "$PROD_CFG" ] || [ "$TEST_HIST" != "$PROD_HIST" ]
then
  echo " The configuration in our environment and in the crab config seems inconcistent. EXIT."
  exit 1
fi

SPATH=`grep storage_path $DIR/share/crab.cfg | cut -d'=' -f3`
RPATH=`grep user_remote_dir $DIR/share/crab.cfg | cut -d'=' -f2`
SOURCE="$SPATH/$RPATH"
echo ""
echo " ==== Configuration ===="
echo ""
echo " crab directory:    $DIR"
echo " source directory:  $SOURCE"
echo ""
echo " output name:       $PROD_CFG"
echo " output directory:  $PROD_HIST"
echo " log directory:     $PROD_LOGS"
echo ""
echo " skim:              $SKIM"
echo " book:              $BOOK"
echo " dataset:           $DATASET"
echo ""

nJobs=`wc -l $DIR/share/arguments.list | cut -d' ' -f1`
i=1

while [ "$i" -le "$nJobs" ]
do
  # decode specific submission
  line=`sed -n ${i}p $DIR/share/arguments.list`  
  FILESET=`echo $line | tr -s ' ' | cut -d' ' -f6`
  FILEBASE="${PROD_CFG}_${DATASET}_${SKIM}_${FILESET}"
  # move the logfiles
  if [ -e "$DIR/res/CMSSW_${i}.stdout" ]
  then
    echo "mv $DIR/res/CMSSW_${i}.stderr $PROD_LOGS/$PROD_CFG/$BOOK/$DATASET/${FILEBASE}.err"
    echo "mv $DIR/res/CMSSW_${i}.stdout $PROD_LOGS/$PROD_CFG/$BOOK/$DATASET/${FILEBASE}.out"
  fi
  # move the root output
  if [ -e "$SOURCE/$BOOK/$DATASET/${FILEBASE}.root" ]
  then
    echo "mv $SOURCE/$BOOK/$DATASET/${FILEBASE}.root $PROD_HIST/$PROD_CFG/$BOOK/$DATASET/${FILEBASE}.root"
  fi
  # make sure we move on ;-)
  let i++
done

exit 0
