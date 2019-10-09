#include <stdio.h>
#include <stdlib.h>
#include<pthread.h>
#include <infinite_sum_functions.h>
double pi_ret, cos_ret, eval_ret;

void *calc_pi(void *arg)
{
    pi_ret = pi();
    pthread_exit(&pi_ret);
}

void *calc_cos(void *arg)
{
    cos_ret = cosine(*((double *)arg));
    pthread_exit(&cos_ret);
}

void *calc_epow(void *arg)
{
    eval_ret = epow(*((double *)arg));
    pthread_exit(&eval_ret);
}

int main(int argc, char **argv)
{
     
    double x, pival, cosval, eval; 
    void *retval;
    pthread_t threads[3];

    if(argc != 2)
          USAGE_EXIT("invalid args\n");
    x = atof(argv[1]);
    
    if(x > 1.0 || x < 0.0)
          USAGE_EXIT("invalid args\n");
    
    
    if(pthread_create(&threads[0], NULL, calc_pi, NULL) != 0){
              perror("pthread_create");
              exit(-1);
    }
    if(pthread_create(&threads[1], NULL, calc_cos, &x) != 0){
              perror("pthread_create");
              exit(-1);
    }
    if(pthread_create(&threads[2], NULL, calc_epow, &x) != 0){
              perror("pthread_create");
              exit(-1);
    }
    
    if(pthread_join(threads[0], &retval) != 0){
              perror("pthread_join 1");
              exit(-1);
    } 
    pival = *((double *)retval);
    printf("%.5f\n", pival); 
    
    if(pthread_join(threads[1], &retval) != 0){
              perror("pthread_join 2");
              exit(-1);
    } 
    cosval = *((double *)retval);
    printf("%.5f\n", cosval); 
   
    if(pthread_join(threads[2], &retval) != 0){
              perror("pthread_join 3");
              exit(-1);
    }
    eval = *((double *)retval);
    printf("%.5f\n", eval); 

    printf("Function = %f\n", pival * cosval * cosval / eval);     
}
