#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>


#define NUM 32

#define CUDA_ERROR_EXIT(str) do{\
                                    cudaError err = cudaGetLastError();\
                                    if( err != cudaSuccess){\
                                             printf("Cuda Error: '%s' for %s\n", cudaGetErrorString(err), str);\
                                             exit(-1);\
                                    }\
                             }while(0);


__global__ void D_Mul(int *dA, int *dB, int *dC)
{
      int i = threadIdx.x; 
  //    int i = blockIdx.x * blockDim.x + threadIdx.x;
      dC[i] = dA[i] * dB[i];
}

int main(int argc, char **argv)
{
    int ctr;
    int *hA, *hB, *hC;
  
    int *dA, *dB, *dC; 
   
    int size = NUM * sizeof(int); 

    /*Allocate memory on the host (CPU) */

    hA = (int *) malloc(size);
    if(!hA){
          perror("malloc");
          exit(-1);
    }
    
    hB = (int *) malloc(size);
    if(!hB){
          perror("malloc");
          exit(-1);
    }
       

    hC = (int *) malloc(size);
    if(!hC){
          perror("malloc");
          exit(-1);
    }
    
    /*Initialize hA and hB*/

    for(ctr=0; ctr < NUM; ++ctr)
         hA[ctr] = hB[ctr] = ctr+1;
    
   /*Allocate memory on the device (GPU) */

    cudaMalloc(&dA,  size);
    CUDA_ERROR_EXIT("cudaMalloc");

    cudaMalloc(&dB,  size);
    CUDA_ERROR_EXIT("cudaMalloc");

    cudaMalloc(&dC,  size);
    CUDA_ERROR_EXIT("cudaMalloc");
   
    /*Copy hA --> dA and hB --> dB */
    
    cudaMemcpy(dA, hA, size, cudaMemcpyHostToDevice);
    CUDA_ERROR_EXIT("memcpy1");
    
    cudaMemcpy(dB, hB, size, cudaMemcpyHostToDevice);
    CUDA_ERROR_EXIT("memcpy1");
    
    
     /*Invoke the kernel*/
     D_Mul<<<1, NUM>>>(dA, dB, dC);
    //int blocks = (NUM + 1023) >> 10;
    //D_Mul<<<blocks, 1024>>>(dA, dB, dC);
    CUDA_ERROR_EXIT("kernel invocation");
   
    printf("kernel successful\n"); 

    /*Copy back results*/
    cudaMemcpy(hC, dC, size, cudaMemcpyDeviceToHost);
    CUDA_ERROR_EXIT("memcpy");
    for(ctr=0; ctr < NUM; ++ctr)
        printf("%d %d %d\n", hA[ctr], hB[ctr], hC[ctr]);
    
    free(hA); 
    free(hB); 
    free(hC); 
    cudaFree(dA);
    cudaFree(dB);
    cudaFree(dC);
}
