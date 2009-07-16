#!/bin/bash
# $Id:$

hf=$1
sf=`dirname $hf`/`basename $hf .h`.cc
sf=`echo $sf | replace interface src`

if ! test -e $sf; then
    echo "Did not find source file for ${hf}, exiting."
    exit 123;
fi

if test -e ${sf}.keep; then
    mv ${sf}.keep ${sf}
fi
