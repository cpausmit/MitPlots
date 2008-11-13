#!/bin/bash
# $Id: setup.sh,v 1.14 2008/11/12 22:21:17 loizides Exp $

if test -z $CMSSW_VERSION; then
    echo "Need cmssw project area setup!";
    exit 1;
fi

export CVSROOT=:pserver:anonymous@cmscvs.cern.ch:/cvs_server/repositories/CMSSW

majver=`echo $CMSSW_VERSION | cut -d_ -f 2`;
minver=`echo $CMSSW_VERSION | cut -d_ -f 3`;
patver=`echo $CMSSW_VERSION | cut -d_ -f 4`;
majver=`expr $majver \* 1000000`;
minver=`expr $minver \* 1000`;
version=`expr $majver + $minver`;
version=`expr $version + $patver`;

echo "Setup called for $CMSSW_VERSION ($version)";

cd $CMSSW_BASE/src;

if test $version -lt 2001008; then
    echo "Nothing to be done, exiting";
    exit 1;
fi

case $version in
       (2001008 | 2001009 | 2001010 | 2001011 | 2001012)
 
       cvs co -r V01-06-05 CondFormats/JetMETObjects;
       cvs co -r V01-08-10 JetMETCorrections/Configuration;
       cvs co -r V02-09-00 JetMETCorrections/Modules;

       #things related to JetsPlusTrack
       cvs co -r V01-07-11 JetMETCorrections/Algorithms
       cvs co -r V03-02-04 JetMETCorrections/JetPlusTrack
       #this is needed to do JetPlusTrack on AOD. we will not use this 
       #for now since we run on RECO for now
       #cvs co -r V01-04-03 RecoJets/JetAssociationAlgorithms       

       #to remove annoying warning messages for the jet to vertex associator.
       cvs co JetMETCorrections/JetVertexAssociation;
       TMP=`mktemp`;
       cat JetMETCorrections/JetVertexAssociation/src/JetVertexMain.cc | 
       sed -e 's/else  std::cout << \"\[Jets\] JetVertexAssociation: Warning\! problems for  Algo = 2: possible division by zero ..\" << std::endl;//' > $TMP;
       mv $TMP JetMETCorrections/JetVertexAssociation/src/JetVertexMain.cc

       #for jurassic isolation veto FIX. Note that this should be fixed
       #in the release at some point so this will be unnecessary then
       #and should be removed at that point in time.
       #These tags were suggested by Sam Harper
       if test $version -eq 2001011 -o $version -eq 2001012; then
           cvs co -rV00-02-00 RecoEgamma/EgammaIsolationAlgos
           cvs co -rV00-02-04 EgammaAnalysis/EgammaIsolationProducers
           cvs co -rV01-01-06 PhysicsTools/IsolationAlgos
           cvs co -rV00-16-07 DataFormats/RecoCandidate
           cvs co -rV00-05-19 RecoEcal/EgammaCoreTools

           #remove this file because it is causing python compile errors due to
           #incompatibilities of the tags...
           #we don't use this file anyways.
           rm RecoEgamma/EgammaIsolationAlgos/python/egammaIsolationSequence_cff.py
       fi

       ;;
    *) 
        echo "Nothing known about this version, exiting";
        exit 1;
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
        *) 
            echo "Nothing special to be done for this version";
        ;;
    esac
fi

echo "Setup done; you probably want to compile your project area now";
