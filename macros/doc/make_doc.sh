#!/bin/bash
# $Id: make_doc.sh,v 1.2 2009/07/17 04:45:21 loizides Exp $


XPATH="./MitAna//macros/doc"

cd $CMSSW_BASE/src
for i in MitCommon MitAna MitPhysics; do
    find ${i}/*/interface -iname "*.h" -exec $XPATH/addDesc.sh "{}" \;
done

cd $CMSSW_BASE/src/MitAna/macros/doc
root -n -b -q make_doc.C+

cd $CMSSW_BASE/src
for i in MitCommon MitAna MitPhysics; do
    find ${i}/*/interface -iname "*.h" -exec $XPATH/rmDesc.sh "{}" \;
done
