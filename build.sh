#!/bin/sh

RAGEL=`which ragel`
CC='gcc'

$RAGEL -I ./ragel ./ragel/rfc3986_c.rl -o ./build/rfc3986_c.c
$CC -fPIC -c ./build/rfc3986_c.c -o ./build/rfc3986_c.o

dmd @build.rf
