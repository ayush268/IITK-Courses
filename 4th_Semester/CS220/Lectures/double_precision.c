#include <stdio.h>
#include <math.h>

int main (void)
{
	//double x = -3.75; // -11.11 = -1.111 x 2^1 in binary
                          // sign = 1, biased exponent = 1024, mantissa = 111000...0

        // double x = 0.0;       // Use this to check the representation of 0
        double x = (2 - pow(2, -52))*pow(2, 1023);     // Use this to check the representation of infinity; include -lm flag when compiling to link with math library
        double y = (2 - pow(2, -51))*pow(2, 1023);     // Use this to check the representation of infinity; include -lm flag when compiling to link with math library
        // double x = sqrt(-1);  // Use this to check the representation of NaN; include -lm flag when compiling to link with math library
        // double x = 0*sqrt(-1); // Use this to verify that if any operand in an operation is NaN, the result is also NaN; include -lm flag when compiling to link with math library
	unsigned sbit;
	unsigned exponent;
	unsigned long long fraction;
	sbit = ((*((unsigned long long*)&x)) >> 63) & 1;
	exponent = ((*((unsigned long long*)&x)) >> 52) & 0x7ff;
	fraction = (*((unsigned long long*)&x)) & 0xfffffffffffff;
	printf("Double value: %lf, sign bit: %u, biased exponent: %u, actual exponent: %d, mantissa: %#llx\n", x, sbit, exponent, exponent-1023, fraction); 
  if(y<x)
  {
    printf("Hi\n");
  }
	return 0;
}
