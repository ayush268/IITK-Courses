CC=         gcc
INCLUDE=    ./
CFLAGS=     -g -I$(INCLUDE) -lpthread -lm

OBJS=       thread_function.o prog.o
INFILES=    thread_1_scatter.out thread_2_scatter.out thread_4_scatter.out thread_8_scatter.out thread_16_scatter.out thread_lineplot.out thread_speedup.out thread_errorbars.out
PLOTS=      thread_1_scatter.eps thread_2_scatter.eps thread_4_scatter.eps thread_8_scatter.eps thread_16_scatter.eps thread_lineplot.eps thread_speedup.eps thread_errorbars.eps

default:
	$(error Usage: make <what to make>)

$(OBJS) : common.h
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

App: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

runtest: runtests.py App
	./$< > $@

$(INFILES) : analyse_results.py runtest
	./$<

analyse: runtest $(INFILES)

%.eps: %.p %.out
	gnuplot $<

plot: $(PLOTS)

report.pdf: report.tex $(PLOTS)
	pdflatex $<
	rm -f *.aux *.log

report: report.pdf

clean:
	rm -f *.o App runtest *.eps *.out *.pdf
