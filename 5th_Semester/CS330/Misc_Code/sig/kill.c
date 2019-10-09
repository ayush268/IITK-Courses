#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

int main(int argc, char **argv)
{
   int signo, pid, repeat;
   if(argc != 4){
        printf("Usage: %s pid signal repeat\n", argv[0]);
        exit(-1);
   }
   signo = atoi(argv[2]);
   pid = atoi(argv[1]);
   repeat = atoi(argv[3]);

   do{
        if(kill(pid, SIGSEGV) < 0)
           perror("kill");
        printf("Sent signal\n");
        sleep(1);
        repeat--;
   }while(repeat);
}
