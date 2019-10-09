#include<context.h>
#include<memory.h>
#include<schedule.h>
#include<apic.h>
#include<idt.h>
#include<lib.h>
#include<types.h>
static u64 numticks;
static u32 free_os_page[MAX_PROCESSES];

static void save_current_context(struct exec_context *ctx, u64 *rsp_break, u64 *entry_rbp)
{
  ctx->regs.r15 = *(rsp_break);
  ctx->regs.r14 = *(rsp_break+1);
  ctx->regs.r13 = *(rsp_break+2);
  ctx->regs.r12 = *(rsp_break+3);
  ctx->regs.r11 = *(rsp_break+4);
  ctx->regs.r10 = *(rsp_break+5);
  ctx->regs.r9 = *(rsp_break+6);
  ctx->regs.r8 = *(rsp_break+7);
  ctx->regs.rdi = *(rsp_break+8);
  ctx->regs.rsi = *(rsp_break+9);
  ctx->regs.rdx = *(rsp_break+10);
  ctx->regs.rcx = *(rsp_break+11);
  ctx->regs.rbx = *(rsp_break+12);
  ctx->regs.rax = *(rsp_break+13);
  ctx->regs.rbp = *(entry_rbp);
  ctx->regs.entry_rip = *(entry_rbp+1);
  ctx->regs.entry_cs = *(entry_rbp+2);
  ctx->regs.entry_rflags = *(entry_rbp+3);
  ctx->regs.entry_rsp = *(entry_rbp+4);
  ctx->regs.entry_ss = *(entry_rbp+5);
}

static void schedule_context(struct exec_context *next, int flag)
{
  /*Your code goes in here. get_current_ctx() still returns the old context*/
 struct exec_context *current = get_current_ctx();
 printf("scheduling: old pid = %d  new pid  = %d\n", current->pid, next->pid); /*XXX: Don't remove*/
/*These two lines must be executed*/
 set_tss_stack_ptr(next);
 set_current_ctx(next);
 next->state = RUNNING;

 if(flag)
    ack_irq();  /*acknowledge the interrupt, before calling iretq */

 asm volatile("sub $8, %%rsp; \
     mov %0, (%%rsp);" :: "r" (next->regs.entry_ss));
 asm volatile("sub $8, %%rsp; \
     mov %0, (%%rsp);" :: "r" (next->regs.entry_rsp));
 asm volatile("sub $8, %%rsp; \
     mov %0, (%%rsp);" :: "r" (next->regs.entry_rflags));
 asm volatile("sub $8, %%rsp; \
     mov %0, (%%rsp);" :: "r" (next->regs.entry_cs));
 asm volatile("sub $8, %%rsp; \
     mov %0, (%%rsp);" :: "r" (next->regs.entry_rip));

 asm volatile("sub $8, %%rsp; \
     mov %0, (%%rsp);" :: "r" (next->regs.rax));
 asm volatile("sub $8, %%rsp; \
     mov %0, (%%rsp);" :: "r" (next->regs.rbx));
 asm volatile("sub $8, %%rsp; \
     mov %0, (%%rsp);" :: "r" (next->regs.rcx));
 asm volatile("sub $8, %%rsp; \
     mov %0, (%%rsp);" :: "r" (next->regs.rdx));
 asm volatile("sub $8, %%rsp; \
     mov %0, (%%rsp);" :: "r" (next->regs.rsi));
 asm volatile("sub $8, %%rsp; \
     mov %0, (%%rsp);" :: "r" (next->regs.rdi));
 asm volatile("sub $8, %%rsp; \
     mov %0, (%%rsp);" :: "r" (next->regs.rbp));
 asm volatile("sub $8, %%rsp; \
     mov %0, (%%rsp);" :: "r" (next->regs.r8));
 asm volatile("sub $8, %%rsp; \
     mov %0, (%%rsp);" :: "r" (next->regs.r9));
 asm volatile("sub $8, %%rsp; \
     mov %0, (%%rsp);" :: "r" (next->regs.r10));
 asm volatile("sub $8, %%rsp; \
     mov %0, (%%rsp);" :: "r" (next->regs.r11));
 asm volatile("sub $8, %%rsp; \
     mov %0, (%%rsp);" :: "r" (next->regs.r12));
 asm volatile("sub $8, %%rsp; \
     mov %0, (%%rsp);" :: "r" (next->regs.r13));
 asm volatile("sub $8, %%rsp; \
     mov %0, (%%rsp);" :: "r" (next->regs.r14));
 asm volatile("sub $8, %%rsp; \
     mov %0, (%%rsp);" :: "r" (next->regs.r15));

 asm volatile ("pop %%r15;        \
                pop %%r14;        \
                pop %%r13;        \
                pop %%r12;        \
                pop %%r11;        \
                pop %%r10;        \
                pop %%r9;         \
                pop %%r8;         \
                pop %%rbp;        \
                pop %%rdi;        \
                pop %%rsi;        \
                pop %%rdx;        \
                pop %%rcx;        \
                pop %%rbx;        \
                pop %%rax;"
              "iretq;"
              :::"memory");
 return;
}

static struct exec_context *pick_next_context(struct exec_context *list, struct exec_context *current)
{
  int i,j;
  i = current->pid;
  struct exec_context *ctx = list;
  for(j=1;j<MAX_PROCESSES;j++)
  {
    ctx = get_ctx_by_pid((i+j)%MAX_PROCESSES);
    if((ctx->pid != 0) && (ctx->state == READY))
      return ctx;
  }
  if(current->state == READY)
    return current;
  return get_ctx_by_pid(0);
}
static void schedule(int flag)
{
 struct exec_context *next;
 struct exec_context *current = get_current_ctx();
 struct exec_context *list = get_ctx_list();
 next = pick_next_context(list, current);
 if(next == current)
   return;
 schedule_context(next, flag);
}

static void do_sleep_and_alarm_account(u64 *entry_rbp)
{
 /*All processes in sleep() must decrement their sleep count*/ 
  struct exec_context *init_ctx = get_ctx_by_pid(1);
  if(init_ctx->ticks_to_alarm > 0)
  {
    if(init_ctx->ticks_to_alarm == 1)
    {
        invoke_sync_signal(SIGALRM, entry_rbp+4, entry_rbp+1);
        init_ctx->ticks_to_alarm = init_ctx->alarm_config_time;
    }
    else
      (init_ctx->ticks_to_alarm)--;
  }

  struct exec_context *list = get_ctx_list();
  struct exec_context *ctx;
  int i;
  for(i=1; i<MAX_PROCESSES; i++)
  {
    ctx = (list + i);
    if((ctx->state == WAITING) && (ctx->ticks_to_sleep > 0))
    {
      if(ctx->ticks_to_sleep == 1)
        ctx->state = READY;
      (ctx->ticks_to_sleep)--;
    }
  }
}

/*The five functions above are just a template. You may change the signatures as you wish*/
void handle_timer_tick()
{
 /*
   This is the timer interrupt handler. 
   You should account timer ticks for alarm and sleep
   and invoke schedule
 */
  u64 *rsp_break, *entry_rbp;
  int i;
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
            push %%r15; \
            mov %%rsp, %0; \
            mov %%rbp, %1;" : "=r" (rsp_break), "=r" (entry_rbp));
  struct exec_context *current = get_current_ctx();
  save_current_context(current, rsp_break, entry_rbp);

  for(i=1;i<MAX_PROCESSES;i++)
  {
    if(free_os_page[i] != 0)
    {
      os_pfn_free(OS_PT_REG, free_os_page[i]);
      free_os_page[i] = 0;
    }
  }

  do_sleep_and_alarm_account(entry_rbp);

  if(current->state == RUNNING)
    current->state = READY;

  printf("Got a tick. #ticks = %u\n", ++numticks);   /*XXX Do not modify this line*/ 
  schedule(1);
  ack_irq();  /*acknowledge the interrupt, before calling iretq */
  asm volatile("mov %0, %%rsp;" :: "r" (rsp_break));
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
                 "mov %%rbp, %%rsp;"
               "pop %%rbp;"
               "iretq;"
               :::"memory");
}

void do_exit()
{
  /*You may need to invoke the scheduler from here if there are
    other processes except swapper in the system. Make sure you make 
    the status of the current process to UNUSED before scheduling 
    the next process. If the only process alive in system is swapper, 
    invoke do_cleanup() to shutdown gem5 (by crashing it, huh!)
    */
    struct exec_context *ctx = get_current_ctx();
    ctx->state = UNUSED;
    free_os_page[ctx->pid] = ctx->os_stack_pfn;
    struct exec_context *ctx_list = get_ctx_list();
    int i;
    for(i=1;i<MAX_PROCESSES;i++)
        if(((ctx_list+i)->pid != 0) && ((ctx_list+i)->state != UNUSED))
          break;
    if(i != MAX_PROCESSES)
      schedule(0);
    do_cleanup();  /*Call this conditionally, see comments above*/
}

/*system call handler for sleep*/
long do_sleep(u32 ticks)
{
  u64 *syscall_rbp;
  struct exec_context *ctx = get_current_ctx();
  ctx->state = WAITING;
  ctx->ticks_to_sleep = ticks;

  asm volatile("mov (%%rbp), %0;" : "=r" (syscall_rbp));
  ctx->regs.r15 = *(syscall_rbp+2);
  ctx->regs.r14 = *(syscall_rbp+3);
  ctx->regs.r13 = *(syscall_rbp+4);
  ctx->regs.r12 = *(syscall_rbp+5);
  ctx->regs.r11 = *(syscall_rbp+6);
  ctx->regs.r10 = *(syscall_rbp+7);
  ctx->regs.r9 = *(syscall_rbp+8);
  ctx->regs.r8 = *(syscall_rbp+9);
  ctx->regs.rbp = *(syscall_rbp+10);
  ctx->regs.rdi = *(syscall_rbp+11);
  ctx->regs.rsi = *(syscall_rbp+12);
  ctx->regs.rdx = *(syscall_rbp+13);
  ctx->regs.rcx = *(syscall_rbp+14);
  ctx->regs.rbx = *(syscall_rbp+15);
  ctx->regs.entry_rip = *(syscall_rbp+16);
  ctx->regs.entry_cs = *(syscall_rbp+17);
  ctx->regs.entry_rflags = *(syscall_rbp+18);
  ctx->regs.entry_rsp = *(syscall_rbp+19);
  ctx->regs.entry_ss = *(syscall_rbp+20);

  schedule(0);
  return 0;
}

/*
  system call handler for clone, create thread like 
  execution contexts
*/
long do_clone(void *th_func, void *user_stack)
{
  u64 *syscall_rbp;
  struct exec_context *ctx = get_current_ctx();
  struct exec_context *new_ctx = get_new_ctx();
  new_ctx->os_stack_pfn = os_pfn_alloc(OS_PT_REG);
  new_ctx->pgd = ctx->pgd;

  char pid[4];
  pid[0] = '_';
  pid[1] = '0' + (new_ctx->pid / 10);
  pid[2] = '0' + (new_ctx->pid % 10);
  pid[3] = 0;
  bzero(new_ctx->name, CNAME_MAX);
  memcpy(new_ctx->name, ctx->name, strlen(ctx->name));
  memcpy(new_ctx->name + (strlen(ctx->name)-1), pid, strlen(pid));
  
  asm volatile("mov (%%rbp), %0;" : "=r" (syscall_rbp));
  new_ctx->regs.entry_rip = (u64 *)th_func;
  new_ctx->regs.entry_cs = 0x23;
  new_ctx->regs.entry_rflags = *(syscall_rbp+18);
  new_ctx->regs.entry_rsp = (u64 *)user_stack;
  new_ctx->regs.entry_ss = 0x2b;

  struct mm_segment *temp;
  temp = &(new_ctx->mms[MM_SEG_STACK]);
  temp->start = ctx->mms[MM_SEG_STACK].start;
  temp->end = ctx->mms[MM_SEG_STACK].end;
  temp->next_free = ctx->mms[MM_SEG_STACK].next_free;
  temp->access_flags = ctx->mms[MM_SEG_STACK].access_flags;

  temp = &(new_ctx->mms[MM_SEG_DATA]);
  temp->start = ctx->mms[MM_SEG_DATA].start;
  temp->end = ctx->mms[MM_SEG_DATA].end;
  temp->next_free = ctx->mms[MM_SEG_DATA].next_free;
  temp->access_flags = ctx->mms[MM_SEG_DATA].access_flags;

  temp = &(new_ctx->mms[MM_SEG_CODE]);
  temp->start = ctx->mms[MM_SEG_CODE].start;
  temp->end = ctx->mms[MM_SEG_CODE].end;
  temp->next_free = ctx->mms[MM_SEG_CODE].next_free;
  temp->access_flags = ctx->mms[MM_SEG_CODE].access_flags;

  temp = &(new_ctx->mms[MM_SEG_RODATA]);
  temp->start = ctx->mms[MM_SEG_RODATA].start;
  temp->end = ctx->mms[MM_SEG_RODATA].end;
  temp->next_free = ctx->mms[MM_SEG_RODATA].next_free;
  temp->access_flags = ctx->mms[MM_SEG_RODATA].access_flags;

  new_ctx->state = READY;
  return new_ctx->pid;
}

long invoke_sync_signal(int signo, u64 *ustackp, u64 *urip)
{
   /*If signal handler is registered, manipulate user stack and RIP to execute signal handler*/
   /*ustackp and urip are pointers to user RSP and user RIP in the exception/interrupt stack*/
   //printf("Called signal with ustackp=%x urip=%x\n", *ustackp, *urip);
   struct exec_context *ctx = get_current_ctx();
   u64 *handler = ctx->sighandlers[signo];
   if(handler != NULL)
   {
       u64 *rsp_value;
       rsp_value = *ustackp;
       rsp_value--;
       *rsp_value = *urip;
       *ustackp = rsp_value;
       *urip = handler;
       return 0;
   }
   /*Default behavior is exit( ) if sighandler is not registered for SIGFPE or SIGSEGV.
    Ignore for SIGALRM*/
    if(signo != SIGALRM)
      do_exit();
    else
      return 0;
}
/*system call handler for signal, to register a handler*/
long do_signal(int signo, unsigned long handler)
{
    struct exec_context *ctx = get_current_ctx();
    if((signo < 0 || signo >= MAX_SIGNALS) || (ctx == NULL))
        return 1;
    ctx->sighandlers[signo] = (void *)handler;
    return 0;
}

/*system call handler for alarm*/
long do_alarm(u32 ticks)
{
    struct exec_context *ctx = get_current_ctx();
    long ticks_left = ctx->ticks_to_alarm;
    ctx->ticks_to_alarm = ticks;
    ctx->alarm_config_time = ticks;
    return ticks_left;
}
