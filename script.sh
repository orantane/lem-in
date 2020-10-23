#!/bin/bash
MINARGS=1
if [ $# -lt $MINARGS ]; then
	echo "Usage: sh script.sh 'flow-one' | 'flow-ten' | 'flow-thousand' | 'big' | 'big-superposition'"
	exit $E_NOARGS
fi
REQ_RESULTS=0
OWN_RESULTS=0
ARG=$1
slow=0
i=0
while [ $i -lt 100 ]
do
	./generator --$ARG > argFILE
	(time -p ./lem-in < argFILE > outFILE) &> "timeFILE"
	TIME=$(grep real "timeFILE" | awk '{print $2}')
	OUTNUM=$(wc -l "outFILE" | awk '{print $1}')
	ARGNUM=$(wc -l "argFILE" | awk '{print $1}')
	REQ=$(head -5 'argFILE' |  grep 'require' | awk '{print $8}')
	REQ_RESULTS=$(( $REQ_RESULTS + $REQ ))
	LINES_NUM=$(( $OUTNUM - $ARGNUM - 1 ))
	OWN_RESULTS=$(( $OWN_RESULTS + $LINES_NUM ))
	echo "req $REQ"
	echo "own $LINES_NUM"
	#echo "Execution time $TIME"
	if (( $(echo "$TIME > 3.00" |bc -l) )); then
		slow=$(( $slow + 1 ))
	fi
	#if (( $LINES_NUM > $REQ + 20 ))
	#then
		#cp -rf outFILE outProblem
		#cp -rf argFILE inProblem
	#fi
	rm -rf timeFILE
	rm -rf outFILE
	rm -rf argFILE
	i=$(( $i + 1 ))
done
REQ_AVERAGE=$(( $REQ_RESULTS / $i))
OWN_AVERAGE=$(( $OWN_RESULTS / $i))
echo "Required average per $i tests: $REQ_AVERAGE"
echo "Our average per $i tests: $OWN_AVERAGE"
echo "$slow times over 3.00s"
exit 0
