#ifndef __SCHEDULE_H_
#define __SCHEDULE_H_
enum signals{
               SIGSEGV,
               SIGFPE,
               SIGALRM,
               MAX_SIGNALS
};

enum process_state{
                       UNUSED,
                       NEW,
                       READY,
                       RUNNING,
                       WAITING,
                       EXITING,
                       MAX_STATE
};
  
extern long do_alarm(u32 ticks);
extern long do_signal(int signo, unsigned long handler);
extern long invoke_sync_signal(int signo, u64 *ustackp, u64 *urip);
extern long do_clone(void *th_func, void *user_stack);
extern long do_sleep(u32 ticks);
extern void do_exit();
#endif
