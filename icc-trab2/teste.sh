#!/bin/bash                                                                                                                                                                                                                                   

ARQUIVO_ENTRADA="$1"
METRICA="FLOPS_DP"
CPU=3

LIKWID_HOME=/home/soft/likwid
CFLAGS="-I${LIKWID_HOME}/include -DLIKWID_PERFMON"
LFLAGS="-L${LIKWID_HOME}/lib -llikwid"

echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

gcc ${CFLAGS} main.c -o perfEG ${LFLAGS} "utils.c"
for k in $METRICA
do
    likwid-perfctr -C ${CPU} -g ${k} -m ./perfEG < ${ARQUIVO_ENTRADA} > ${k}_SemOtimiz.log
done

rm -f perfEG
gcc ${CFLAGS} -O3 main.c -o perfEG ${LFLAGS} "utils.c"
for k in $METRICA
do
    likwid-perfctr -C ${CPU} -g ${k} -m ./perfEG < ${ARQUIVO_ENTRADA} > ${k}_Otimiz.log
done

echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor
