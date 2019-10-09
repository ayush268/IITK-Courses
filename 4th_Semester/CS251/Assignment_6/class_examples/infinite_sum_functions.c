#include <infinite_sum_functions.h>

double pi(void)
{
    double sum = 1.0;
    int ctr;
    for(ctr=1; ctr < PI_ITERS; ++ctr){
          double add = (1.0)/(2*ctr + 1.0);
          if(ctr % 2 == 0) 
             sum += add;
          else
             sum -= add;
    }
   return (sum * 4);
}

double cosine(double x)
{
     double sum = 1;
     int ctr;
     double factorial = 1.0;
     double xpow = 1.0;
     for(ctr=1; ctr < COS_ITERS; ctr++){
          double add = 0.0;
          factorial *= ctr * (ctr + 1);
          xpow *= x * x;
          add = xpow / factorial;
          if(ctr % 2 == 0) 
             sum += add;
          else
             sum -= add;
          
     }
   return sum;
}

double epow(double x)
{
     double sum = 1;
     int ctr;
     double factorial = 1.0;
     double xpow = 1.0;
     for(ctr=1; ctr < EPOW_ITERS; ctr++){
          double add = 0.0;
          factorial *= ctr;
          xpow *= x;
          add = xpow / factorial;
          sum += add;
          
     }
   return sum;
}

