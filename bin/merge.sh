#!/bin/bash
#===================================================================================================
# Script to merge all histogram files from a complete analysis task such that each sample with
# a well defined cross section is in one 'merged' file. This script follows the environment
# definitions.
#
#                                                                             Ch.Paus (Aug 15, 2010)
#===================================================================================================
PATTERN="$1"

echo " Config: ${MIT_USER_DIR}/config/${MIT_PROD_CFG}.txt"

# make clean copy of the config
grep -v ^# ${MIT_USER_DIR}/config/${MIT_PROD_CFG}.txt > /tmp/merge-${USER}.$$
nLine=0

# make sure to merge efficiently into hadoop scratch
mkdir -p /mnt/hscratch/$USER/$MIT_PROD_CFG/merged
mkdir -p /tmp/$MIT_PROD_CFG/merged
if   [ -L  "$MIT_PROD_HIST/$MIT_PROD_CFG/merged" ] 
then
  echo " Link ($MIT_PROD_HIST/$MIT_PROD_CFG/merged) exist already, using it."
elif [ -e  "$MIT_PROD_HIST/$MIT_PROD_CFG/merged" ] 
then
  echo " The directory: $MIT_PROD_HIST/$MIT_PROD_CFG/merged exists and is not a link."
  echo " Please fix! The easiest is to delete it but be careful not to loose anything. EXIT."
  exit 1
else
  cd            $MIT_PROD_HIST/$MIT_PROD_CFG/
  ln    -s /mnt/hscratch/$USER/$MIT_PROD_CFG/merged
  cd -  >& /dev/null
fi

for dset in `cat /tmp/merge-${USER}.$$|grep -v ^#|tr -s ' '|cut -d' ' -f 2`
do

  nLine=$(($nLine+1))

  # find the line to this dataset and do further analysis
  line=`sed -n ${nLine}p /tmp/merge-${USER}.$$`

  # determine the input dataset
  BOOK_VERSION=`echo $line | tr -s ' ' | cut -d ' ' -f 1`
  DATASET=`     echo $line | tr -s ' ' | cut -d ' ' -f 2`
  SKIM=`        echo $line | tr -s ' ' | cut -d ' ' -f 3`

  if [ "$PATTERN" == "" ] || [ "`echo $DATASET | grep $PATTERN`" != "" ]
  then
    # now merge the sucker
    echo " mergeHist.py --Dataset=$DATASET --Skim=$SKIM --FilenameHeader=$MIT_PROD_CFG
              --InputPath=$MIT_PROD_HIST/$MIT_PROD_CFG/$BOOK_VERSION
              --OutputPath=/tmp/$MIT_PROD_CFG/merged"
                 
    mergeHist.py --Dataset=$DATASET --Skim=$SKIM --FilenameHeader=$MIT_PROD_CFG \
	         --InputPath=$MIT_PROD_HIST/$MIT_PROD_CFG/$BOOK_VERSION \
                 --OutputPath=/tmp/$MIT_PROD_CFG/merged
    # move output to hadoop scratch (merging into hadoop does not work!)
    #                                root uses random writes that hadoop does not support)
    mv /tmp/$MIT_PROD_CFG/merged/${MIT_PROD_CFG}_${DATASET}_${SKIM}.root \
       /mnt/hscratch/$USER/$MIT_PROD_CFG/merged/${MIT_PROD_CFG}_${DATASET}_${SKIM}.root
  fi

done

rm /tmp/merge-${USER}.$$

exit 0
