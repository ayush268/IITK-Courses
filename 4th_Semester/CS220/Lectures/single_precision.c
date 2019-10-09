#include <stdio.h>
#include <math.h>

int main (void)
{
	//float x = -3.75; // -11.11 = -1.111 x 2^1 in binary
			 // sign = 1, biased exponent = 128, mantissa = 111000...0

	// float x = 0.0;	// Use this to check the representation of 0
	 float x = (2 - pow(2, -23))*pow(2, 127);	// Use this to check the representation of infinity; include -lm flag when compiling to link with math library
	// float x = sqrt(-1);	// Use this to check the representation of NaN; include -lm flag when compiling to link with math library
	// float x = 0*sqrt(-1); // Use this to verify that if any operand in an operation is NaN, the result is also NaN; include -lm flag when compiling to link with math library
	unsigned int sbit;
	unsigned int exponent;
	unsigned int fraction;
	sbit = ((*((unsigned int*)&x)) >> 31) & 1;
	exponent = ((*((unsigned int*)&x)) >> 23) & 0xff;
	fraction = (*((unsigned int*)&x)) & 0x7fffff;
	printf("Float value: %f, sign bit: %u, biased exponent: %u, actual exponent: %d, mantissa: %#x\n", x, sbit, exponent, exponent-127, fraction); 
	return 0;
}
