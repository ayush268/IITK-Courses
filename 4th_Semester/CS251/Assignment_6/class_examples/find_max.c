#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<math.h>

#define USAGE_EXIT(s) do{ \
                             printf("Usage: %s <# of elements>\n %s\n", argv[0], s); \
                            exit(-1);\
                    }while(0);

#define TDIFF(start, end) ((end.tv_sec - start.tv_sec) * 1000000UL + (end.tv_usec - start.tv_usec))

double function(double element)
{
    return (sqrt(element) * sin(element));
}

int find_max(int *array, int size, double *maxval)
{
     int ctr, index;
     *maxval = function(array[0]);
     index = 0;
     for(ctr=1; ctr < size; ++ctr){
           double x = function(array[ctr]);
           if(x > *maxval){
                *maxval = x;
                index = ctr;
           }
     }          
     return index;
}

int main(int argc, char **argv)
{
  struct timeval start, end;
  int *a, num_elements, ctr;
  double max;
  if(argc !=2)
           USAGE_EXIT("not enough parameters");

  num_elements = atoi(argv[1]);
  if(num_elements <=0)
          USAGE_EXIT("invalid num elements");
  
  a = malloc(num_elements * sizeof(int));
  if(!a){
          USAGE_EXIT("invalid num elements, not enough memory");
  }
  
  for(ctr=0; ctr<num_elements; ++ctr)
        a[ctr] = random();
         
  gettimeofday(&start, NULL);

  ctr = find_max(a, num_elements, &max);
  printf("Max = %.2f for %d at index=%d\n", max, a[ctr], ctr);
  gettimeofday(&end, NULL);
  
  printf("Time taken = %ld microsecs\n", TDIFF(start, end));
  free(a);
}
