#!/bin/bash
# $Id: setup-pixelLessTracking.sh,v 1.2 2008/10/21 07:22:07 paus Exp $

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
       (2001008 | 2001009 | 2001011)
        
       #updated four step iterative track reconstruction (includes pixel-less seeding)
       cvs co -r V00-03-00 RecoTracker/IterativeTracking
       cvs co -r V00-13-00 RecoTracker/FinalTrackSelectors

       ;;
    *) 
        echo "Nothing known about this version, exiting";
        exit 1;
    ;;
esac

echo "Setup for pixel less tracking done; you probably want to compile your project area now";
