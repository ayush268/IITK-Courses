#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void sighandler(int signo)
{
    printf("SIGINT from %d\n", getpid());
}
main()
{
    int i, status;
    pid_t pid, cpid;
    printf("Before calling fork mypid = %d\n", getpid());
    
    if(signal(SIGINT, &sighandler) < 0)
        perror("signal");
    
    pid = fork();
    if(pid < 0){
         perror("fork");
         exit(-1);
    }
    
    if(!pid){ /*Child*/
         printf("%s: childpid= %d\n", __FILE__, getpid());
         while(1);
         exit(0);
    }
   cpid = wait(&status);    /*Wait for the child to finish*/

   if(cpid < 0)
        perror("wait");
   printf("Child pid = %d exited with status = %d\n", cpid, WEXITSTATUS(status));
   while(1);

}
