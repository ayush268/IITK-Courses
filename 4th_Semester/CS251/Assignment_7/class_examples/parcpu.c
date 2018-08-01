#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<string.h>
#include<pthread.h>
#include<math.h>


#define MAX_THREADS 64
#define USAGE_EXIT(s) do{ \
                             printf("Usage: %s <# of elements> <# of threads> \n %s\n", argv[0], s); \
                            exit(-1);\
                    }while(0);

#define TDIFF(start, end) ((end.tv_sec - start.tv_sec) * 1000000UL + (end.tv_usec - start.tv_usec))

struct num_array{
                    double num1;
                    double num2;
                    double result;
};

struct thread_param{
                       pthread_t tid;
                       struct num_array *array;
                       int size;
                       int skip;
                       int thread_ctr;
};


void function(struct num_array *a)
{
    double square = a->num1 * a->num1 +  a->num2 * a->num2  + 2 * a->num1 * a->num2;
    a->result = log(square)/sin(square);
    return;
}

void* thread_func(void *arg)
{
     struct thread_param *param = (struct thread_param *) arg;
     int ctr = param->thread_ctr;

     while(ctr < param->size){
           function(param->array + ctr);
           ctr += param->skip;
     }          
     return NULL;
}

int main(int argc, char **argv)
{
  void *params;
  struct timeval start, end;
  int num, ctr, num_threads;
  char *a, *ptr;
  struct num_array *pa;
  if(argc !=3)
           USAGE_EXIT("not enough parameters");

  num = atoi(argv[1]);
  if(num <=0)
          USAGE_EXIT("invalid num elements");
  
  num_threads = atoi(argv[2]);
  if(num_threads <=0 || num_threads > MAX_THREADS){
          USAGE_EXIT("invalid num of threads");
  }


  /* Parameters seems to be alright. Lets start our business*/

  ptr= malloc(num * 3 * sizeof(double));
  if(!ptr){
          USAGE_EXIT("invalid num elements, not enough memory");
  }

  a = ptr;
  for(ctr=0; ctr<num; ++ctr){
       pa = (struct num_array *) a;
       pa->num1 = (double) ctr + (double) ctr * 0.1;
       pa->num2 = pa->num1 + 1.0;
       a += 3 * sizeof(double);
   }


  /*Allocate thread specific parameters*/
  params = malloc(num_threads * sizeof(struct thread_param));
  bzero(params, num_threads * sizeof(struct thread_param));

  gettimeofday(&start, NULL);

  /*Partion data and create threads*/      
  for(ctr=0; ctr < num_threads; ++ctr){
        struct thread_param *param = ((struct thread_param *)params) + ctr;
        param->size = num;
        param->skip = num_threads;
        param->array = (struct num_array *) ptr;
        param->thread_ctr = ctr;
        
        if(pthread_create(&param->tid, NULL, thread_func, param) != 0){
              perror("pthread_create");
              exit(-1);
        }
 
  }
  
  /*Wait for threads to finish their execution*/      
  for(ctr=0; ctr < num_threads; ++ctr){
        struct thread_param *param = ((struct thread_param *)params) + ctr;
        pthread_join(param->tid, NULL);
  }
  
     
  pa = (struct num_array *) (ptr + (num -1)*3*sizeof(double));
  printf("num1=%f num2=%f result=%f\n", pa->num1, pa->num2, pa->result);
  gettimeofday(&end, NULL);
  printf("Time taken = %ld microsecs\n", TDIFF(start, end));

  free(ptr);
  free(params);
}
