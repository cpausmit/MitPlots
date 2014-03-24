#!/bin/bash
#---------------------------------------------------------------------------------------------------
# Request one file to be downloaded using SmartCache queues. 
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
if [ -e "/usr/local/DynamicData/SmartCache/setup.sh" ]
then
  echo " Making request:"
  echo " -> addDownloadRequest.py --file=$filename --dataset=$dataset --book=$book/$version"
  addDownloadRequest.py --file=$filename --dataset=$dataset --book=$book/$version
  rc="$?"
else
  echo " $h - SmartCache not available here... need alternative."
  exit 1
fi

exit $rc

