#!/bin/bash

date

# setup CMSSW (MitPlots needs to be there)
source /cvmfs/cms.cern.ch/cmsset_default.sh
cd $HOME/cms/cmssw/033/CMSSW_5_3_14_patch2/src
eval `scram runtime -sh`
export EXTERNAL=/home/cmsprod/cms/external

# now we are ready to plot
cd $HOME/cms/root/
root -l -b -q $HOME/cms/cmssw/033/CMSSW_5_3_14_patch2/src/MitPlots/macros/plotSmartCacheTransferRate.C+
root -l -b -q $HOME/cms/cmssw/033/CMSSW_5_3_14_patch2/src/MitPlots/macros/plotSmartCacheFailures.C+

#ls -l 

# move them into the foreseen place
echo " Moving plots to the web page."
mkdir -p $HOME/public_html/plots/
mv transferRateLast*.png $HOME/public_html/plots/
mv failuresLast*.png     $HOME/public_html/plots/

exit
