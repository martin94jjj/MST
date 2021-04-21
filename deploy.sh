#!/bin/bash

#for dimension in 0 2 3 4

for dimension in 0 2 3 4
do
    for N in 128 256 512 1024 2048 4096 8192 16384 32768 65536 131072 262144
    do
        ./randmst_heap 0 $N 10 $dimension > results/0_${N}_10_${dimension}.txt
        echo finishing 0_${N}_10_${dimension}
    done
done

