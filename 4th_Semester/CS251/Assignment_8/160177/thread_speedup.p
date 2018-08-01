set terminal postscript eps enhanced color size 3.9, 2.9

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
set style data histograms
set style histogram cluster
set style fill solid 0.3
set xtics rotate by -45

set output "thread_speedup.eps"
plot 'thread_speedup.out' u 2:xticlabels(1) title "1 Thread", \
     '' u 3 title "2 Threads", \
     '' u 4 title "4 Threads", \
     '' u 5 title "8 Threads", \
     '' u 6 title "16 Threads"
