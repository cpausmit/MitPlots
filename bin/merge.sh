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
grep -v ^# ${MIT_USER_DIR}/config/${MIT_PROD_CFG}.txt > /tmp/mergeHgg.$$
nLine=0

for dset in `cat /tmp/mergeHgg.$$|grep -v ^#|tr -s ' '|cut -d' ' -f 2`
do

  nLine=$(($nLine+1))

  # find the line to this dataset and do further analysis
  line=`sed -n ${nLine}p /tmp/mergeHgg.$$`

  # determine the input dataset
  BOOK_VERSION=`echo $line | tr -s ' ' | cut -d ' ' -f 1`
  DATASET=`     echo $line | tr -s ' ' | cut -d ' ' -f 2`
  SKIM=`        echo $line | tr -s ' ' | cut -d ' ' -f 3`

  if [ "$PATTERN" == "" ] || [ "`echo $DATASET | grep $PATTERN`" != "" ]
  then
    if [ "`echo $BOOK_VERSION | tr -d [a-zA-Z0-9\-_]`" == "//" ]
    then
      BOOK_VERSION=`echo $BOOK_VERSION | cut -d/ -f2-3`
    fi

    # now merge the sucker
    mergeHist.py --Dataset=$DATASET \
                 --Skim=$SKIM \
                  --InputPath=$MIT_PROD_HIST/$MIT_PROD_CFG/$BOOK_VERSION \
                 --OutputPath=$MIT_PROD_HIST/$MIT_PROD_CFG/merged \
                 --FilenameHeader=$MIT_PROD_CFG
  fi

done

rm /tmp/mergeHgg.$$

exit 0
