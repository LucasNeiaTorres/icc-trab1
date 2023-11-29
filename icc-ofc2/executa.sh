#!/bin/bash                                                                                                                                                                                                                                   

ARQUIVO_ENTRADA="$1"
METRICA="FLOPS_DP L3 L2CACHE ENERGY"
CPU=3

ARRAY=(64 128 200 256 512 600 800 1024 2000 3000 4096 6000 7000 10000 50000 100000 1000000 10000000 100000000)

LIKWID_HOME=/home/soft/likwid
CFLAGS="-I${LIKWID_HOME}/include -DLIKWID_PERFMON"
LFLAGS="-L${LIKWID_HOME}/lib -llikwid"

echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

make purge
make

# for valor in "${ARRAY[@]}"
# do
#     ./gera_entrada $valor | ./ajustePol > aux.txt
#     cat aux.txt | grep -E 'geraTime|resolveTime|residuoTime'
# done


gcc -Wall gEntrada/gera_entrada.c -o gera_entrada 

#Para cada metrica
for k in $METRICA
do
	echo $k
	# Executa todos os valores de vetor
	for valor in "${ARRAY[@]}"
	do
		echo "Valor: $valor"
		./gera_entrada $valor | likwid-perfctr -C ${CPU} -g ${k} -m ./ajustePol > aux.txt

		LINHA1="${valor}"
		# Cada execução do matmult gera um arquivo LIKWID de 4 marcadores ( as 4 funções do programa )
		for i in 1 2 3
		do
			# FLOPS_DP tem que ser tratado diferente dos demais, dado que nesse marcador temos dois parâmetros de interesse
			if [ $k == "FLOPS_DP" ];then
				LINHA1="${LINHA1},$(cat aux.txt | grep -m $i -E "  DP MFLOP/s" | cut -d "|" -f 3 | tail -n 1 | bc),$(cat aux.txt | grep -m $i -E "AVX DP MFLOP/s" | cut -d "|" -f 3 | tail -n 1 | bc)"
            else
				LINHA1="${LINHA1},$(cat aux.txt | grep -m $i -E "L3 bandwidth \[MBytes/s\]|L2 miss ratio|Energy \[J\]" | cut -d "|" -f 3 | tail -n 1 | bc)"
			fi
		done
		# Por fim escreve no arquivo
		echo "${LINHA1}"
	done
done