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
    /usr/bin/time -f%e ./sub_bench.sh $PASSES $PGRM $TFILE $1
  done
done <programlist
