#include<common.h>

static double function(double element)
{
    return (sqrt(element) * sin(element));
}

void* find_max(void *arg)
{
     struct thread_param *param = (struct thread_param *) arg;
     int ctr = param->thread_ctr;

     param->max = function(param->array[ctr]);
     param->max_index = ctr;
     ctr += param->skip;

     while(ctr < param->size){
           double x = function(param->array[ctr]);
           if(x > param->max){
                param->max = x;
                param->max_index = ctr;
           }
           ctr += param->skip;
     }          
     return NULL;
}
