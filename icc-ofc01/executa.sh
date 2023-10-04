#!/bin/bash                                                                                                                                                                                                                                   

ARQUIVO_ENTRADA="$1"
METRICA="FLOPS_DP ENERGY"
CPU=3

LIKWID_HOME=/home/soft/likwid
CFLAGS="-I${LIKWID_HOME}/include -DLIKWID_PERFMON"
LFLAGS="-L${LIKWID_HOME}/lib -llikwid"

echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

make
for k in $METRICA
do
    likwid-perfctr -C ${CPU} -g ${k} -m ./ajustePol < ${ARQUIVO_ENTRADA} | grep '  DP MFLOP/s\| AVX DP MFLOP/s\| Energy \[J\]' 
done
