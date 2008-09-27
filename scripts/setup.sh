#!/bin/bash
# $Id: setup.sh,v 1.2 2008/09/17 19:27:05 sixie Exp $

if test -z $CMSSW_VERSION; then
    echo "Need cmssw project area setup!";
    exit 1;
fi

majver=`echo $CMSSW_VERSION | cut -d_ -f 2`;
minver=`echo $CMSSW_VERSION | cut -d_ -f 3`;
patver=`echo $CMSSW_VERSION | cut -d_ -f 4`;
majver=`expr $majver \* 10000`;
minver=`expr $minver \* 100`;
version=`expr $majver + $minver`;
version=`expr $version + $patver`;

echo "Setup called for $CMSSW_VERSION ($version)";

cd $CMSSW_BASE/src;

if test $version -lt 20108; then
    echo "Nothing to be done, exiting";
    exit 1;
elif test $version -eq 20108; then
    cvs co -r V01-06-02 CondFormats/JetMETObjects;
    cvs co -r V01-08-03 JetMETCorrections/Configuration;
    cvs co -r V02-09-00 JetMETCorrections/Modules;

    #to remove annoying Warning messages for the jet to vertex associator.
    cvs co JetMETCorrections/JetVertexAssociation;
    TMP=`mktemp`;
    cat JetMETCorrections/JetVertexAssociation/src/JetVertexMain.cc | 
    sed -e 's/else  std::cout << \"\[Jets\] JetVertexAssociation: Warning\! problems for  Algo = 2: possible division by zero ..\" << std::endl;//' > $TMP;
    mv $TMP JetMETCorrections/JetVertexAssociation/src/JetVertexMain.cc
else
    echo "Nothing known about this version, exiting";
    exit 1;
fi

echo "Setup done; you probably want to compile your project area now";
