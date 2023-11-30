#!/usr/bin/gnuplot -c

## set encoding iso_8859_15
set encoding utf

# set terminal qt persist

set grid

set style data point
set style function line
set style line 1 lc 3 pt 7 ps 0.3
set boxwidth 1
set xtics
# set xrange [0:]
set xlabel  "N (tamanho matriz)"


# ALTERNATIVA 2: Tabela com 3 colunas 
#
set key outside right # posição da legenda: outside {left | right}
set logscale x 10
set logscale y 10
set datafile separator whitespace
set ylabel  "FLOPS DP"
set title   "Quantidade FLOPS DP para resolver SL"
set terminal qt 1 title "Quantidade FLOPS DP para resolver SL"
set datafile separator ","
plot 'FLOPS_DP_RESOLVE.dat' using 1:2 title "<com otimização>" lc rgb "green" with linespoints, \
     '' using 1:3 title "<sem otimização>" lc rgb "blue" with linespoints

pause -1


# Gerando figura PNG
set terminal png
set output "FLOPS_DP_RESOLVE.png"
plot 'FLOPS_DP_RESOLVE.dat' using 1:2 title "<com otimização>" lc rgb "green" with linespoints, \
     '' using 1:3 title "<sem otimização>" lc rgb "blue" with linespoints

replot
unset output