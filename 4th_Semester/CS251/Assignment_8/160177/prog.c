#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<string.h>

#include<common.h>

int main(int argc, char **argv)
{
  struct thread_param *params;
  struct timeval start, end;
  int *a, num_elements, ctr, num_threads;
  double max;
  int max_index;

  if(argc !=3)
           USAGE_EXIT("not enough parameters");

  num_elements = atoi(argv[1]);
  if(num_elements <=0)
          USAGE_EXIT("invalid num elements");
  
  num_threads = atoi(argv[2]);
  if(num_threads <=0 || num_threads > MAX_THREADS){
          USAGE_EXIT("invalid num of threads");
  }


  /* Parameters seems to be alright. Lets start our business*/

  a = malloc(num_elements * sizeof(int));
  if(!a){
          USAGE_EXIT("invalid num elements, not enough memory");
  }

  srand(SEED);  
  for(ctr=0; ctr<num_elements; ++ctr)
        a[ctr] = random();


  /*Allocate thread specific parameters*/
  params = malloc(num_threads * sizeof(struct thread_param));
  bzero(params, num_threads * sizeof(struct thread_param));

  gettimeofday(&start, NULL);

  /*Partion data and create threads*/      
  for(ctr=0; ctr < num_threads; ++ctr){
        struct thread_param *param = params + ctr;
        param->size = num_elements;
        param->skip = num_threads;
        param->array = a;
        param->thread_ctr = ctr;
        
        if(pthread_create(&param->tid, NULL, find_max, param) != 0){
              perror("pthread_create");
              exit(-1);
        }
 
  }
  
  /*Wait for threads to finish their execution*/      
  for(ctr=0; ctr < num_threads; ++ctr){
        struct thread_param *param = params + ctr;
        pthread_join(param->tid, NULL);
        if(ctr == 0 || (ctr > 0 && param->max > max)){
             max = param->max;    
             max_index = param->max_index;
        }
  }
     
//  printf("Max = %.2f for %d at index=%d\n", max, a[max_index], max_index);
  gettimeofday(&end, NULL);
  printf("Time taken = %ld microsecs\n", TDIFF(start, end));
  free(a);
  free(params);
}
