#!/bin/bash

ARG=$1
./generator --$ARG > argFILE
./lem-in argFILE > outFILE
OUTNUM=$(wc -l "outFILE" | awk '{print $1}')
ARGNUM=$(wc -l "argFILE" | awk '{print $1}')
REQ=$((grep 'require' argFILE | awk '{print $8}') | awk '{print $1}')
echo $REQ
NUM=$(($OUTNUM - $ARGNUM - 1))
#cat "outFILE"
echo $NUM
rm -rf outFILE
rm -rf argFILE
