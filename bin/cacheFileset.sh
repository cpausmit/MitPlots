#!/bin/bash
#---------------------------------------------------------------------------------------------------
# Execute one job (works interactively and when executed in condor)
#---------------------------------------------------------------------------------------------------
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

# Enter the download requests into the database
for file in `echo $files`
do
  echo " Testing: $SMARTCACHE_DATA/$newBook/$dataset/$file"

  if [ -e "$SMARTCACHE_DATA/$newBook/$dataset/$file" ]
  then
    echo " File: $newBook/$dataset/$file already available."
  else
    addDownloadRequest.py --file=$file --dataset=$dataset --book=$newBook
  fi
done

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

exit 0
