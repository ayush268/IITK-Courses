#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
  char string1[200];
  char string2[200];
  int f1 = open(argv[1], O_RDONLY);
  
  printf("Original -> %d\n", f1);
  read(f1, string1, 20); 

  printf("%s\n", string1);
  //int f2 = dup(f1);
  int f2 = open(argv[1], O_RDONLY);
  printf("Dupped -> %d\n", f2);

  read(f2, string2, 20); 
  printf("%s\n", string2);
  return 0;
}
