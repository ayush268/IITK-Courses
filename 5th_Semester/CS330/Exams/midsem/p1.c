#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int var1 = 0;
int var2 = 0;

main()
{
  int i;
  pid_t pid = getpid();

  for(i=0;i<3;++i)
  {
    if(fork() < 0)
      exit(-1);
    ++var1;
    if(i%2==0 && getpid() != pid)
      execl("./p2", "p2", NULL);
    ++var2;
  }
  sleep(1);
  printf("var1=%d var2=%d\n", var1, var2);
}
