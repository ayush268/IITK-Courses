#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *ptr = NULL;
main()
{
  int pid = fork();
  if(!pid)
  {
    ptr = malloc(64);
    *ptr = 'A';
    exit(0);
  }
  wait();
  printf("%c\n", *ptr);
}
