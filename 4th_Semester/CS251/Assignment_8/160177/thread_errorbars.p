set key font ",12"
set key outside
set xtics font ",12"
set ytics font ",12"
set ylabel font ",15"
set xlabel font ",15"
set xlabel "Num of Elements"
set ylabel "Average Speedup"
set yrange[0:]
set ytic auto
set boxwidth 1 relative
set style histogram cluster
set style fill solid 0.3

set terminal postscript eps enhanced color size 3.9, 2.9
set style histogram errorbars lw 3 
set style data histogram
set xtics rotate by -45

set output "thread_errorbars.eps"
plot 'thread_errorbars.out' u 2:3:xticlabels(1) title "1 Thread", \
     '' u 4:5 title "2 Threads", \
     '' u 6:7 title "4 Threads", \
     '' u 8:9 title "8 Threads", \
     '' u 10:11 title "16 Threads"
