#!/bin/sh
gawk -v key="$2" -f chicken.awk < $1 > chicken.out
mv chicken.out $1

