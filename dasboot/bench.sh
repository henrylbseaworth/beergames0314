#!/bin/bash

if [ $# -eq 0 ]
then
  echo "Usage: $0 <key>"
  exit 2
fi
if [[ ! -f programlist ]]; then
  echo "Can't find programlist"
  exit 2
fi

while read PGRM; do
  for TFILE in *.txt
  do
	  NAME=${TFILE%.txt}
	  EXE=${PGRM#*./}
	  cp $TFILE $TFILE.tmp
	  strace -c -o"BENCH_${NAME}_$EXE.trace" -Ttt $PGRM $TFILE.tmp $1
	  rm $TFILE.tmp
  done
done <programlist
