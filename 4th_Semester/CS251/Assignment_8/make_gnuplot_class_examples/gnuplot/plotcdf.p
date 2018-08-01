set term postscript eps enhanced monochrome 20 dashed dashlength 1 lw 1.5
#set terminal postscript eps enhanced color

set key samplen 2 spacing 1.5 font ",22"

set xtics font ",22"
set ytics font ",22"
set ylabel font ",25"
set xlabel font ",25"

set xlabel "X"
set ylabel "F(X)"
set yrange[0:1]
set xrange[0:500]
set ytic auto
set xtic auto

set output "expo_cdf.eps"
plot 'expo_cdf.out' using 1:2 notitle "Application 1" with line lt 5 lw 2 
#pt 3 ps 0.5
