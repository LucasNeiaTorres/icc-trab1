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
set xlabel  "N (bytes)"

#
# ALTERNATIVA 1: Tabelas em arquivos separados (2 colunas)
#
set key center center # posição da legenda: center, left, right
set datafile separator comma
set ylabel  "<metrica 1>"
set logscale x
set title   "<campo[marcador 1]>"
set terminal qt 0 title "<campo[marcador 1]>"
plot 'FLOPS_DP.dat' using 1:2 title "<sem otimização>" lc rgb "green" with linespoints, \
     '' using 1:3 "<com otimização>" lc rgb "blue" with linespoints, \

pause -1


