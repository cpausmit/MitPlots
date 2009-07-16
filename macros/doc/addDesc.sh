#!/bin/bash
# $Id: addDesc.sh,v 1.2 2009/07/16 13:39:12 loizides Exp $

hf=$1

if test -z "`echo $hf | grep TAM/`"; then
    sf=`dirname $hf`/`basename $hf .h`.cc
    sf=`echo $sf | replace interface src`

    if ! test -e $sf; then
        echo "Did not find source file for ${hf}, exiting."
        exit 123;
    fi

    if test -e ${sf}.keep; then
        echo "Modified source file for ${hf} already exists, exiting."
        exit 123;
    fi

    strs="//------------------------------"
    lnum=`grep -n $strs $hf | cut -d: -f1 | head -n2 | tail -n1`

    if test -z $lnum; then
        echo "Did not find header description for ${hf}, exiting."
        exit 123;
    fi

    head -n$lnum $hf > ${sf}.tmp
    cat $sf | grep -v "// \$Id" >> ${sf}.tmp
    mv ${sf} ${sf}.keep
    mv ${sf}.tmp $sf
else
    sf=`dirname $hf`/`basename $hf .h`.cxx
    sf=`echo $sf | replace interface src`

    if ! test -e $sf; then
        echo "Did not find source file for ${hf}, exiting."
        exit 123;
    fi

    if test -e ${sf}.keep; then
        echo "Modified source file for ${hf} already exists, exiting."
        exit 123;
    fi

    cat $sf | replace "//////////////////////////////////////////////////////////////////////////" "//------------------------------------------------------------------------" > ${sf}.tmp
    mv ${sf} ${sf}.keep
    mv ${sf}.tmp $sf
fi
