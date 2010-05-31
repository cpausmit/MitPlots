#!/bin/bash
# $Id: setup.sh,v 1.44 2010/05/29 18:09:17 bendavid Exp $

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

if test $version -lt 2002014; then
    echo "Version not supported, exiting";
    exit 1;
fi

if test $version -lt 3007000; then
        #Remove annoying warning messages for the jet to vertex associator.
        if ! test -d "JetMETCorrections/JetVertexAssociation"; then
            addpkg JetMETCorrections/JetVertexAssociation;
            TMP=`mktemp`;
            cat JetMETCorrections/JetVertexAssociation/src/JetVertexMain.cc | 
            sed -e 's/else  std::cout << \"\[Jets\] JetVertexAssociation: Warning\! problems for  Algo = 2: possible division by zero ..\" << std::endl;//' > $TMP;
            mv $TMP JetMETCorrections/JetVertexAssociation/src/JetVertexMain.cc
        fi

        if ! test -d "RecoVertex/GaussianSumVertexFit"; then
            addpkg RecoVertex/GaussianSumVertexFit;
            patch -p0 < MitAna/scripts/GSFFitPatch.patch 
        fi

        if ! test -d "RecoVertex/KalmanVertexFit"; then
            addpkg RecoVertex/KalmanVertexFit;
            patch -p0 < MitAna/scripts/KalmanFitPatch.patch 
        fi


        addpkg RecoEgamma/EgammaTools V00-05-03
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
        *) 
            echo "Nothing special to be done for this version";
        ;;
    esac
fi

echo "Setup done; you probably want to compile your project area now";
