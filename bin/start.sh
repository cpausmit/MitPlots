#!/bin/bash

# Need this wrapper since system default python is 2.6 while 2.7 is used in CMSSW

BOOK=$1
DATASET=$2
FILESET=$3

WD=$PWD

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

eval $(cd $CMSSW_RELEASE; scram runtime -sh)

ls -l

#echo "python analysis.py --book=$BOOK --dataset=$DATASET --fileset=$FILESET --output=${FILESET}.root --libs=libs.list --pickle analysis.pkl"
#echo ""
#python analysis.py --book=$BOOK --dataset=$DATASET --fileset=$FILESET --output=${FILESET}.root --libs=libs.list --pickle analysis.pkl

echo "python analysis.py --book=$BOOK --dataset=$DATASET --fileset=$FILESET --output=${FILESET}.root analysisCfg.py"
echo ""
python analysis.py --book=$BOOK --dataset=$DATASET --fileset=$FILESET --output=${FILESET}.root --nentries=10 analysisCfg.py