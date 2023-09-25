#!/bin/bash                                                                                                                                                                                                                                   

PONTO_ENTRADA="$1"
ARQUIVO_ENTRADA="$2"
METRICA="FLOPS_DP"
CPU=3

LIKWID_HOME=/home/soft/likwid
CFLAGS="-I${LIKWID_HOME}/include -DLIKWID_PERFMON"
LFLAGS="-L${LIKWID_HOME}/lib -llikwid"
LOCAL_LIBS="utils.c interpolacao.c auxiliar.c"

echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

gcc ${CFLAGS} main.c -o interpola ${LFLAGS} ${LOCAL_LIBS}
for k in $METRICA
do
    likwid-perfctr -C ${CPU} -g ${k} -m ./interpola  ${PONTO_ENTRADA} < ${ARQUIVO_ENTRADA} > ${k}_SemOtimiz.log
done

rm -f interpola
gcc ${CFLAGS} -O3 main.c -o interpola ${LFLAGS} ${LOCAL_LIBS}
for k in $METRICA
do
    likwid-perfctr -C ${CPU} -g ${k} -m ./interpola ${PONTO_ENTRADA} < ${ARQUIVO_ENTRADA} > ${k}_Otimiz.log
done

echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor
