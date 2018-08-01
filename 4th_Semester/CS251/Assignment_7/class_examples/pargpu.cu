#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>

#define NUM 10000000

#define CUDA_ERROR_EXIT(str) do{\
                                    cudaError err = cudaGetLastError();\
                                    if( err != cudaSuccess){\
                                             printf("Cuda Error: '%s' for %s\n", cudaGetErrorString(err), str);\
                                             exit(-1);\
                                    }\
                             }while(0);
#define TDIFF(start, end) ((end.tv_sec - start.tv_sec) * 1000000UL + (end.tv_usec - start.tv_usec))

struct num_array
{
                    double num1;
                    double num2;
                    double result;
};



__device__ void function(struct num_array *a)
{
    double square = a ->num1 * a->num1 +  a->num2 * a->num2  + 2 * a->num1 * a->num2;
    a->result = log(square)/sin(square);
    return;
}
__global__ void calculate(char *mem, int num)
{
      int i = blockDim.x * blockIdx.x + threadIdx.x;
      if(i >= num)
           return;
       struct num_array *a = (struct num_array *)(mem + (i * 3 * sizeof(double)));
      function(a);
}

int main(int argc, char **argv)
{
    struct timeval start, end, t_start, t_end;
    int i;
    struct num_array *pa;
    char *ptr;
    char *sptr;
    char *gpu_mem;   
    unsigned long num = NUM;   /*Default value of num from MACRO*/
    int blocks;

    if(argc == 2){
         num = atoi(argv[1]);   /*Update after checking*/
         if(num <= 0)
               num = NUM;
    }

    /* Allocate host (CPU) memory and initialize*/

    ptr = (char *)malloc(num * 3 * sizeof(double));
    sptr = ptr;
    for(i=0; i<num; ++i){
       pa = (struct num_array *) sptr;
       pa->num1 = (double) i + (double) i * 0.1;
       pa->num2 = pa->num1 + 1.0;
       sptr += 3 * sizeof(double);
    }
    
    
    gettimeofday(&t_start, NULL);
    
    /* Allocate GPU memory and copy from CPU --> GPU*/

    cudaMalloc(&gpu_mem, num * 3 * sizeof(double));
    CUDA_ERROR_EXIT("cudaMalloc");

    cudaMemcpy(gpu_mem, ptr, num * 3 * sizeof(double) , cudaMemcpyHostToDevice);
    CUDA_ERROR_EXIT("cudaMemcpy");
    
    gettimeofday(&start, NULL);
    
    blocks = num /1024;
    
    if(num % 1024)
           ++blocks;

    calculate<<<blocks, 1024>>>(gpu_mem, num);
    CUDA_ERROR_EXIT("kernel invocation");
    gettimeofday(&end, NULL);
    
    /* Copy back result*/

    cudaMemcpy(ptr, gpu_mem, num * 3 * sizeof(double) , cudaMemcpyDeviceToHost);
    CUDA_ERROR_EXIT("memcpy");
    gettimeofday(&t_end, NULL);
    
    printf("Total time = %ld microsecs Processsing =%ld microsecs\n", TDIFF(t_start, t_end), TDIFF(start, end));
    cudaFree(gpu_mem);
    sptr = ptr;
   
    /*Print the last element for sanity check*/ 
    pa = (struct num_array *) (sptr + (num -1)*3*sizeof(double));
    printf("num1=%f num2=%f result=%f\n", pa->num1, pa->num2, pa->result);

    
    free(ptr);
}
