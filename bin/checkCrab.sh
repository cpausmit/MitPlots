#!/bin/bash
#===================================================================================================
#
# Script to keep track of the present crab submissions active in our analysis area.
#
#                                                                             Ch.Paus (Apr 03, 2014)
#===================================================================================================
sleep=600
OPERATION="$1"
# setup relevant variables
logsDir=$MIT_PROD_LOGS/$MIT_PROD_CFG
globDir=$MIT_PROD_HIST/$MIT_PROD_CFG
# make a list of all our crab task directories
list=`echo $MIT_PROD_HIST/$MIT_PROD_CFG/crab_* 2> /dev/null`

if [ "$list" == "$MIT_PROD_HIST/$MIT_PROD_CFG/crab_"'*' ]
then
  echo " No crab tasks to check. EXIT!"
  exit 0
fi

# a little function to make our wait loud (seeing dots appear)
sleepLoud() {
  TOTAL_SLEEP=$1
  i=0
  while [ "$i" -le "$TOTAL_SLEEP" ]
  do
    echo -n "."
    sleep 6
    let "i += 6"
  done
}

# endless loop to stay on top of things
while [ 1 ]
do

  # loop through the directories we are monitoring
  for dir in $list
  do
    crabTask=`basename $dir`
    echo ""
    echo " ==== Check crab task: $crabTask  --> $OPERATION ===="
    echo ""

    if   [ "$OPERATION" == "status" ] || [ ".$OPERATION" == "." ]
    then
      # iterate crab status
      crab -status    -continue $dir
      crab -getoutput -continue $dir  
      # convert the output files to our usual condor output
      convertCrabOutput.sh $dir
    elif [ "$OPERATION" == "kill" ]
    then
      nJobs=`wc -l $dir/share/arguments.list | cut -d' ' -f1`
      crab -kill 1-${nJobs} -continue $dir
      rm   -rf                        $dir
    else
      echo " Operation: $OPERATION is unknown."
    fi
  done

  echo ""
  echo " ==== FINISHED ONE FULL CYCLE ===="
  echo ""
  echo "      --> sleep $sleep"
  sleepLoud $sleep

done
  
exit 0
