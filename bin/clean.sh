#!/bin/bash
#----------------------------------------------------------------------------------------------------
# Script to cleanup certain files that follow certain patterns like backup file or core files shared
# libraries and dependenciy file generated from the root compiler (AClibC).
#
#                                                                            C.Paus V0 (Mar 05, 2014)
#----------------------------------------------------------------------------------------------------

if [ ".$1" == ".backup" ]
then
  find $HOME \( -name \*.~\*~ -o -name \*~ -o -name \*.bak -o \
                -name .\*.~\*~ -o -name .\*~ -o -name .\*.bak \) \
       -exec ls -s {} \; -exec rm {} \;
elif [ ".$1" == ".backup-local" ]
then
  find ./    \( -name \*.~\*~ -o -name \*~ -o -name \*.bak -o \
                -name .\*.~\*~ -o -name .\*~ -o -name .\*.bak \) \
       -exec ls -s {} \; -exec rm {} \;
elif [ ".$1" == ".so-d" ]
then
  find ./    \( -name \*_C.so -o -name \*~ -o -name \*_C.d \) \
       -exec ls -s {} \; -exec rm {} \;
elif [ ".$1" == ".core" ]
then
  find $HOME -type f \( -name core -o -name core.\[0-9\]\* \) \
       -exec ls -s {} \; -exec rm {} \;
elif [ ".$1" == ".tex" ]
then
  find $HOME/tex $HOME/teaching -type f \( -name \*.aux -o -name \*~ -o -name \*.dvi -o -name \*.log \) \
       -exec ls -s {} \; -exec rm {} \;
else
  echo ERROR - unknown request: \"$1\"
fi

exit 0
