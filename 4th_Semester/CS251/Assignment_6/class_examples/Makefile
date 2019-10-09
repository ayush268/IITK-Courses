CC=gcc
CFLAGS=-I. -g
LDFLAGS=-lm -lpthread

all:max pmax mfunc pmfunc blockhash

max:find_max.c 
	$(CC) $(CFLAGS) find_max.c $(LDFLAGS) -o max 

pmax:find_max_p.c
	$(CC) $(CFLAGS) find_max_p.c $(LDFLAGS) -o pmax

mfunc:pi_cos2x_epwx.c infinite_sum_functions.c infinite_sum_functions.h
	$(CC) $(CFLAGS) infinite_sum_functions.c pi_cos2x_epwx.c -o mfunc

pmfunc:p_pi_cos2x_epwx.c infinite_sum_functions.c infinite_sum_functions.h
	$(CC) $(CFLAGS) infinite_sum_functions.c p_pi_cos2x_epwx.c $(LDFLAGS) -o pmfunc

blockhash:block_hash.c
	$(CC) $(CFLAGS) block_hash.c $(LDFLAGS) -o blockhash

clean:
	rm -f *.o max pmax mfunc pmfunc blockhash
	
