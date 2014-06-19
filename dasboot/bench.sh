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

for TFILE in *.txt
do
  cp $TFILE $TFILE.tmp
  while read PGRM; do
	  NAME=${TFILE%.txt}
	  EXE=${PGRM#*./}
	  #strace -c -o"BENCH_${NAME}_$EXE.trace" -Ttt $PGRM $TFILE.tmp $1
		(time $PGRM $TFILE.tmp $1) &> output_${NAME}_$EXE.log
  done <programlist
  rm $TFILE.tmp
done
