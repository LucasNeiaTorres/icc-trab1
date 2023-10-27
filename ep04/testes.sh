#!/bin/bash                                                                                                                                                                                                                                   

METRICA="FLOPS_DP L3 CACHE ENERGY FLOPS_AVX"
CPU=3

echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

make
for k in $METRICA
do
    likwid-perfctr -C ${CPU} -g ${k} -m ./matmult 8 > ${k}.log # adicionar tamanhos de matriz de teste
done

echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor 