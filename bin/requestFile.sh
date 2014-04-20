#!/bin/bash
#---------------------------------------------------------------------------------------------------
# Request one file to be downloaded using SmartCache queues or through local download with xrdcp. 
#
#                                                                           C.Paus (V0 Apr xx, 2014)
#---------------------------------------------------------------------------------------------------
h=`basename $0`
# start waiting time now
startTime=$(date +%s)

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
  # do not ask me why I do this! PYTHON MADNESS
  home=$HOME; unset -v `env | sed -e 's/=.*//'`; export HOME=$home; export PATH=/bin:/usr/bin
  source $home/.bashrc
  # worst patch in a long time #

  source /usr/local/DynamicData/SmartCache/setup.sh
  export PATH="${PATH}:$SMARTCACHE_DIR/Client"

  echo " Making request:"
  echo " -> addDownloadRequest.py --file=$filename --dataset=$dataset --book=$book/$version"
  addDownloadRequest.py --file=$filename --dataset=$dataset --book=$book/$version
  rc="$?"
else
  server="xrootd.cmsaf.mit.edu"
  echo " $h - SmartCache not available or not requested.. trying xrootd cp (xrdcp)."
  echo " -> xrdcp from $server to ./store/user/paus/$book/$version/$dataset/$filename"
  mkdir -p ./store/user/paus/$book/$version/$dataset
  ( xrdcp -s root://${server}//store/user/paus/$book/$version/$dataset/$filename \
                            ./store/user/paus/$book/$version/$dataset/$filename.xrdcp && \
    mv ./store/user/paus/$book/$version/$dataset/$filename.xrdcp \
       ./store/user/paus/$book/$version/$dataset/$filename ) &
  
fi

exit $rc
