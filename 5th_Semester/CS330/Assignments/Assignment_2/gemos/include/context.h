#ifndef __CONTEXT_H_
#define __CONTEXT_H_

#include<types.h>
#define CNAME_MAX 64

enum{
           EXEC_CTX_BOOT,
           EXEC_CTX_OS,
           EXEC_CTX_USER,
           MAX_CTX
};
enum{
          MM_SEG_CODE,
          MM_SEG_RODATA,
          MM_SEG_DATA,
          MM_SEG_STACK,
          MAX_MM_SEGS
};

#define MM_RD 0x1
#define MM_WR 0x2
#define MM_EX 0x4
#define MM_SH 0x8


#define CODE_START       0x100000000  
#define RODATA_START     0x140000000 
#define DATA_START       0x180000000
#define STACK_START      0x800000000 

#define CODE_PAGES       0x8

#define MAX_STACK_SIZE   0x1000000


struct mm_segment{
                   unsigned long start;
                   unsigned long end;
                   unsigned long next_free; 
                   u32 access_flags;   /*R=1, W=2, X=4, S=8*/ 
};

struct exec_context{
             u32 id;
             u8 type;
             u8 status;
             u16 used_mem;
             u32 pgd;     /*CR3 should contain this value when schedulled*/
             u32 os_stack_pfn;
             struct mm_segment mms[MAX_MM_SEGS];
             char name[CNAME_MAX];
};


extern struct exec_context* create_context(char *, u8);
extern int exec_init (struct exec_context *);
extern struct exec_context *get_current_ctx(void);
extern void set_current_ctx(struct exec_context *);
extern void do_exit(void);
#endif
