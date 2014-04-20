#!/bin/bash
#---------------------------------------------------------------------------------------------------
# Execute one job (works interactively and when executed in condor)
#---------------------------------------------------------------------------------------------------
# do not ask me why I do this!
home=$HOME; unset -v `env | sed -e 's/=.*//'`; export HOME=$home; export PATH=/bin:/usr/bin
source $home/.bashrc
# worst patch in a long time #

h=`basename $0`
# start waiting time now
startTime=$(date +%s)

# this need to be fixed when setting up the package correctly
source /usr/local/DynamicData/SmartCache/setup.sh
export PATH="${PATH}:$SMARTCACHE_DIR/Client"

catalogDir=$1
      book=$2
   dataset=$3
      skim=$4
   fileset=$5

# some basic printing
echo " "
echo " INFO ($h) - Show what we will do";
echo " "
echo "      arguments: $*";
echo " ";


exit 0; # - TO FAKE IT

# Make sure catalog and book are compliant for download

if [ "`echo $book | tr -d [a-zA-Z0-9\-_]`" == "//" ]
then
  newBook=`echo $book | cut -d/ -f2-3`
  newCatalogDir=$catalogDir/`echo $book | cut -d/ -f1`
else
  newBook=$book
  newCatalogDir=$catalogDir
fi

# First make the filelist
files=""
nFiles=`cat $newCatalogDir/$newBook/$dataset/Files | grep ^$fileset | wc -l`
echo " Number of files to cache: $nFiles"
echo ""

for line in `cat $newCatalogDir/$newBook/$dataset/Files | grep ^$fileset`
do
  if [ "`echo $line | grep root`" != "" ]
  then
    files="$files $line"
    if [ -z "$filesCheck" ]
    then
      filesCheck=$line
    else
      filesCheck="$filesCheck,$line"
    fi
  fi
done

# Avoid caching if running on a T2 machine
if [ "`hostname  | grep 'cmsaf' `" != "" ]  
then
  echo ""
  echo " cacheFileset.sh -- running on a Tier-2 machine, no caching needed. EXIT"
  echo ""
  exit 0
fi

# Enter the download requests into the database
complete=1
for file in `echo $files`
do
  echo " Testing: $SMARTCACHE_DATA/$newBook/$dataset/$file"

  if [ -e "$SMARTCACHE_DATA/$newBook/$dataset/$file" ]
  then
    echo " File: $newBook/$dataset/$file already available."
  else
    complete=0
    addDownloadRequest.py --file=$file --dataset=$dataset --book=$newBook
  fi
done

# Prevent further checking if no download requests were made
if [ "$complete" == "1" ]
then
  echo ""
  echo " cacheFileset.sh -- all files are available. EXIT"
  echo ""
  exit 0
fi

# Now check every now and then whether they have completed
done=0
while [ "$done" == "0" ]
do
  nowTime=$(date +%s)
  duration=$(($nowTime - $startTime))
  echo " Waiting time --> $duration sec"
  sleep 10
  done=1
  echo "checkDownloadRequest.py --files=$filesCheck --dataset=$dataset --book=$newBook"
  checkDownloadRequest.py --files=$filesCheck --dataset=$dataset --book=$newBook
  if [ "$?" == "0" ]
  then
    done=0
  fi
done

# Before exiting ensure fuse is synchronized to hadoop fs status
# check the first file of the fileset as it is the first to be processed
echo " INFO - File caching complete: waiting to ensure fuse synchronization with hadoop fs."
firstFile=`cat $newCatalogDir/$newBook/$dataset/Files | grep ^$fileset | head -1 | cut -d" " -f2`
firstFileCheck=0
fuseCheckStartTime=$(date +%s)
while [ "$firstFileCheck" == "0" ]
do
  nowTime=$(date +%s)
  duration=$(($nowTime - $fuseCheckStartTime))
  echo " Fuse check waiting time --> $duration sec"
  sleep 20
  if [ -e "$SMARTCACHE_DATA/$newBook/$dataset/$firstFile" ]
  then
    firstFileCheck=1
  fi
done

exit 0
