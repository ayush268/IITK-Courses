#ifndef INFINITE_SUM_FUNCTIONS
   #define INFINITE_SUM_FUNCTIONS

#define PI_ITERS 1000000
#define COS_ITERS 1000
#define EPOW_ITERS 1000

#define USAGE_EXIT(s) do{ \
                             printf("Usage: %s <value of x>\n %s\n", argv[0], s); \
                            exit(-1);\
                    }while(0);

extern double epow (double x);
extern double cosine (double x);
extern double pi (void);

#endif
