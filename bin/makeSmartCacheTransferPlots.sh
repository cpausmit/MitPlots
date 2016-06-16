#!/bin/bash

date

# setup CMSSW (MitPlots needs to be there)
source /cvmfs/cms.cern.ch/cmsset_default.sh
cd $HOME/cms/cmssw/040/CMSSW_7_4_0/src
eval `scram runtime -sh`
export EXTERNAL=/home/cmsprod/cms/external

# now we are ready to plot
source $HOME/MitRootStyle/setup.sh
cd $HOME/cms/root/

echo ""
echo " = = = =  T R A N S F E R   R A T E S  = = = ="
echo ""
root -l -b -q \
  $CMSSW_BASE/src/MitPlots/macros/plotSmartCacheTransferRate.C+
echo ""
echo " = = = =  F A I L U R E S  = = = ="
echo ""
root -l -b -q \
  $CMSSW_BASE/src/MitPlots/macros/plotSmartCacheFailures.C+
echo ""
echo " = = = =  R E Q U E S T S  = = = ="
echo ""
root -l -b -q \
  $CMSSW_BASE/src/MitPlots/macros/plotSmartCacheRequests.C+

# generate web page for the single machine performance

## missing for now

# move them into the foreseen place
echo ""
echo " = = = = M o v i n g   p l o t s   t o    t h e   w e b   p a g e  = = = ="
echo ""
mkdir -p $HOME/public_html/plots/

mv transferRateLast*.png $HOME/public_html/plots/

mv failuresLast*.png     $HOME/public_html/plots/

mv lagTime*.png          $HOME/public_html/plots/
mv downloadSpeed*.png    $HOME/public_html/plots/
mv t3btch*.png           $HOME/public_html/plots/

exit
