#!/usr/bin/zsh

BIN=${1%%.*}
cython -3 --embed $1 -o $BIN.c
gcc -O2 -I /usr/include/python3.7m -o $BIN $BIN.c  -lpython3.7m -lpthread -lm -lutil -ldl
echo "$1 Compiled"
