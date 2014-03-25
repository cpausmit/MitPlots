#!/bin/bash
#---------------------------------------------------------------------------------------------------
# Request one file to be downloaded using SmartCache queues or through local download with xrdcp. 
#
#---------------------------------------------------------------------------------------------------
h=`basename $0`
# start waiting time now
startTime=$(date +%s)

if [ -e "/usr/local/DynamicData/SmartCache/setup.sh" ]
then
  source /usr/local/DynamicData/SmartCache/setup.sh
  export PATH="${PATH}:$SMARTCACHE_DIR/Client"
fi

FILE="$1"

if [ -e "$FILE" ]
then
  echo " $h - Found file: $FILE. EXIT!"
  exit 0
fi

filename=`basename $FILE`
dirName=`dirname $FILE`

dataset=`basename $dirName`
dirName=`dirname $dirName`

version=`basename $dirName`
dirName=`dirname $dirName`

book=`basename $dirName`

rc=0
if [ -e "/usr/local/DynamicData/SmartCache/setup.sh" ] && \
   [ "`echo $FILE | grep ^/mnt/hadoop/cms`" != "" ]
then
  echo " Making request:"
  echo " -> addDownloadRequest.py --file=$filename --dataset=$dataset --book=$book/$version"
  addDownloadRequest.py --file=$filename --dataset=$dataset --book=$book/$version
  rc="$?"
else
  server="xrootd.cmsaf.mit.edu"
  echo " $h - SmartCache not available or not requested.. trying xroot cp (xrdcp)."
  mkdir -p ./store/user/paus/$book/$version/$dataset
  ( xrdcp -s root://${server}//store/user/paus/$book/$version/$dataset/$filename \
                            ./store/user/paus/$book/$version/$dataset/$filename.xrdcp && \
    mv ./store/user/paus/$book/$version/$dataset/$filename.xrdcp \
       ./store/user/paus/$book/$version/$dataset/$filename ) &
  
fi

exit $rc
