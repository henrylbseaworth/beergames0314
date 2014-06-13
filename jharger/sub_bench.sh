#!/bin/bash

PASSES=$1

for i in $(seq 1 $PASSES)
  do
    cp $3 $3.tmp
    $2 $3.tmp $4 > /dev/null
    rm $3.tmp
done

