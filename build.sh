#!/bin/bash
mkdir -p obj && cd obj || (echo "Error creating directory" >&2 && exit -1)

rm *.o
clang -c ../src/*.c ../src/linux/*.c && \
clang -lm *.o -o ../bin/vm
