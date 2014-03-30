#!/bin/bash
#---------------------------------------------------------------------------------------------------
# Execute one job fom inside the crab job. Will not work interactively!
#---------------------------------------------------------------------------------------------------
# Read argument
NJOB="$1"

# find the line to this dataset and do further analysis
echo ""
echo " START runCrab.sh $NJOB"
echo ""
echo " -=o=-.-=o=-.-=o=-.-=o=-.-=o=-.-=o=-.-=o=-.-=o=-.-=o=-.-=o=-.-=o=-.-=o=-.-=o=-.-=o=-.-=o=-";
echo " -=o=-.-=o=-.-=o=-.-=o=-.-=o=-.-=o=-.-=o=-.-=o=-.-=o=-.-=o=-.-=o=-.-=o=-.-=o=-.-=o=-.-=o=-";
echo ""

echo " make sure runCrabJob.sh is executable." 
echo ""
chmod 750 ./runCrabJob.sh

ls -lhrt

line=`sed -n ${NJOB}p arguments.list`
echo " Start running:  ./runCrabJob.sh $line "
./runCrabJob.sh $line
status="$?"

echo ""
echo " -=o=-.-=o=-.-=o=-.-=o=-.-=o=-.-=o=-.-=o=-.-=o=-.-=o=-.-=o=-.-=o=-.-=o=-.-=o=-.-=o=-.-=o=-";
echo " -=o=-.-=o=-.-=o=-.-=o=-.-=o=-.-=o=-.-=o=-.-=o=-.-=o=-.-=o=-.-=o=-.-=o=-.-=o=-.-=o=-.-=o=-";
echo ""
echo " END runCrab.sh"
echo ""
exit $status;
