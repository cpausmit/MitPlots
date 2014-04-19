#!/bin/bash
#---------------------------------------------------------------------------------------------------
# Script to commit and push the existing Mit* packages in your present release. Please be careful
# that the repository is completely in sync once you start. Questions will be asked.
#
#                                                                         Ch.Paus (V0, Apr 18, 2014)
#---------------------------------------------------------------------------------------------------
n=`basename $0`
if [ -z "$1" ]
then
  echo ""
  echo " usage: $n <message-string>  (ex. Updating function blah to do foo.)"
  echo ""
  exit 1
else
  MESSAGE="$*"
fi

# make sure the release is setup
if [ -z "$CMSSW_BASE" ]
then
  echo ""
  echo " ERROR - There is no release setup (CMSSW_BASE = \"\")."
  echo ""
  exit 1
fi

# go to our release
cd $CMSSW_BASE/src

# make sure to cleanup backup files etc.
clean.sh backup-local

# find all packages we want to work on
dirs=`echo Mit*`

# say what we will do
echo ""
echo " Working on packages: $dirs"
echo " Message will be    : $MESSAGE"
echo ""

for dir in $dirs
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
    git commit -am "$MESSAGE"
    git push
    if [ "$?" != "0" ]
    then
      echo ""
      echo " ERROR - git push  in $dir failed. Please correct. EXIT!"
      echo ""
      exit 1
    fi
  fi

  # make sure to go back to where we started
  cd - >& /dev/null

done
