#!/bin/bash
#---------------------------------------------------------------------------------------------------
# Copy a file in case the date on the source file is newer.
#---------------------------------------------------------------------------------------------------
if [ $# != 2 ]
then
  echo ""
  echo " Exactly two existing files are needed ($#)."
  echo ""
  exit 0
fi

# get arguments
FILE_1="$1"
FILE_2="$2"

# check whether they exist
if   [ -e "$FILE_1" ] && ! [ -e "$FILE_2" ]
then
    cp "$FILE_1" "$FILE_2"
elif [ -e "$FILE_1" ] && [ -e "$FILE_2" ]
then
  if test "$FILE_1" -nt "$FILE_2"
  then
    echo " Newer file ($FILE_1) found, copy now."
    cp "$FILE_1" "$FILE_2"
  else
    echo " File ($FILE_2) is already up to date."
  fi
else
  echo " ERROR - one of the files does not exist."
fi

exit 0
