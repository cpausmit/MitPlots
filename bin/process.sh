#!/bin/bash
#===================================================================================================
# Script to process our complete analysis task.
#
#                                                                             Ch.Paus (Aug 15, 2010)
#===================================================================================================
echo " Config: ${MIT_USER_DIR}/config/${MIT_PROD_CFG}.txt"

# make clean copy of the config
grep -v ^# ${MIT_USER_DIR}/config/${MIT_PROD_CFG}.txt > /tmp/processHgg.$$
nLine=0

for dset in `cat /tmp/processHgg.$$|grep -v ^#|tr -s ' '|cut -d' ' -f 2`
do

  nLine=$(($nLine+1))

  # find the line to this dataset and do further analysis
  line=`sed -n ${nLine}p /tmp/processHgg.$$`

  # determine the input dataset
  BOOK_VERSION=`echo $line | tr -s ' ' | cut -d ' ' -f 1`
  DATASET=`     echo $line | tr -s ' ' | cut -d ' ' -f 2`
  SKIM=`        echo $line | tr -s ' ' | cut -d ' ' -f 3`

  # find potential JSON file and the cut to remove overlaps
  export MIT_PROD_JSON=`   echo $line | tr -s ' ' | cut -d ' ' -f 8`
  export MIT_PROD_OVERLAP=`echo $line | tr -s ' ' | cut -d ' ' -f 7`
  echo " JSON: $MIT_PROD_JSON  Overlap: $MIT_PROD_OVERLAP"

  # now submit the sucker
  submit.sh $MIT_PROD_MACRO $MIT_CATALOG   $BOOK_VERSION   $DATASET $SKIM \
            $MIT_PROD_CFG   $MIT_PROD_HIST $CHECK_COMPLETE

done

rm /tmp/processHgg.$$

exit 0
