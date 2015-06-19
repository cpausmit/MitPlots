#!/bin/bash
#----------------------------------------------------------------------------------------------------
#
# Make a tar ball that is up to date and can be used to start the analysis standalone on the worker.
# There are two tar balls relevant: the CMSSW one and the external one in case you have external
# packages like fastjet and contributions.
#
#----------------------------------------------------------------------------------------------------
if [ -z "$CMSSW_BASE" ]
then
  echo " Please setup CMSSW before trying to make a tar ball. EXIT!"
  exit 1
fi

workDir=`pwd`
echo "  Working directory: $workDir"

# Make the main CMSSW tar balls (split into external/libs and src)

cd $CMSSW_BASE
cd ..

if [ -e "${CMSSW_VERSION}.tgz" ]
then
  newer=`find $CMSSW_VERSION/{external,lib} -newer ./${CMSSW_VERSION}.tgz -print | tr '\n' ','`
else
  newer='${CMSSW_VERSION}.tgz does not exist.'
fi

if [ "$newer" != "" ]
then
  clean.sh backup-local
  clean.sh so-d
  echo "  Make new tar ball."
  echo "  found newer: $newer"
  echo "  -> tar fzc ${CMSSW_VERSION}.tgz $CMSSW_VERSION/{external,lib}"
  tar fzc ${CMSSW_VERSION}.tgz $CMSSW_VERSION/{external,lib}
else
  echo "  Tar ball ${CMSSW_VERSION}.tgz is up to date."  
fi

cp ${CMSSW_VERSION}.tgz $workDir

if [ -e "${CMSSW_VERSION}-src.tgz" ]
then
  newer=`find ${CMSSW_VERSION}/src -newer ./${CMSSW_VERSION}-src.tgz -print | tr '\n' ','`
else
  newer='${CMSSW_VERSION}-src.tgz does not exist.'
fi

if [ "$newer" != "" ]
then
  clean.sh backup-local
  clean.sh so-d
  echo "  Make new tar ball."
  echo "  found newer: $newer"
  echo "  -> tar fzc ${CMSSW_VERSION}-src.tgz $CMSSW_VERSION/src \
                     --exclude ${CMSSW_VERSION}/src/MitPhysics/data"
  tar fzc ${CMSSW_VERSION}-src.tgz $CMSSW_VERSION/src --exclude ${CMSSW_VERSION}/src/MitPhysics/data
else
  echo "  Tar ball ${CMSSW_VERSION}-src.tgz is up to date."  
fi

cp ${CMSSW_VERSION}-src.tgz $workDir

if [ $EXTERNAL != "/cvmfs/cvmfs.cmsaf.mit.edu/hidsk0001/cmsprod/cms/external" ]
then
  # Make the tar of our own external packages tar
  cd /home/cmsprod/cms
  
  if [ -e "$workDir/external.tgz" ]
  then
    newer=`find ./external -newer $workDir/external.tgz -print | tr '\n' ','`
  else
    newer="$workDir/external.tgz does not exist."
  fi
  
  if [ "$newer" != "" ]
  then
    echo "  Make new tar ball."
    echo "  found newer: $newer"
    echo "  -> tar fzc external.tgz external"
    tar fzc $workDir/external.tgz external
  else
    echo "  Tar ball $workDir/external.tgz is up to date."  
  fi
fi

# Make the tar of json files

cd /home/cmsprod/cms

if [ -e "$workDir/json.tgz" ]
then
  newer=`find ./json -newer $workDir/json.tgz -print | tr '\n' ','`
else
  newer="$workDir/json.tgz does not exist."
fi

if [ "$newer" != "" ]
then
  echo "  Make new tar ball."
  echo "  found newer: $newer"
  echo "  -> tar fzc json.tgz json"
  tar fzc $workDir/json.tgz json
else
  echo "  Tar ball $workDir/json.tgz is up to date."  
fi

exit 0
