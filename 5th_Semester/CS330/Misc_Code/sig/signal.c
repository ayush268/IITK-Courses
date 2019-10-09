#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void sighandler(int signo)
{
    printf("I am SIGSEGV\n");
}

main(int argc, char **argv)
{
    printf("PID -> %d\n", getpid());
   //if(signal(SIGSEGV, &sighandler) < 0)
   //     perror("signal");

    while(1)
    {
        sleep(1);
        printf("Hi Man!\n");
    };
}
