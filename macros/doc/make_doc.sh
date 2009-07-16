#!/bin/bash
# $Id: rmDesc.sh,v 1.1 2009/07/16 13:39:12 loizides Exp $


XPATH="./MitAna//macros/doc"

cd $CMSSW_BASE/src
for i in MitCommon MitAna MitPhysics; do
    find ${i}/*/interface -iname "*.h" -exec $XPATH/addDesc.sh "{}" \;
done
exit 1;
cd $CMSSW_BASE/src/MitAna/macros/doc
root -b -q make_doc.C+

cd $CMSSW_BASE/src
for i in MitCommon MitAna MitPhysics; do
    find ${i}/*/interface -iname "*.h" -exec $XPATH/rmDesc.sh "{}" \;
done
