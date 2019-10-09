#include <stdio.h>

int main (void)
{
	long long x = -10;
	unsigned long long bits = *((unsigned long long*)&x);
	printf("bits = %#llx\n", bits);
	return 0;
}
