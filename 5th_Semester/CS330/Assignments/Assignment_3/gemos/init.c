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

static void clone_func(void)
{
  write("I am a child\n", 13);
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
  clone(&clone_func, expand(5, MAP_WR));
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
