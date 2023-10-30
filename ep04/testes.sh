#!/bin/bash                                                                                                                                                                                                                                   

METRICA="FLOPS_DP L3 L2CACHE ENERGY"
QNT_METRICAS=4
CPU=3

ARRAY=(64 100 128 200 256 512 600 900 1024 2000 2048 3000 4000)

echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

make purge
make

#Exclui os arquivos .dat existente
for k in $METRICA
do
     if [ -e ${k}.dat ];then
          rm ${k}.dat
     fi
done

#Para cada metrica
for k in $METRICA
do
	echo $k
	# Executa todos os valores de vetor
	for valor in "${ARRAY[@]}"
	do
		echo "Valor: $valor"
		likwid-perfctr -C ${CPU} -g "${k}" -m ./matmult $valor > aux.txt
		LINHA1="${valor}"

		# Cada execução do matmult gera um arquivo LIKWID de 4 marcadores ( as 4 funções do programa )
		for i in 1 2 3 4
		do
			# FLOPS_DP tem que ser tratado diferente dos demais, dado que nesse marcador temos dois parâmetros de interesse
			if [ $k == "FLOPS_DP" ];then
				LINHA1="${LINHA1},$(cat aux.txt | grep -m $i -E "  DP MFLOP/s" | cut -d "|" -f 3 | tail -n 1 | bc),$(cat aux.txt | grep -m $i -E "AVX DP MFLOP/s" | cut -d "|" -f 3 | tail -n 1 | bc)"
			else
				LINHA1="${LINHA1},$(cat aux.txt | grep -m $i -E "L3 bandwidth \[MBytes/s\]|L2 miss ratio|Energy \[J\]" | cut -d "|" -f 3 | tail -n 1 | bc)"
			fi
		done
		# Por fim escreve no arquivo
		echo "${LINHA1}" >> ${k}.dat
	done
done


echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor
