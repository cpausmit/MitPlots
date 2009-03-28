#!/bin/bash
# $Id: setup.sh,v 1.23 2009/03/25 10:04:03 loizides Exp $

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

echo "Setup called for $CMSSW_VERSION ($version)";

cd $CMSSW_BASE/src;

if test $version -lt 2002006; then
    echo "Nothing to be done, exiting";
    exit 1;
fi

case $version in
    (2002006 | 2002007) 
        #Remove annoying warning messages for the jet to vertex associator.
        cvs co -r $CMSSW_VERSION JetMETCorrections/JetVertexAssociation;
        TMP=`mktemp`;
        cat JetMETCorrections/JetVertexAssociation/src/JetVertexMain.cc | 
        sed -e 's/else  std::cout << \"\[Jets\] JetVertexAssociation: Warning\! problems for  Algo = 2: possible division by zero ..\" << std::endl;//' > $TMP;
        mv $TMP JetMETCorrections/JetVertexAssociation/src/JetVertexMain.cc
       
        #Tags required for Summer08 redigi-rereco and Winter09 FastSim JetMetCorrections
        cvs co -r V01-07-02 CondFormats/JetMETObjects
        cvs co -r V01-08-13 JetMETCorrections/Configuration
        cvs co -r V02-09-02 JetMETCorrections/Modules
        cvs co -r V01-08-00 JetMETCorrections/Algorithms
       
        #Tag needed for JetPlusTracks and associated corrections
        cvs co -r V01-04-03 RecoJets/JetAssociationAlgorithms
       
        #Tags for tcMet in 2_2_X
        cvs co -r V02-05-00-20 RecoMET/METAlgorithms
        cvs co -r V02-08-02-16 RecoMET/METProducers
        cvs co -r V00-04-02-16 RecoMET/Configuration
        cvs co -r V00-06-02-09 DataFormats/METReco 

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
