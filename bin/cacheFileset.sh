#!/bin/bash
#---------------------------------------------------------------------------------------------------
# Execute one job (works interactively and when executed in condor)
#---------------------------------------------------------------------------------------------------
h=`basename $0`
# start waiting time now
startTime=$(date +%s)

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

# First make the filelist
files=""
for line in `cat $catalogDir/$book/$dataset/Files | grep ^$fileset`
do
  if [ "`echo $line | grep root`" != "" ]
  then
    files="$files $line"
  fi
done

# Enter the download requests into the database
for file in `echo $files`
do
  ~cmsprod/SmartCache/addDownloadRequest.py --file=$file --dataset=$dataset --book=$book
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
  for file in `echo $files`
  do
    ~cmsprod/SmartCache/checkDownloadRequest.py --file=$file --dataset=$dataset --book=$book
    if [ "$?" == "0" ]
    then
      done=0
      break
    fi
  done
done

exit 0
