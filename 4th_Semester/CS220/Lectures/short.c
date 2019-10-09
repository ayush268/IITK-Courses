#include <stdio.h>

int main (void)
{
	short x = -10;
	unsigned short bits = *((unsigned short*)&x);
	printf("bits = %#x\n", bits);
	return 0;
}
