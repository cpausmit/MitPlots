#!/bin/bash
#===================================================================================================
# Script to move a given set of output to a new tag name.
#
#                                                                             Ch.Paus (Mar 13, 2014)
#===================================================================================================
TAG="$1"
NEW_TAG="$2"

# first we do the histogram output

cd $MIT_PROD_HIST
mv $TAG $NEW_TAG
cd -

cd $MIT_PROD_HIST/$NEW_TAG/merged
pwd
repfil $TAG $NEW_TAG spacing
cd -

cd $MIT_PROD_HIST/$NEW_TAG/$MIT_PROD_BOOK
for dir in `echo  ???/*`
do
  cd $dir
  pwd
  repfil $TAG $NEW_TAG spacing
  cd -
done

# next we do the log output

cd $MIT_PROD_LOGS
mv $TAG $NEW_TAG
cd -

cd $MIT_PROD_LOGS/$NEW_TAG/$MIT_PROD_BOOK
for dir in `echo  ???/*`
do
  cd $dir
  pwd
  repfil $TAG $NEW_TAG spacing
  cd -
done

exit 0
