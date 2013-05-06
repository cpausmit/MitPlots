#!/bin/bash
# $Id: setup.sh,v 1.84 2012/12/28 18:58:53 pharris Exp $

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

if test $version -lt 6000000 -a $version -ge 5002000; then
    cvs co -r V01-04-23 RecoTauTag/RecoTau
    cvs co -r V01-04-10 RecoTauTag/Configuration
    cvs co -r V00-04-00 CondFormats/EgammaObjects
    cvs co -r b5_3_x_analysis_2013Apr18 TauAnalysis/MCEmbeddingTools
fi

if test $version -lt 5004000 -a $version -ge 5003000; then
  addpkg RecoEcal/EgammaCoreTools  V05-08-20
  # not protected pointer of recHits (very often they are not there)
  patch  RecoEcal/EgammaCoreTools/src/EcalClusterLazyTools.cc MitAna/scripts/EcalClusterLazyTools.cc.patch
  addpkg RecoEgamma/EgammaTools    EcalLocalFix
  checkdeps -a
fi

if test $version -lt 5003000 -a $version -ge 5002000; then
  #support GBRForest for classification, and make compatible with GBRTrain
  addpkg CondFormats/EgammaObjects V00-04-00
  addpkg RecoEcal/EgammaCoreTools  V05-08-20
  addpkg RecoEgamma/EgammaTools    GlobePFDevPatch1
  checkdeps -a
fi

if test $version -lt 4005000 -a $version -ge 4004000; then

  # add packages for clustered PFMET
  cvs co -r AlbertoAndPedro_Sep20_FastJetDevelopments -d RecoParticleFlow/PostProcessing UserCode/RecoParticleFlow/PostProcessing
  cvs co -r v11_09_28 -d CommonTools/ClusteredPFMetProducer UserCode/psilva/ClusteredPFMetProducer

  #patch silly bug...
  patch -p0 -u -N -i MitAna/scripts/ClusteredPFMetProducer.cc.patch -r /dev/null

  #regression and photonfix corrections
  cvs co -r regression_Oct11 HiggsAnalysis/HiggsToGammaGamma

  # RecoTauTag package with bug fix
  addpkg RecoTauTag/RecoTau       V01-02-16
  addpkg RecoTauTag/Configuration V01-02-12

  # RecoTauTag package recommended for 2012
  addpkg DataFormats/TauReco    CMSSW_5_2_4 # yes, this is correct
  addpkg RecoTauTag/TauTagTools CMSSW_5_2_4
  cvs co -r V01-04-17 RecoTauTag/RecoTau
  cvs co -r V01-04-03 RecoTauTag/Configuration


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
