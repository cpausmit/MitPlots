#!/bin/bash
#---------------------------------------------------------------------------------------------------
# Download exactly one file, either interactively or submitting to condor batch system.
#
#                                                                             Ch.Paus (Nov 18, 2010)
#---------------------------------------------------------------------------------------------------
h=`basename $0`
echo " ";echo " ==== JOB ENVIRONMENT ==== ";echo " "; whoami;id;/bin/hostname;pwd
echo " ";echo " ==== START JOB WITH ARGUMENTS: $* ====";echo " "

LCGCP='lcg-cp'
SRMCP='srmcp'

id=`id -u`
cp ~/.krb5/x509up_u${id} /tmp/
cp ~/.krb5/krb5cc_${id}  /tmp/
ls -lhrt /tmp/krb5cc_${id}
export KRB5CCNAME=FILE:/tmp/krb5cc_${id}

dataFile=$1
target=$2
procId=$$

echo " DataFile: $dataFile  to: $target"

echo " "; echo "Initialize CMSSW"; echo " "
pwd
pwd=`pwd`

# legacy but works on 32 bit machines
if [ "`uname -p`" != "x86_64" ]
then
  source /afs/cern.ch/cms/LCG/LCG-2/UI/cms_ui_env_3_1.sh
else
  source /afs/cern.ch/cms/LCG/LCG-2/UI/cms_ui_env.sh
fi

# make storage Urls for target and source

targetUrl="file:///$target"   # target is always a local file
 
sourceUrl="file:///$dataFile" # start out with local file and adjust
if [ "`echo $dataFile | grep /mnt/hadoop/cms/store`" != "" ]
then
  storageEle="se01.cmsaf.mit.edu"
  storagePath='/srm/v2/server?SFN='
  sourceUrl="srm://${storageEle}:8443${storagePath}$dataFile"
elif [ "`echo $dataFile | grep /castor/cern.ch`" != "" ]
then
  storageEle='srm-cms.cern.ch'
  storagePath='/srm/managerv2?SFN='
  sourceUrl="srm://${storageEle}:8443${storagePath}$dataFile"
fi

echo " "; echo "Make directory"; echo " "
mkdir -p `dirname $target`
chmod ug+wx `dirname $target`

echo " "; echo "Starting download now"; echo " "
echo "$LCGCP -D srmv2 -b $sourceUrl $targetUrl.smartcache.$$"
$LCGCP -D srmv2 -b  $sourceUrl $targetUrl.smartcache.$$
if [ "$?" != "0" ]
then
  echo " ERROR ($h) - file copy failed for: $source/$file"
  exit 1
else
  echo " SUCCESS ($h) - copy worked."
fi 
mv $dataFile.smartcache.$$ $dataFile

exit 0
