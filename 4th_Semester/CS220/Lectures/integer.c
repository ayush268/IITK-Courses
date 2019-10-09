#include <stdio.h>

int main (void)
{
	int x = -10;
	unsigned int bits = *((unsigned int*)&x);
	printf("bits = %#x\n", bits);
	return 0;
}
