#include <stdio.h>
#include <stdlib.h>

#define ERROR(s) printf("%s \n Usage: %s <no. of elements> <random seed>\n", s, argv[0]); exit(-1);

#define CUDA_ERROR_EXIT(str) do{\
                                    cudaError err = cudaGetLastError();\
                                    if( err != cudaSuccess){\
                                        printf("Cuda Error: '%s' for %s\n", cudaGetErrorString(err), str);\
                                        exit(-1);\
                                    }\
                             }while(0);

__global__ void Xor(char *dev_in, int num_elements, int interval)
{
    int tid = blockDim.x * blockIdx.x + threadIdx.x;
    int k = tid * interval;

    if(k >= num_elements)
        return;

    if(k + interval >= num_elements)
        interval = num_elements - k;

    unsigned *tmp1 = (unsigned *)(dev_in + k * sizeof(unsigned));
    unsigned *tmp2 = tmp1 + interval - 1;

    if(tmp1 == tmp2)
        return;

    if(tid % 2 == 0)
    {
        *tmp1 = (*tmp1) ^ (*tmp2);
        *tmp2 = 0;
    }
    else
    {
        *tmp2 = (*tmp1) ^ (*tmp2);
        *tmp1 = 0;
    }
}

int main(int argc, char **argv)
{
    int i, seed, interval;
    unsigned *in;
    char *tmp;
    char *dev_in;
    int blocks, threads = 1024;
    unsigned num_elements;

    if(argc != 3)
    {
        ERROR("Invalid number of parameters!");
    }

    num_elements = atoi(argv[1]);
    if(num_elements<=0)
    {
        ERROR("Invalid number of elements!");
    }

    seed = atoi(argv[2]);
    if(seed<=0)
    {
        ERROR("Invalid seed value!");
    }

    tmp = (char *)malloc(num_elements * sizeof(unsigned));
    in = (unsigned *)tmp;

    srand(seed);
    for(i=0; i<num_elements; i++)
    {
        *in = rand();
        in++;
    }

    cudaMalloc(&dev_in, num_elements * sizeof(unsigned));
    CUDA_ERROR_EXIT("cudaMalloc");

    cudaMemcpy(dev_in, tmp, num_elements * sizeof(unsigned), cudaMemcpyHostToDevice);
    CUDA_ERROR_EXIT("cudaMemcpy");

    blocks = (num_elements + 1023) / threads;

    for(interval=1;;interval++)
    {
        if(blocks > 1)
            blocks = ((num_elements >> interval) + 1023) / threads;
        else
            threads = threads >> 1;

        Xor<<<blocks, threads>>>(dev_in, num_elements, 1 << interval);
        CUDA_ERROR_EXIT("kernel invocation");

        cudaMemcpy(tmp, dev_in, num_elements * sizeof(unsigned), cudaMemcpyDeviceToHost);
        CUDA_ERROR_EXIT("cudaMemcpy");
        in = (unsigned *)tmp;

        if(threads <= 1)
            break;
    }

    cudaMemcpy(tmp, dev_in, sizeof(unsigned), cudaMemcpyDeviceToHost);
    cudaFree(dev_in);

    in = (unsigned *)tmp;
    printf("%u\n", *in);

    free(tmp);
    return 0;
}
