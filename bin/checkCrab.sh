#!/bin/bash
#===================================================================================================
#
# Script to keep track of the present crab submissions active in our analysis area.
#
#                                                                             Ch.Paus (Apr 03, 2014)
#===================================================================================================
sleep=60
# setup relevant variables
logsDir=$MIT_PROD_LOGS/$MIT_PROD_CFG
globDir=$MIT_PROD_HIST/$MIT_PROD_CFG
# make a list of all our crab task directories
list=`echo $MIT_PROD_HIST/$MIT_PROD_CFG/crab_*`

# a little function to make our wait loud (seeing dots appear)
sleepLoud() {
  TOTAL_SLEEP=$1
  i=0
  while [ "$i" -le "$TOTAL_SLEEP" ]
  do
    echo -n "."
    sleep 4
    let "i += 4"
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
    echo " ==== Check crab task: $crabTask ===="
    echo ""
  
    # iterate crab status
    crab -status    -continue $dir
    crab -getoutput -continue $dir  

    # convert the output files to our usual condor output
    convertCrabOutput.sh $dir

  done

  
  echo ""
  echo " ==== FINISHED ONE FULL CYCLE ===="
  echo ""
  echo "      --> sleep $sleep"
  sleepLoud $sleep

done
  
exit 0
