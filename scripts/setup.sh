#!/bin/bash
# $Id: setup.sh,v 1.5 2008/10/07 17:58:34 sixie Exp $

if test -z $CMSSW_VERSION; then
    echo "Need cmssw project area setup!";
    exit 1;
fi

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
       (2001008 | 2001009)
 
       cvs co -r V01-06-02 CondFormats/JetMETObjects;
       cvs co -r V01-08-03 JetMETCorrections/Configuration;
       cvs co -r V02-09-00 JetMETCorrections/Modules;

       #things related to Calo+track Jets
       cvs co -A JetMETCorrections/Configuration/data/CMSSW_167_TrackLeakage.txt
       cvs co -A JetMETCorrections/Configuration/data/CMSSW_167_TrackLeakage_one.txt
       cvs co -A JetMETCorrections/Configuration/data/CMSSW_167_TrackNonEff_one.txt
       cvs co -A JetMETCorrections/Configuration/data/CMSSW_167_response.txt
       cvs co -A JetMETCorrections/Configuration/python/JetPlusTrackCorrections_cff.py
       cvs co -r CMSSW_2_1_9 JetMETCorrections/JetPlusTrack
       cvs co -A JetMETCorrections/JetPlusTrack/BuildFile
       cvs co -A JetMETCorrections/JetPlusTrack/plugins/BuildFile
       cvs co -A JetMETCorrections/JetPlusTrack/test/JPTanalyzer_cfg.py
       cvs co -r CMSSW_2_1_9 JetMETCorrections/Algorithms
       cvs co -A JetMETCorrections/Algorithms/src/JetPlusTrackCorrector.cc
       cvs co -A JetMETCorrections/Algorithms/interface/JetPlusTrackCorrector.h
       cvs co -A JetMETCorrections/Algorithms/BuildFile
       

       #to remove annoying Warning messages for the jet to vertex associator.
       cvs co JetMETCorrections/JetVertexAssociation;
       TMP=`mktemp`;
       cat JetMETCorrections/JetVertexAssociation/src/JetVertexMain.cc | 
       sed -e 's/else  std::cout << \"\[Jets\] JetVertexAssociation: Warning\! problems for  Algo = 2: possible division by zero ..\" << std::endl;//' > $TMP;
       mv $TMP JetMETCorrections/JetVertexAssociation/src/JetVertexMain.cc
       ;;
    *) 
        echo "Nothing known about this version, exiting";
        exit 1;
    ;;
esac

if test -z $MIT_VERS; then
    echo " "
    echo "Production setup not executed: MIT_VERS is not setup."
    echo " "
else
    echo " "
    echo "Entering production setup. Looking for MIT_VERS: $MIT_VERS dependencies."
    echo " "
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
