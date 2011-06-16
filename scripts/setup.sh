#!/bin/bash
# $Id: setup.sh,v 1.64 2011/06/16 11:46:44 rwolf Exp $

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

if test $version -lt 4003000 -a $version -ge 4002000; then
  #tau id and svfit
  addpkg TauAnalysis/CandidateTools b4_1_x_2011Apr25 
  cvs up -r 1.16 TauAnalysis/CandidateTools/python/nSVfitAlgorithmDiTau_cfi.py
  addpkg AnalysisDataFormats/TauAnalysis b4_1_x_2011Apr25
  addpkg RecoTauTag/RecoTau V01-00-33-06

  #deterministic rho computation
  addpkg RecoJets/Configuration V02-04-16

  checkdeps -a
fi

if test $version -lt 4002000; then
  #tau id and svfit
  addpkg RecoJets/Configuration V02-04-16
  addpkg RecoJets/JetAlgorithms V04-01-00
  addpkg RecoJets/JetProducers V05-05-03-00

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
    case $MIT_VERS in
        005)
            MitAna/scripts/setup-pixelLessTracking.sh
        ;;
	022)
	echo "Checkout additional tags for nSVfit. Status 11/06/13"
	# latest PhysicsTools patches for tauID
	cvs co -r V06-04-16 DataFormats/PatCandidates
	cvs co -r V08-06-34 PhysicsTools/PatAlgos
	cvs co -r V00-06-06 PhysicsTools/MVAComputer
	# latest RecoTauTag patches for tauID
	cvs co -r V01-02-00 RecoTauTag/Configuration
	cvs co -r V01-02-00 RecoTauTag/RecoTau
	cvs co -r V01-02-00 RecoTauTag/TauTagTools 
	# and finally latest svfit developments
	cvs co -r b4_2_x_2011Jun13 AnalysisDataFormats/TauAnalysis
	cvs co -r b4_2_x_2011Jun13 TauAnalysis/CandidateTools
        *) 
	echo "Nothing special to be done for this version";
        ;;
    esac
fi

echo "Setup done; you probably want to compile your project area now";
