set terminal postscript eps enhanced color

set key samplen 2 spacing 1 font ",12"

set xtics font ",12"
set ytics font ",12"
set ylabel font ",15"
set xlabel font ",15"

set xlabel "Num of Elements"
set ylabel "Execution Time"
set yrange[:]
set xrange[:]
set logscale x 10
set logscale y 10
set format x "10^{%L}"
set format y "10^{%L}"
set ytic auto
set xtic auto

set output "thread_8_scatter.eps"
set title "8 Threads"
plot 'thread_8_scatter.out' using 1:2 notitle with p pt 7
