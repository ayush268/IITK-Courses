#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <pthread.h>
#include <math.h>

#define SEED 0x7457

#define MAX_THREADS 64

#define ERROR(s) printf("%s \n Usage: %s <no. of elements> <no. of threads>\n", s, argv[0]); exit(-1);

#define TDIFF(start, end) ((end.tv_sec - start.tv_sec) * 1000000UL + (end.tv_usec - start.tv_usec))

typedef struct thread {
    pthread_t tid;
    int *arr;
    int max;
    int max_index;
    int limit;
    int interval;
} thr;

int isPrime(int val)
{
    if(val <= 1)
        return 0;
    if(val <= 3)
        return 1;
    if(val % 2 == 0 || val % 3 == 0)
        return 0;

    for(int i=5;i*i<=val;i+=6)
    {
        if(val % i == 0 || val % (i+2) == 0)
            return 0;
    }
}

int func(int val)
{
    if(isPrime(val))
        return val;
    return 0;
}

void* get_max(void *ptr)
{
    thr *thread = (thr *) ptr;
    int i;
    thread->max = 0;
    thread->max_index = -1;

    for(i=0;i<thread->limit;i+=thread->interval)
    {
        int val = func(thread->arr[i]);
        if(val > thread->max)
        {
            thread->max = val;
            thread->max_index = i;
        }
    }

    return NULL;
}

void main(int argc, char **argv)
{
    thr *threads;
    struct timeval start, end;
    int *arr, ptr, num_elements, num_threads;
    int max=0, max_index=-1;

    if(argc != 3)
    {
       ERROR("invalid number of parameters");
    }

    num_elements = atoi(argv[1]);
    if(num_elements <= 0)
    {
        ERROR("number of elements must be a positive integer");
    }

    num_threads = atoi(argv[2]);
    if(num_threads <= 0 || num_threads > MAX_THREADS)
    {
        ERROR("invalid number of threads");
    }

    arr = malloc(num_elements * sizeof(int));
    if(!arr)
    {
        ERROR("Invalid number of elements, memory is not enough");
    }

    srand(SEED);
    for(ptr=0; ptr<num_elements; ++ptr)
        arr[ptr] = random();

    threads = malloc(num_threads * sizeof(thr));
    bzero(threads, num_threads * sizeof(thr));

    gettimeofday(&start, NULL);

    for(ptr=0; ptr<num_threads; ++ptr)
    {
        thr *thread = threads + ptr;
        thread->limit = num_elements - ptr;
        thread->interval = num_threads;
        thread->arr = arr + ptr;

        if(pthread_create(&thread->tid, NULL, get_max, (void*) thread) != 0)
        {
            perror("pthread_create");
            exit(-1);
        }
    }

    for(ptr=0;ptr<num_threads;++ptr)
    {
        thr* thread = threads + ptr;
        pthread_join(thread->tid, NULL);
        if(ptr == 0 || (ptr > 0 && thread->max > max))
        {
            max = thread->max;
            max_index = thread->max_index;
        }
    }

    if(max==0)
        printf("The generated numbers DO NOT contain a prime number\n");
    else
        printf("Max prime = %d at index = %d\n", max, max_index);
    
    gettimeofday(&end, NULL);
    printf("Time taken = %ld microsecs\n", TDIFF(start, end));
    free(arr);
    free(threads);

}
