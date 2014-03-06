#!/bin/bash
#---------------------------------------------------------------------------------------------------------------------
#
# When CMSSW is setup in the conor area the external libraries are also copied but need to be setup with scram so they
# appear in the right places for linking. We can assume that when this script this called CMSSW is already setup.
#
#                                                                                            C.Paus, V0 (Mar 05, 2014)
#---------------------------------------------------------------------------------------------------------------------

# go to the base area
cd $CMSSW_BASE/..

# Setup for fastjet
# -----------------

# move the old setup out of the way
mv $CMSSW_BASE/config/toolbox/$SCRAM_ARCH/tools/selected/fastjet.xml \
   $CMSSW_BASE/config/toolbox/$SCRAM_ARCH/tools/selected/fastjet.xml-last.$$

# define the extrnal area
EXTERNAL=`pwd`/external

# find out fastjest version
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

exit 0
