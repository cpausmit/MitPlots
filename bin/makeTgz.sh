#!/bin/bash
#----------------------------------------------------------------------------------------------------
#
# Make a tar ball that is up to date and can be used to start the analysis standalone on the worker.
# There are two tar balls relevant: the CMSSW one and the external one in case you have external
# packages like fastjet.
#
#----------------------------------------------------------------------------------------------------
if [ -z "$CMSSW_BASE" ]
then
  echo " Please setup CMSSW before trying to make a tar ball. EXIT!"
  exit 1
fi

workDir=`pwd`
echo "  Working directory: $workDir"

# Make the main CMSSW tar

cd $CMSSW_BASE
cd ..

if [ -e "${CMSSW_VERSION}.tgz" ]
then
  newer=`find $CMSSW_VERSION -newer ./${CMSSW_VERSION}.tgz -print | tr '\n' ','`
else
  newer='${CMSSW_VERSION}.tgz does not exist.'
fi

if [ "$newer" != "" ]
then
  echo "  Make new tar ball."
  echo "  found newer: $newer"
  echo "  -> tar fzc ${CMSSW_VERSION}.tgz -h $CMSSW_VERSION/external $CMSSW_VERSION/lib $CMSSW_VERSION/src/Mit* \
          --exclude ${CMSSW_VERSION}/src/MitPhysics/data"
  clean.sh backup-local
  clean.sh so-d
  tar fzc ${CMSSW_VERSION}.tgz -h ${CMSSW_VERSION}/external ${CMSSW_VERSION}/lib ${CMSSW_VERSION}/src/Mit* \
          --exclude ${CMSSW_VERSION}/src/MitPhysics/data
else
  echo "  Tar ball ${CMSSW_VERSION}.tgz is up to date."  
fi

cp ${CMSSW_VERSION}.tgz $workDir

# Make the tar of our own external packages tar

cd $HOME/cms

if [ -e "external.tgz" ]
then
  newer=`find ./external -newer ./external.tgz -print | tr '\n' ','`
else
  newer='external.tgz does not exist.'
fi

if [ "$newer" != "" ]
then
  echo "  Make new tar ball."
  echo "  found newer: $newer"
  echo "  -> tar fzc external.tgz -h external"
  clean.sh backup-local
  tar fzc external.tgz -h external
else
  echo "  Tar ball external.tgz is up to date."  
fi

cp external.tgz $workDir

exit 0
