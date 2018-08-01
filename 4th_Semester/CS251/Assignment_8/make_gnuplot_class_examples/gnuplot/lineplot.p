#set term postscript eps enhanced monochrome 20 dashed dashlength 1 lw 1.5
set terminal postscript eps enhanced color

set key samplen 2 spacing 1.5 font ",22"

set xtics font ",22"
set ytics font ",22"
set ylabel font ",25"
set xlabel font ",25"

set xlabel "Time (sec)"
set ylabel "Memory usage (MB)"
set yrange[0:750]
set xrange[0:2700]
set ytic auto
set xtic auto

set key bottom right

set output "musage_compare.eps"
plot 'usage.out' every 4 using 1:($2/256) title "Application 1" with linespoints, \
     '' every 4 using 1:($3/256) title "Application 2" with linespoints pt 5 lc 4,\
     '' every 4 using 1:($5/256) title "Application 3" with linespoints lc 3

set key top right
set output "musage_single_line.eps"
plot 'usage.out' using 1:($2/256) title "Application 1" with lines lw 2
