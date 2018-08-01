#ifndef __COMMON_H_
#define __COMMON_H_

#include<pthread.h>
#include<math.h>

#define SEED 0x7457

#define MAX_THREADS 64
#define USAGE_EXIT(s) do{ \
                             printf("Usage: %s <# of elements> <# of threads> \n %s\n", argv[0], s); \
                            exit(-1);\
                    }while(0);

#define TDIFF(start, end) ((end.tv_sec - start.tv_sec) * 1000000UL + (end.tv_usec - start.tv_usec))

struct thread_param{
                       pthread_t tid;
                       int *array;
                       int size;
                       int skip;
                       int thread_ctr;
                       double max;  
                       int max_index;
};

extern void * find_max (void *arg);

#endif
