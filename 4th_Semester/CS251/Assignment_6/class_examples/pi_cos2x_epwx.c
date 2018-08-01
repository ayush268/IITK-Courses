#include <stdio.h>
#include <stdlib.h>
#include <infinite_sum_functions.h>

/*calculate pi * cos^2x / e^x 
  X is input */

int main(int argc, char **argv)
{
     
    double x, pival, cosval, eval; 
    if(argc != 2)
          USAGE_EXIT("invalid args\n");
    x = atof(argv[1]);
    
    if(x > 1.0 || x < 0.0)
          USAGE_EXIT("invalid args\n");

    pival = pi();
    cosval = cosine(x);
    eval = epow(x);
    
    printf("Function = %f\n", pival * cosval * cosval / eval);     
}
