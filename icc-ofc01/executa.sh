#!/bin/bash                                                                                                                                                                                                                                   

ARQUIVO_ENTRADA="$1"
METRICA="FLOPS_DP FLOPS_AVX ENERGY"
CPU=3

LIKWID_HOME=/home/soft/likwid
CFLAGS="-I${LIKWID_HOME}/include -DLIKWID_PERFMON"
LFLAGS="-L${LIKWID_HOME}/lib -llikwid"

echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

make
for k in $METRICA
do
    likwid-perfctr -C ${CPU} -g ${k} -m ./ajustePol < ${ARQUIVO_ENTRADA} > ${k}_SemOtimiz.log
done

rm -f ajustePol
make
for k in $METRICA
do
    likwid-perfctr -C ${CPU} -g ${k} -m ./ajustePol < ${ARQUIVO_ENTRADA} > ${k}_Otimiz.log
done

echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor
