#!/bin/bash
#---------------------------------------------------------------------------------------------------
# Script to introduce a new tag. Please be careful that the repository is completely in sync once
# you start. Questions will be asked.
#
#                                                                         Ch.Paus (V0, Apr 18, 2014)
#---------------------------------------------------------------------------------------------------
n=`basename $0`
if [ -z "$1" ]
then
  echo ""
  echo " usage: $n <mit-tag>  (ex. Mit_034)"
  echo ""
  exit 1
else
  MIT_TAG="$1"
fi

# make sure the release is setup
if [ -z "$CMSSW_BASE" ]
then
  echo ""
  echo " ERROR - There is no release setup (CMSSW_BASE = \"\")."
  echo ""
  exit 1
fi

cd $CMSSW_BASE/src

DIRS=`echo Mit*`
echo " Working on packages: $DIRS"

for dir in $DIRS
do
  echo ""
  echo " Tagging package: $dir"

  # move into the package area
  cd  $dir

  # checking whether package is up-to-date
  git status

  read -p "Do you wish to continue? [N/y] " yn
  if [ "$yn" != "y" ] && [ "$yn" != "Y" ] 
  then
    echo " Nothing done. Moving to next package."
  else
    git tag  $MIT_TAG
    git remote set-url origin git@github.com:cpausmit/$dir
    git push origin --tags
  fi

  # make sure to go back to where we started
  cd - >& /dev/null

done
