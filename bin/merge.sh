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
              --OutputPath=$MIT_PROD_HIST/$MIT_PROD_CFG/merged"
                 
    mergeHist.py --Dataset=$DATASET --Skim=$SKIM --FilenameHeader=$MIT_PROD_CFG \
	         --InputPath=$MIT_PROD_HIST/$MIT_PROD_CFG/$BOOK_VERSION \
                 --OutputPath=$MIT_PROD_HIST/$MIT_PROD_CFG/merged
  fi

done

rm /tmp/merge-${USER}.$$

exit 0
