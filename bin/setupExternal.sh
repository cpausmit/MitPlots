#!/bin/bash
#---------------------------------------------------------------------------------------------------------------------
#
# When CMSSW is setup in the condor area the external libraries are also copied but need to be setup with scram so
# they appear in the right places for linking. We can assume that when this script this called CMSSW is already setup.
#
#                                                                                            C.Paus, V0 (Mar 05, 2014)
#---------------------------------------------------------------------------------------------------------------------

# go to the base area
cd $CMSSW_BASE/..

# Setup for fastjet
# -----------------

# move the old setup out of the way
echo ' moving old config out of the way'
mv $CMSSW_BASE/config/toolbox/$SCRAM_ARCH/tools/selected/fastjet.xml \
   $CMSSW_BASE/config/toolbox/$SCRAM_ARCH/tools/selected/fastjet.xml-last.$$

# define the external area
EXTERNAL=`pwd`/external

# find out fastjet version
FASTJET_VER=`ls -1 $EXTERNAL | grep fastjet | tail -1 |cut -d '-' -f2`

# Generate fastjet file from modified template
echo \
'
  <tool name="fastjet" version="xx-VERSION-xx">
    <info url="http://www.lpthe.jussieu.fr/~salam/fastjet/"/>
    <lib name="fastjetplugins"/>
    <lib name="fastjettools"/>
    <lib name="siscone"/>
    <lib name="siscone_spherical"/>
    <lib name="fastjet"/>
    <lib name="fastjetcontrib"/>
    <client>
      <environment name="FASTJET_BASE" default="xx-PATH-xx"/>
      <environment name="LIBDIR" default="$FASTJET_BASE/lib"/>
      <environment name="INCLUDE" default="$FASTJET_BASE/include"/>
    </client>
  </tool>
' | sed "s/xx-VERSION-xx/$FASTJET_VER/"  | sed "s#xx-PATH-xx#$EXTERNAL#" \
  > $CMSSW_BASE/config/toolbox/$SCRAM_ARCH/tools/selected/fastjet.xml

# show the user what was created
cat $CMSSW_BASE/config/toolbox/$SCRAM_ARCH/tools/selected/fastjet.xml

# commit the scram config changes
cd $CMSSW_BASE/src
scram setup fastjet
cd -

# Setup for qjets
# -----------------

# move the old setup out of the way
echo ' moving old config out of the way'
mv $CMSSW_BASE/config/toolbox/$SCRAM_ARCH/tools/selected/qjets.xml \
   $CMSSW_BASE/config/toolbox/$SCRAM_ARCH/tools/selected/qjets.xml-last.$$

# Generate qjets file from modified template
echo \
'
  <tool name="qjets" version="2">
    <info url="http://jets.physics.harvard.edu/Qjets/html/Welcome.html"/>
    <lib name="qjets"/>
    <client>
      <environment name="QJETS_BASE" default="xx-PATH-xx/Qjets"/>
      <environment name="LIBDIR" default="$QJETS_BASE/lib"/>
      <environment name="INCLUDE" default="$QJETS_BASE"/>
    </client>
  </tool>
' | sed "s#xx-PATH-xx#$EXTERNAL#" \
> $CMSSW_BASE/config/toolbox/$SCRAM_ARCH/tools/selected/qjets.xml

# show the user what was created
cat $CMSSW_BASE/config/toolbox/$SCRAM_ARCH/tools/selected/qjets.xml

# commit the scram config changes
cd $CMSSW_BASE/src
scram setup qjets
cd -

exit 0
