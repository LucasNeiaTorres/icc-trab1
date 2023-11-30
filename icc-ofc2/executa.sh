#!/bin/bash                                                                                                                                                                                                                                   

ARQUIVO_ENTRADA="$1"
METRICA="FLOPS_DP L3 L2CACHE"
CPU=3

ARRAY=(64 128 200 256 512 600 800 1024 2000 3000 4096 6000 7000 10000 50000 100000 1000000 10000000 100000000)

LIKWID_HOME=/home/soft/likwid
CFLAGS="-I${LIKWID_HOME}/include -DLIKWID_PERFMON"
LFLAGS="-L${LIKWID_HOME}/lib -llikwid"

echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

# Compila ajustePol atual
make purge
make

# Compila ajustePol antigo
cd antigo
make purge
make
cd ..

gcc -Wall gEntrada/gera_entrada.c -o gera_entrada 


for k in $METRICA
do
     if [ -e ${k}_GERA.dat ];then
          rm ${k}_GERA.dat
     fi
done

for k in $METRICA
do
	 if [ -e ${k}_RESOLVE.dat ];then
		  rm ${k}_RESOLVE.dat
	 fi
done

for k in $METRICA
do
	 if [ -e ${k}_RESIDUO.dat ];then
		  rm ${k}_RESIDUO.dat
	 fi
done

if [ -e FLOPS_DP_GERA.dat ];then
	rm FLOPS_DP_GERA.dat
fi

if [ -e FLOPS_DP_RESOLVE.dat ];then
	rm FLOPS_DP_RESOLVE.dat
fi

if [ -e FLOPS_DP_RESIDUO.dat ];then
	rm FLOPS_DP_RESIDUO.dat
fi

if [ -e FLOPS_AVX_GERA.dat ];then
	rm FLOPS_AVX_GERA.dat
fi

if [ -e FLOPS_AVX_RESOLVE.dat ];then
	rm FLOPS_AVX_RESOLVE.dat
fi

if [ -e FLOPS_AVX_RESIDUO.dat ];then
	rm FLOPS_AVX_RESIDUO.dat
fi

if [ -e TEMPO_GERA.dat ];then
	rm TEMPO_GERA.dat
fi

if [ -e TEMPO_RESOLVE.dat ];then
	rm TEMPO_RESOLVE.dat
fi

if [ -e TEMPO_RESIDUO.dat ];then
	rm TEMPO_RESIDUO.dat
fi

for valor in "${ARRAY[@]}"
do
	echo "TEMPO"
	echo "Valor-> $valor"
    ./gera_entrada $valor | ./ajustePol > aux.txt
	./gera_entrada $valor | ./antigo/ajustePol > aux2.txt
	tGeraAtual=$(cat aux.txt | grep -E 'geraTime' | cut -d ":" -f 2)
	tGeraAntigo=$(cat aux2.txt | grep -E 'geraTime' | cut -d ":" -f 2)
	tResolveAtual=$(cat aux.txt | grep -E 'resolveTime' | cut -d ":" -f 2)
	tResolveAntigo=$(cat aux2.txt | grep -E 'resolveTime' | cut -d ":" -f 2)
	tResiduoAtual=$(cat aux.txt | grep -E 'residuoTime' | cut -d ":" -f 2)
	tResiduoAntigo=$(cat aux2.txt | grep -E 'residuoTime' | cut -d ":" -f 2)
	echo "${valor},${tGeraAtual},${tGeraAntigo}" >> TEMPO_GERA.dat
	echo "${valor},${tResolveAtual},${tResolveAntigo}" >> TEMPO_RESOLVE.dat
	echo "${valor},${tResiduoAtual},${tResiduoAntigo}" >> TEMPO_RESIDUO.dat

done


#Para cada metrica
for k in $METRICA
do
	echo $k
	# Executa todos os valores de vetor
	for valor in "${ARRAY[@]}"
	do
		echo "Valor-> $valor"
		./gera_entrada $valor | likwid-perfctr -C ${CPU} -g ${k} -m ./ajustePol > aux.txt
		./gera_entrada $valor | likwid-perfctr -C ${CPU} -g ${k} -m ./antigo/ajustePol > aux2.txt

		LINHA1="${valor}"

		# Cada execução do matmult gera um arquivo LIKWID de 4 marcadores ( as 4 funções do programa )
		for i in 1 2 3
		do
			# FLOPS_DP tem que ser tratado diferente dos demais, dado que nesse marcador temos dois parâmetros de interesse
			if [ $k == "FLOPS_DP" ];then
				FLOPS_DP="$(cat aux.txt | grep -m $i -E "  DP MFLOP/s" | cut -d "|" -f 3 | tail -n 1 | bc)"
				FLOPS_AVX="$(cat aux.txt | grep -m $i -E "AVX DP MFLOP/s" | cut -d "|" -f 3 | tail -n 1 | bc)"

				FLOPS_DP="${FLOPS_DP},$(cat aux2.txt | grep -m $i -E "  DP MFLOP/s" | cut -d "|" -f 3 | tail -n 1 | bc)"
				FLOPS_AVX="${FLOPS_AVX},$(cat aux2.txt | grep -m $i -E "AVX DP MFLOP/s" | cut -d "|" -f 3 | tail -n 1 | bc)"

				if [ $i == 1 ];then
					echo "${valor},${FLOPS_DP}" >> FLOPS_DP_GERA.dat
					echo "${valor},${FLOPS_AVX}" >> FLOPS_AVX_GERA.dat
				elif [ $i == 2 ];then
					echo "${valor},${FLOPS_DP}" >> FLOPS_DP_RESOLVE.dat
					echo "${valor},${FLOPS_AVX}" >> FLOPS_AVX_RESOLVE.dat
				else
					echo "${valor},${FLOPS_DP}" >> FLOPS_DP_RESIDUO.dat
					echo "${valor},${FLOPS_AVX}" >> FLOPS_AVX_RESIDUO.dat
				fi

			else
				LINHA1="$(cat aux.txt | grep -m $i -E "L3 bandwidth \[MBytes/s\]|L2 miss ratio|Energy \[J\]" | cut -d "|" -f 3 | tail -n 1 | bc)"
				LINHA1="${LINHA1},$(cat aux2.txt | grep -m $i -E "L3 bandwidth \[MBytes/s\]|L2 miss ratio|Energy \[J\]" | cut -d "|" -f 3 | tail -n 1 | bc)"

				if [ $i == 1 ];then
					echo "${valor},${LINHA1}" >> ${k}_GERA.dat
				elif [ $i == 2 ];then
					echo "${valor},${LINHA1}" >> ${k}_RESOLVE.dat
				else
					echo "${valor},${LINHA1}" >> ${k}_RESIDUO.dat
				fi
			fi
		done
	done
done