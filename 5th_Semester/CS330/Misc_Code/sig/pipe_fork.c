#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
main()
{
   int pid;
   char buf[32];
   int fd[2];
   if(pipe(fd) < 0){
        perror("pipe");
        exit(-1);
   }

   pid = fork();   
   if(pid < 0){
      perror("fork");
      exit(-1);
   }  

   if(!pid){ // Child 
       close(fd[0]);      // Close the read end in child
       sleep(1);
       if(write(fd[1], "Hello pipe\n", 11) != 11){
            perror("write");
            exit(-1);
        }
       exit(0);
   }
   
   close(fd[1]);    // Close the write end in parent
   if(read(fd[0], buf, 11) != 11){
       perror("read");
       exit(-1);
   }
   
  buf[11] = 0;
  printf("%s", buf);
  
}
