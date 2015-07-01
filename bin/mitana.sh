if [ -z $CMSSW_BASE ]
then
  echo ""
  echo " Setting up MitAna failed! (\$CMSSW_BASE is empty)."
  echo ""
else
  export MIT_DATA="/cvmfs/cvmfs.cmsaf.mit.edu/hidsk0001/cmsprod/cms/MitPhysics/data"
  export EXTERNAL="/cvmfs/cvmfs.cmsaf.mit.edu/hidsk0001/cmsprod/cms/external"
  export MIT_ANA_DIR="$CMSSW_BASE/src/MitAna"
  export PATH="$MIT_ANA_DIR/bin:${PATH}"
fi
