#!/bin/bash

#	This script runs every program in
#	the file "programlist" using 
#	every text file in the directory
#	and a key provided with 
#	command line arguments.
#	There may be some issues with 
#	escape characters and names.


if [ $# -eq 0 ]
then
  echo "Usage: $0 <key>"
  exit 2
fi
if [[ ! -f programlist ]]; then
  echo "Can't find programlist"
  exit 2
fi

PASSES=150

while read PGRM; do
  for TFILE in *.txt
  do
    TOTAL=0.0
	for i in $(seq 1 $PASSES)
      do
	    NAME=${TFILE%.txt}
	    EXE=${PGRM#*./}
	    cp $TFILE $TFILE.tmp
	    #strace -c -o"BENCH_${NAME}_$EXE.trace" -Ttt $PGRM $TFILE.tmp $1
	    ELAPSED=`strace -c -Ttt $PGRM $TFILE.tmp $1 2>&1 >/dev/null | tail -n1 | awk '{ print $2 }' RS='\t'`
	    rm $TFILE.tmp
        TOTAL=$(echo $TOTAL + $ELAPSED | bc)
      done
      echo TOTAL: $TOTAL AVG: $(echo "($TOTAL / $PASSES) * 1000000" | bc -l | sed s/[.].*//) us for $PGRM
  done
done <programlist
