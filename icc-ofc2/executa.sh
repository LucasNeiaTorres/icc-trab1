#!/bin/bash                                                                                                                                                                                                                                   

ARQUIVO_ENTRADA="$1"
METRICA="FLOPS_DP L3 L2CACHE ENERGY"
CPU=3

LIKWID_HOME=/home/soft/likwid
CFLAGS="-I${LIKWID_HOME}/include -DLIKWID_PERFMON"
LFLAGS="-L${LIKWID_HOME}/lib -llikwid"

echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

make purge
make


if [ -e "aux.txt" ]; then
    rm aux.txt
fi

for k in $METRICA
do
    likwid-perfctr -C ${CPU} -g ${k} -m ./ajustePol < ${ARQUIVO_ENTRADA} >> aux.txt
done

# cat aux.txt
# cat aux.txt | sed -n '6,9p'
cat aux.txt | grep -E '  DP MFLOP/s\ | AVX DP MFLOP/s\ | L3 bandwidth \[MBytes/s\] | L2 miss ratio | Energy \[J\]|geraTime|solTime'
rm aux.txt