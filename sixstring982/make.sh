#!/bin/bash

gcc -O99 -o ./barley-wine ./barley-wine.c
./barley-wine $1 $2
