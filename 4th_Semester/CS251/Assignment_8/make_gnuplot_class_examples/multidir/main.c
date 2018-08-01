#include<stdio.h>
#include<common.h>
main()
{
   printf("hello world\n");
   #ifdef DBG
   printf("bye world\n");
   #endif
}
