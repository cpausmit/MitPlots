if [ -z $CMSSW_BASE ]
then
  echo ""
  echo " Setting up MitAna failed! (\$CMSSW_BASE is empty)."
  echo ""
else
  export MIT_DATA="$CMSSW_BASE/src/MitPhysics/data"
  export EXTERNAL="/home/cmsprod/cms/external"
  export MIT_ANA_DIR="$CMSSW_BASE/src/MitAna"
  export PATH="$MIT_ANA_DIR/bin:${PATH}"
  export PYTHONPATH="$MIT_ANA_DIR/python:${PYTHONPATH}"
fi
