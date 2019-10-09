#include<stdio.h>

void dummy(int n)
{
  if(n < 0)
    return;
  puts("I am here");
  unsigned long rsp_val;
    asm volatile("mov %%rsp, %0;"
                  : "=r" (rsp_val)
                  :
                 );
   
    printf("RSP = %lx\n", rsp_val);
  dummy(n-1);
}

main(int argc, char **argv)
{
    unsigned long cr3_val, cs_val, rsp_val, rbp_val;
//    asm volatile ("hlt;");
    asm volatile("mov %%rsp, %0;"
                  : "=r" (rsp_val)
                  :
                 );
   
    printf("RSP = %lx\n", rsp_val);

    asm volatile("mov %%rbp, %0;"
                  : "=r" (rbp_val)
                  :
                 );
   
    printf("RBP = %lx\n", rbp_val);

  
//    asm volatile("mov %%cr3, %0;"
//                  : "=r" (cr3_val)
//                  :
//                 );
//   
//    printf("CR3 = %lx\n", cr3_val);
    asm volatile("mov %%cs, %0;"
                  : "=r" (cs_val)
                  :
                 );
    printf("CS = %lx\n", cs_val);

    int n = atoi(argv[1]);
    dummy(n);
    unsigned long rsp2_val;

    asm volatile("mov %%rsp, %0;"
                  : "=r" (rsp2_val)
                  :
                 );
   
    printf("RSP = %lx\n", rsp2_val);


    asm volatile("mov %0, %%rsp;"
                  :
                  : "r" (rsp_val)
                 );

    puts("here");
    asm volatile("mov %0, %%cs;"
                  :
                  : "r" (cs_val)
                 );
}
