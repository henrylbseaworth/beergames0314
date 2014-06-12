#!/bin/bash
if [ $# -eq 0 ]
then
  echo "Usage: $0 <program> <key>"
  exit 2
fi
if [[ ! -f programlist ]]; then
  echo "Can't find programlist"
  exit 2
fi

while read p; do

  for fs in *.txt
  do
	  NAME=${fs%.txt}
	  EXE=${1#*./}
	  cp $fs $fs.tmp
	  strace -c -o"BENCH_${NAME}_$EXE.d" -Ttt $1 $fs.tmp $2
	  rm $fs.tmp
  done
done <programlist
