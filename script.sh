#!/bin/bash
MINARGS=1
if [ $# -lt $MINARGS ]; then
	echo "Usage: sh script.sh 'flow-one' | 'flow-ten' | 'flow-thousand' | 'big' | 'big-superposition'"
	exit $E_NOARGS
fi
REQ_RESULTS=0
OWN_RESULTS=0
ARG=$1
i=1
while [ $i -le 100 ]
do
	./generator --$ARG > argFILE
	#TIME=$(time ./lem-in < argFILE > outFILE | awk '{print $6}'n | sed 's/.$//')
	./lem-in < argFILE > outFILE
	OUTNUM=$(wc -l "outFILE" | awk '{print $1}')
	ARGNUM=$(wc -l "argFILE" | awk '{print $1}')
	REQ=$(head -5 'argFILE' |  grep 'require' | awk '{print $8}')
	REQ_RESULTS=$(( $REQ_RESULTS + $REQ ))
	LINES_NUM=$(( $OUTNUM - $ARGNUM - 1 ))
	OWN_RESULTS=$(( $OWN_RESULTS + $LINES_NUM ))
	echo "req $REQ"
	echo "own $LINES_NUM"
	echo $TIME
	#if ($TIME > 3.00)
	#then
		#echo "$TIME s"
	#fi
	#if (( $LINES_NUM > $REQ + 20 ))
	#then
		#cp -rf outFILE outProblem
		#cp -rf argFILE inProblem
	#fi
	rm -rf outFILE
	rm -rf argFILE
	i=$(( $i + 1 ))
done
i=$(( $i - 1))
REQ_AVERAGE=$(( $REQ_RESULTS / $i))
OWN_AVERAGE=$(( $OWN_RESULTS / $i))
echo "Required average per $i tests: $REQ_AVERAGE"
echo "Our average per $i tests: $OWN_AVERAGE"
exit 0
