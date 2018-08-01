#set terminal postscript eps enhanced color size 3.9,2.9
set term postscript eps enhanced monochrome 20 dashed dashlength 1 lw 1.5
set output "speedup.eps"

set key font ",22"
set xtics font ",22"
set ytics font ",22"
set ylabel font ",25"
set xlabel font ",25"
set xlabel "Workload"
set ylabel "Application speedup"
set yrange[0:]
set ytic auto
set boxwidth 1 relative
set style data histograms
set style histogram cluster
set style fill pattern border
plot 'speedup.out' u 2:xticlabels(1) title "Baseline",\
'' u 3 title "Policy(A)" fillstyle pattern 7,\
'' u 4 title "Policy(B)" fillstyle pattern 12,\
'' u 5 title "Policy(C)" fillstyle pattern 14

set terminal postscript eps enhanced color size 3.9,2.9
set output "speedup_color.eps"
plot 'speedup.out' u 2:xticlabels(1) title "Baseline",\
'' u 3 title "Policy(A)" fillstyle pattern 7,\
'' u 4 title "Policy(B)" fillstyle pattern 12,\
'' u 5 title "Policy(C)" fillstyle pattern 14

set term postscript eps enhanced monochrome 20 dashed dashlength 1 lw 1.5
set output "speedup_errorbar.eps"
set xtics rotate by -45
set style histogram errorbars lw 3
set style data histogram

plot 'speedup.out' u 2:6:xticlabels(1) title "Baseline",\
'' u 3:7 title "Policy(A)" fillstyle pattern 7,\
'' u 4:8 title "Policy(B)" fillstyle pattern 12,\
'' u 5:9 title "Policy(C)" fillstyle pattern 14
