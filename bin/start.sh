#!/bin/bash

# Need this wrapper since system default python is 2.6 while 2.7 is used in CMSSW

BOOK=$1
DATASET=$2
FILESET=$3
shift 3
JSONLIST="$@"

if ! [ -d /cvmfs/cms.cern.ch ] || ! [ -d /cvmfs/cvmfs.cmsaf.mit.edu ]
then
  echo "CVMFS not visible from "$(hostname)
  exit 1
fi

source /cvmfs/cms.cern.ch/cmsset_default.sh
source taskenv.sh

env

scram project CMSSW $CMSSW_RELEASE
tar xzf *.lib.tar.gz -C $CMSSW_RELEASE
tar xzf *.inc.tar.gz -C $CMSSW_RELEASE
# TEMPORARY
tar xzf *.python.tar.gz -C $CMSSW_RELEASE
# TEMPORARY
tar xzf *.MitAna-bin.tar.gz -C $CMSSW_RELEASE

mkdir catalog
tar xzf catalog.tar.gz -C catalog

export MIT_CATALOG=catalog
export MIT_DATA=/cvmfs/cvmfs.cmsaf.mit.edu/hidsk0001/cmsprod/cms/MitPhysics/data
export MIT_JSON_DIR=/cvmfs/cvmfs.cmsaf.mit.edu/hidsk0001/cmsprod/cms/json

export HOSTNAME=$(hostname)

echo $HOSTNAME

eval $(cd $CMSSW_RELEASE; scram runtime -sh)

ls -l

if [ "$JSONLIST" ]
then
  JSONARG="--goodlumi $JSONLIST"
fi

echo "python analysis.py analysisCfg.py --book=$BOOK --dataset=$DATASET --fileset=$FILESET --output=${FILESET}.root --nentries=-1 $JSONARG"
echo ""
python analysis.py analysisCfg.py --book=$BOOK --dataset=$DATASET --fileset=$FILESET --output=${FILESET}.root --nentries=-1 $JSONARG
