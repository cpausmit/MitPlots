#!/bin/bash
# $Id: setup.sh,v 1.77 2011/10/22 15:08:08 bendavid Exp $

if test -z $CMSSW_VERSION; then
    echo "Need cmssw project area setup!";
    exit 1;
fi

if test -z "$CVSROOT"; then
    export CVSROOT=:pserver:anonymous@cmscvs.cern.ch:/cvs_server/repositories/CMSSW
    if test -z "`grep anonymous@cmscvs.cern.ch ~/.cvspass`"; then
        echo "You must have a valid cvs password for user anonymous@cmscvs.cern.ch"
        echo "The password (taken from the workbook) to be used in the next line is 98passwd"
        cvs login 
    fi
fi

majver=`echo $CMSSW_VERSION | cut -d_ -f 2`;
minver=`echo $CMSSW_VERSION | cut -d_ -f 3`;
patver=`echo $CMSSW_VERSION | cut -d_ -f 4`;
majver=`expr $majver \* 1000000`;
minver=`expr $minver \* 1000`;
version=`expr $majver + $minver`;
version=`expr $version + $patver`;

echo
echo "Setup called for $CMSSW_VERSION ($version)";
echo

cd $CMSSW_BASE/src;




if test $version -lt 4005000 -a $version -ge 4004000; then

  # add packages for clustered PFMET
  cvs co -r AlbertoAndPedro_Sep20_FastJetDevelopments -d RecoParticleFlow/PostProcessing UserCode/RecoParticleFlow/PostProcessing
  cvs co -r v11_09_28 -d CommonTools/ClusteredPFMetProducer UserCode/psilva/ClusteredPFMetProducer

  #patch silly bug...
  patch -p0 -u -N -i MitAna/scripts/ClusteredPFMetProducer.cc.patch -r /dev/null

  #regression and photonfix corrections
  cvs co -r regression_Oct11 HiggsAnalysis/HiggsToGammaGamma

  # RecoTauTag package with bug fix
  addpkg RecoTauTag/RecoTau V01-02-16
  addpkg RecoTauTag/Configuration V01-02-12

  #fix HitPattern accessor issue in 44x
  addpkg DataFormats/TrackReco
  patch -p0 -u -N -i MitAna/scripts/HitPattern.cc.patch -r /dev/null

  checkdeps -a
fi



case $version in
    (3003006) 
        ;;
    *) 
        #echo "Nothing known about this version, exiting";
        #exit 1;
    ;;
esac

if test -z $MIT_VERS; then
    echo
    echo "Warning: Production setup not executed since \$MIT_VERS is not setup."
    echo
else
    echo
    echo "Entering production setup. Looking for MIT_VERS: $MIT_VERS dependencies."
    echo
fi

echo "Setup done; you probably want to compile your project area now";
