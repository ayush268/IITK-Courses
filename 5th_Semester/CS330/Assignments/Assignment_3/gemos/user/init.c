#include <init.h>
#include <memory.h>
static void exit(int);
static int main(void);

void init_start()
{
  int retval = main();
  exit(0);
}

/*Invoke system call with no additional arguments*/
static long _syscall0(int syscall_num)
{
  asm volatile ( "int $0x80;"
                 "leaveq;"
                 "retq;"
                :::"memory");
  return 0;   /*gcc shutup!*/
}

/*Invoke system call with one argument*/

static long _syscall1(int syscall_num, int exit_code)
{
  asm volatile ( "int $0x80;"
                 "leaveq;"
                 "retq;"
                :::"memory");
  return 0;   /*gcc shutup!*/
}
/*Invoke system call with two arguments*/

static long _syscall2(int syscall_num, u64 arg1, u64 arg2)
{
  asm volatile ( "int $0x80;"
                 "leaveq;"
                 "retq;"
                :::"memory");
  return 0;   /*gcc shutup!*/
}

static void exit(int code)
{
  _syscall1(SYSCALL_EXIT, code); 
}

static void alarm(int ticks)
{
  _syscall1(SYSCALL_ALARM, ticks); 
}

static void sleep(int ticks)
{
  _syscall1(SYSCALL_SLEEP, ticks); 
}

static long getpid()
{
  return(_syscall0(SYSCALL_GETPID));
}

static long write(char *ptr, int size)
{
   return(_syscall2(SYSCALL_WRITE, (u64)ptr, size));
}

static long clone(void *ptr1, void *ptr2)
{
   return(_syscall2(SYSCALL_CLONE, ptr1, ptr2));
}

static long expand(u32 size, int flags)
{
  return(_syscall2(SYSCALL_EXPAND, size, flags));
}

static long signal(int signo, void *handler)
{
   return(_syscall2(SYSCALL_SIGNAL, signo, (u64)handler));
}

static void clone_func1(void)
{
  sleep(8);
  write("I am a child\n", 13);
  exit(910);
}

static void clone_func2(void)
{
  write("I 22 2 child\n", 13);
  write("I 22 2 child\n", 13);
  sleep(2);
  write("I 22 2 child\n", 13);
  write("I 22 2 child\n", 13);
  sleep(2);
  write("I 22 2 child\n", 13);
  write("I 22 2 child\n", 13);
  sleep(2);
  write("I 22 2 child\n", 13);
  write("I 22 2 child\n", 13);
  sleep(2);
  exit(100);
}

static void clone_func3(void)
{
  write("I 3333 child\n", 13);
  write("I 3333 child\n", 13);
  write("I 3333 child\n", 13);
  write("I 3333 child\n", 13);
  write("I 3333 child\n", 13);
  write("I 3333 child\n", 13);
  write("I 3333 child\n", 13);
  write("I 3333 child\n", 13);
  write("I 3333 child\n", 13);
  write("I 3333 child\n", 13);
  write("I 3333 child\n", 13);
  write("I 3333 child\n", 13);
  write("I 3333 child\n", 13);
  write("I 3333 child\n", 13);
  exit(9);
}

static void clone_func4(void)
{
  write("44444444444\n", 13);
  write("44444444444\n", 13);
  write("44444444444\n", 13);
  write("44444444444\n", 13);
  write("44444444444\n", 13);
  write("44444444444\n", 13);
  write("44444444444\n", 13);
  write("44444444444\n", 13);
  write("44444444444\n", 13);
  write("44444444444\n", 13);
  write("44444444444\n", 13);
  write("44444444444\n", 13);
  write("44444444444\n", 13);
  write("44444444444\n", 13);
  sleep(10);
  write("44444444444\n", 13);
  write("44444444444\n", 13);
  write("44444444444\n", 13);
  write("44444444444\n", 13);
  write("44444444444\n", 13);
  write("44444444444\n", 13);
  write("44444444444\n", 13);
  write("44444444444\n", 13);
  write("44444444444\n", 13);
  write("44444444444\n", 13);
  write("44444444444\n", 13);
  write("44444444444\n", 13);
  write("44444444444\n", 13);
  write("44444444444\n", 13);
  write("44444444444\n", 13);
  write("44444444444\n", 13);
  write("44444444444\n", 13);
  exit(1000);
}

static void clone_func5(void)
{
  write("I am a 55555\n", 13);
  write("I am a 55555\n", 13);
  exit(1009);
  write("I am a 55555\n", 13);
  write("I am a 55555\n", 13);
}

static void clone_func6(void)
{
  sleep(1);
  exit(10);
  write("I am a 66666\n", 13);
}

static void clone_func7(void)
{
  write("I 7777 child\n", 13);
  write("I 7777 child\n", 13);
  sleep(11);
  write("I 7777 child\n", 13);
  exit(10);
  write("I 7777 child\n", 13);
}

static void clone_func8(void)
{
  int i = getpid();
  write("I am a 88888\n", 13);
  i = i/0;
  exit(10);
}

static void clone_func9(void)
{
  u64 *i = 0x0;
  write("I am a 99999\n", 13);
  u64 j = *i;
  write("I am a 99999\n", 13);
  exit(10);
}

static void clone_func10(void)
{
  write("I am a child\n", 13);
  sleep(100);
  exit(10);
}

static void segalarm_handler(void)
{
   asm volatile("push %%rax; \
             push %%rbx; \
             push %%rcx; \
             push %%rdx; \
			       push %%rsi; \
             push %%rdi; \
             push %%r8;  \
             push %%r9;  \
             push %%r10; \
             push %%r11; \
             push %%r12; \
             push %%r13; \
             push %%r14; \
             push %%r15;"
			 ::);
   write("I am segalarm\n", 14);
   asm volatile ("pop %%r15;        \
                  pop %%r14;        \
                  pop %%r13;        \
                  pop %%r12;        \
                  pop %%r11;        \
                  pop %%r10;        \
                  pop %%r9;         \
                  pop %%r8;         \
                  pop %%rdi;        \
                  pop %%rsi;        \
                  pop %%rdx;        \
                  pop %%rcx;        \
                  pop %%rbx;        \
                  pop %%rax;"
                  ::);
}

static void segfpe_handler(void)
{
   asm volatile("push %%rax; \
             push %%rbx; \
             push %%rcx; \
             push %%rdx; \
			       push %%rsi; \
             push %%rdi; \
             push %%r8;  \
             push %%r9;  \
             push %%r10; \
             push %%r11; \
             push %%r12; \
             push %%r13; \
             push %%r14; \
             push %%r15;"
			 ::);
   write("I am segfpe\n", 12);
   asm volatile ("pop %%r15;        \
                  pop %%r14;        \
                  pop %%r13;        \
                  pop %%r12;        \
                  pop %%r11;        \
                  pop %%r10;        \
                  pop %%r9;         \
                  pop %%r8;         \
                  pop %%rdi;        \
                  pop %%rsi;        \
                  pop %%rdx;        \
                  pop %%rcx;        \
                  pop %%rbx;        \
                  pop %%rax;"
                  ::);
}

static void segfault_handler(void)
{
   asm volatile("push %%rax; \
             push %%rbx; \
             push %%rcx; \
             push %%rdx; \
			       push %%rsi; \
             push %%rdi; \
             push %%r8;  \
             push %%r9;  \
             push %%r10; \
             push %%r11; \
             push %%r12; \
             push %%r13; \
             push %%r14; \
             push %%r15;"
			 ::);
   write("I am segfault\n", 14);
   //static int a=0;
   //a++;
   asm volatile ("pop %%r15;        \
                  pop %%r14;        \
                  pop %%r13;        \
                  pop %%r12;        \
                  pop %%r11;        \
                  pop %%r10;        \
                  pop %%r9;         \
                  pop %%r8;         \
                  pop %%rdi;        \
                  pop %%rsi;        \
                  pop %%rdx;        \
                  pop %%rcx;        \
                  pop %%rbx;        \
                  pop %%rax;"
                  ::);
   //if(a==2)
    //exit(100);
}

static int main()
{
  #if 0
  unsigned long *k;
  unsigned long i, j;
  unsigned long buff[4096];
  i = getpid();
   
  for(i=0; i<4096; ++i){
      j = buff[i];
  }
  k = NULL;
  signal(SIGSEGV, &segfault_handler);
  signal(SIGFPE, &segfpe_handler);
  signal(SIGALRM, &segalarm_handler);
  alarm(5);
  alarm(1);
  write("TOTO\n", 5);
  //while(1);
  //j = *k;
  i=0x100034;
  j = i / (i-0x100034);
  //exit(-5);
  #endif
  
  #if 1
  clone(&clone_func1, expand(5, MAP_WR));
  clone(&clone_func2, expand(5, MAP_WR));
  clone(&clone_func3, expand(5, MAP_WR));
  clone(&clone_func4, expand(5, MAP_WR));
  clone(&clone_func5, expand(5, MAP_WR));
  clone(&clone_func6, expand(5, MAP_WR));
  clone(&clone_func7, expand(5, MAP_WR));
  clone(&clone_func8, expand(5, MAP_WR));
  clone(&clone_func9, expand(5, MAP_WR));
  clone(&clone_func10, expand(5, MAP_WR));
  sleep(4);
  write("I am parent\n", 12);
  exit(1);
  #endif

  #if 0
  //unsigned long *user_rsp_break;
  //int i=0;
  write("AA\n", 3);
  sleep(3);
  sleep(5);
  //int a = 10;
  write("HI\n", 3);
   //asm volatile("push %%rax; \
   //          push %%rbx; \
   //          push %%rcx; \
   //          push %%rdx; \
	 // 	       push %%rsi; \
   //          push %%rdi; \
   //          push %%r8;  \
   //          push %%r9;  \
   //          push %%r10; \
   //          push %%r11; \
   //          push %%r12; \
   //          push %%r13; \
   //          push %%r14; \
   //          push %%r15; \
   //          mov %%rsp, %0;" : "=r" (user_rsp_break));
   //for(i=0;i<15;i++)
   //  printf("Original Value (rsp + %d) -> %x\n", *(user_rsp_break + i));
  #endif

  #if 0
  void *ptr1;
  char *ptr = (char *)expand(2, MAP_WR);
  *ptr = 'A';
  exit(100);
  #endif
  return 0;
}
