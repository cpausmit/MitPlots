#!/bin/bash

hf=$1
sf=`dirname $hf`/`basename $hf .h`.cc
sf=`echo $sf | replace interface src`
strs="//------------------------------"
lnum=`grep -n $strs $hf | cut -d: -f1 | head -n2 | tail -n1`

if test -z $lnum; then
    echo "Did not find header description, exiting."
    exit 123;
fi


echo $lnum
head -n$lnum $hf > ${sf}.tmp
cat $sf | grep -v "// \$Id:" >> ${sf}.tmp
mv ${sf} ${sf}.keep
mv ${sf}.tmp $sf
exit 1;

maxlnum=`grep -n ClassImp $sf | cut -d: -f1`
f1num=`grep -n $strs $sf | cut -d: -f1 | head -n1 | tail -n1`
f2num=`grep -n $strs $sf | cut -d: -f1 | head -n2 | tail -n1`

if test -z $maxlnum; then
    echo "Did not find ClassImp in source file, exiting."
    exit 123;
fi

if test $maxlnum -gt 0; then
    maxlnum=`expr $maxlnum - 1`
fi

if test $f1num -gt 0; then
    f1num=`expr $f1num - 1`
fi
if test $f2num -gt 0; then
    f2num=`expr $f2num + 1`
fi

echo $maxlnum $f1num - $f2num

tlnum=`wc -l $sf`
echo test $tlnum
expr $tlnum - $lnum

if test $f1num -gt $maxlnum; then
    echo "->>>>>>>>>>>>>>>>>> $fnum"
    head -n$maxlnum $sf
    head -n$lnum $hf | grep -v "// \$Id:"
    tail -n$fnum $sf
else
    echo "dooo";
fi
