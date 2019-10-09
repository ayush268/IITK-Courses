set term postscript eps enhanced monochrome 20 dashed dashlength 1 lw 1.5
#set terminal postscript eps enhanced color

set key samplen 2 spacing 1 font ",22"

set xtics font ",22"
set ytics font ",22"
set ylabel font ",25"
set xlabel font ",25"

#set format y "10^{%L}"
set xlabel "Random Sample"
set ylabel "EXP(10)"
set yrange[0:500]
set xrange[0:5000]
set ytic auto
set xtic auto


set output "exponential.eps"
set style circle radius 0.02
plot 'exponential.out' using 1:2 with circles lc rgb "blue"
