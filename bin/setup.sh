#!/bin/bash
#----------------------------------------------------------------------------------------------
# Setup the MitPlots package adjusting things that are needed for it to compile and run properly.
#
#                                                                   Apr 17, 2015 - V1 Y. Iiyama
#----------------------------------------------------------------------------------------------

echo "***********************"
echo " MitPlots/bin/setup.sh"
echo "***********************"

# Generate ROOT dictionaries for classes defined in this module
$CMSSW_BASE/src/MitCommon/bin/genDict.sh MitPlots/{Style,Input,Plot}

