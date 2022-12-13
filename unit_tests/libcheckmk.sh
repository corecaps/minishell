#!/bin/sh
cd ./check-0.15.2
make distclean
./configure
make
make check
cd ..
cp $(find . -name 'libcheck.a') .
cp $(find . -name 'check.h') .


