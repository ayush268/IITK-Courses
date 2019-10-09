#include<init.h>
#include<lib.h>
#include<context.h>
#include<memory.h>

#define L4_MASK 39
#define L3_MASK 30
#define L2_MASK 21
#define L1_MASK 12

static int mask[5] = { 0, L1_MASK, L2_MASK, L3_MASK, L4_MASK };

/* This function is for performing a page_table_walk for a specific level and populating the entries of pfn and pte_address on the way,
 * it returns 0 if it encounters an invalid bit on checking the PTE entry's last bit otherwise returns 1 (i.e. if entry is valid)
 */

static int page_table_walk(u64 virtual_address, u64 pfn[], u64 *pte_address[], int level)
{
    u64 *current_address = (u64 *)(osmap(pfn[level]));
    current_address += ((virtual_address >> mask[level]) & (0x1FF));
    if(current_address == pte_address[level])
        return 1;
    pte_address[level] = current_address;
    if(!(*pte_address[level] & (0x1)))
        return 0;
    else
    {
        pfn[level-1] = *pte_address[level] >> 12;
        return 1;
    }
}

/* This function will check the validity of the virtual_address (i.e. it is mapped and accessible by user or not (U/S bit -> 1)) if "alloc_or_not" is 0
 * If "alloc_or_not" is 1 (i.e. true), then it will allocate the page for the virtual address using cr3_value from context; access (R/W) bit will be set depending on segment's access flags.
 * The return value of this function is used only for "Check address part" which is used inside the write syscall, if return value is 1, then address is valid else invalid (for acces by user).
 */

static int check_or_alloc_address(u64 virtual_address, struct exec_context *ctx, int alloc_or_not, int segment)
{
    u32 pfn = ctx->pgd, iterator = 0;
    u32 access = ctx->mms[segment].access_flags;
    u64 *pte_address;
    for(iterator = 4; iterator > 0; iterator--)
    {
        pte_address = (u64 *)(osmap(pfn));
        pte_address += ((virtual_address >> mask[iterator]) & (0x1FF));
        if(!(*pte_address & (0x1)))
        {
            if(!alloc_or_not)
                return 0;
            else
            {
                if(iterator != 1)
                {
                    pfn = os_pfn_alloc(OS_PT_REG);
                    *pte_address = (pfn << 12) | (0x005 | (access & (0x2)));
                    pte_address = (u64 *)(osmap(pfn));
                    for(u32 j=0; j<512; j++)
                        *(pte_address+j) = 0;
                }
                else
                {
                    pfn = os_pfn_alloc(USER_REG);
                    *pte_address = (pfn << 12) | (0x005 | (access & (0x2)));
                }
            }
        }
        else
        {
            pfn = *pte_address >> 12;
            if(alloc_or_not)
                *pte_address = (pfn << 12) | (0x005 | (access & (0x2)));
        }
    }
    if(!((*pte_address >> 2) & (0x1)))
        return 0;
    return 1;
}

/* This function just checks the new value of next_free and sets the value if it is valid else doesn't change it and returns 0 */

static u64 expand_segment(u64 size, struct mm_segment *segment)
{
    u64 end = segment->end, next_free = segment->next_free, iterator = 0, original_next_free = segment->next_free;
    next_free += (size * PAGE_SIZE);
    if(next_free > end)
        return 0;
    segment->next_free = next_free;
    return original_next_free;
}

/* This function first checks the final value of next_free, if it is valid then it will walk the page table for each page (to be freed) and unallocate the DATA Page if any present
 * The if condition inside for loop will be activated if all 4 level walks are successful and since I am using the && operator here, the next (lower) level walk will only be done if the current level is valid.
 * Lastly, when freeing the page, we will have to invalidate the PTE from the TLB and all other caches for which we use the INVLPG instruction, one hack is to remove and restore value of CR3 triggering a TLB flush but that will clear out full TLB which is bad.
 */

static u64 shrink_segment(u64 size, u32 cr3_value, struct mm_segment *segment)
{
    u64 start = segment->start, next_free = segment->next_free, iterator = 0, pfn[5], *pte_address[5], virtual_address;
    if((next_free - (size * PAGE_SIZE)) < start)
        return 0;
    pfn[4] = cr3_value;
    for(iterator = 0; iterator < size; iterator++)
    {
        next_free -= PAGE_SIZE;
        virtual_address = next_free;
        if(page_table_walk(virtual_address, pfn, pte_address, 4) && page_table_walk(virtual_address, pfn, pte_address, 3) && page_table_walk(virtual_address, pfn, pte_address, 2) && page_table_walk(virtual_address, pfn, pte_address, 1))
        {
            os_pfn_free(USER_REG, pfn[0]);
            *pte_address[1] &= ~(1UL);
            asm ("invlpg (%0)" :: "r" (next_free) : "memory");
        }
    }
    segment->next_free = next_free;
    return next_free;
}

/* This function is used to get the segment where the virtual address belongs, returns -1 if it doesn't belong anywhere (checking in between valid ranges i.e. start and next_free) */

static int get_segment(u64 virtual_address, struct exec_context *ctx)
{
    if(virtual_address >= ctx->mms[MM_SEG_DATA].start && virtual_address < ctx->mms[MM_SEG_DATA].next_free)
        return MM_SEG_DATA;
    else if(virtual_address >= ctx->mms[MM_SEG_RODATA].start && virtual_address < ctx->mms[MM_SEG_RODATA].next_free)
        return MM_SEG_RODATA;
    else if(virtual_address >= ctx->mms[MM_SEG_STACK].start && virtual_address < ctx->mms[MM_SEG_STACK].end)
        return MM_SEG_STACK;
    else
        return -1;
}

/*System Call handler*/
u64 do_syscall(int syscall, u64 param1, u64 param2, u64 param3, u64 param4)
{
    struct exec_context *current = get_current_ctx();
    printf("[GemOS] System call invoked. syscall no  = %d\n", syscall);
    switch(syscall)
    {
          case SYSCALL_EXIT:
                              printf("[GemOS] exit code = %d\n", (int) param1);
                              do_exit();
                              break;
          case SYSCALL_GETPID:
                              printf("[GemOS] getpid called for process %s, with pid = %d\n", current->name, current->id);
                              return current->id;      
          case SYSCALL_WRITE:
                             {
                                 u64 virtual_address = param1, length = param2, iterator = 0, end_virtual_address = virtual_address+(length-1);
                                 if(length > 1024)
                                 {
                                     printf("The length is limited to 1024\n");
                                     do_exit();
                                 }
                                 
                                 // Checking start address and if the (address + length - 1) is in different page then checking that as well

                                 if(check_or_alloc_address(virtual_address, current, 0, -1) && ((virtual_address >> PAGE_SHIFT == end_virtual_address >> PAGE_SHIFT) || check_or_alloc_address(end_virtual_address, current, 0, -1)))
                                 {
                                    char *buf_address = virtual_address;
                                    for(iterator = 0; iterator < length; iterator++)
                                        printf("%c",*(buf_address + iterator));
                                    return iterator;
                                 }
                                 else
                                     return -1;
                             }
          case SYSCALL_EXPAND:
                             {
                                 u64 size = param1, flag = param2, iterator = 0, expanded_address;
                                 if(size > 512)
                                 {
                                     printf("The maximum value of size can be 512\n");
                                     do_exit();
                                 }
                                 if(flag != MAP_WR && flag != MAP_RD)
                                     return 0;
                                 expanded_address = (flag == MAP_RD) ? expand_segment(size, &current->mms[MM_SEG_RODATA]) : expand_segment(size, &current->mms[MM_SEG_DATA]);
                                 return expanded_address;
                             }
          case SYSCALL_SHRINK:
                             {
                                 u64 size = param1, flag = param2, iterator = 0, shrinked_address;
                                 if(flag != MAP_WR && flag != MAP_RD)
                                     return 0;
                                 shrinked_address = (flag == MAP_RD) ? shrink_segment(size, current->pgd, &current->mms[MM_SEG_RODATA]) : shrink_segment(size, current->pgd, &current->mms[MM_SEG_DATA]);
                                 return shrinked_address;
                             }
          default:
                              return -1;
    }
    return 0;   /*GCC shut up!*/
}

extern int handle_div_by_zero(void)
{
	u64 rip;
    asm volatile("mov 8(%%rbp), %0;" : "=r" (rip));
    printf("Div-by-zero detected at %x\n", rip);
    do_exit();
    return 0;  /*GCC shut up!*/
}

extern int handle_page_fault(void)
{
    // Pushing all the registers which are to be restored later into the stack and saving the stack pointer.
    u64 top_rsp_value;
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
                  mov %%rsp, %0;" : "=r" (top_rsp_value));

    printf("Page Fault Handler Invoked!\n");

    struct exec_context *current; 
    u64 error_code, virtual_address, rip, present_bit, access_bit, cpl_bit, segment;
    asm volatile("mov 8(%%rbp), %0;" : "=r" (error_code));
    asm volatile("mov 16(%%rbp), %0;" : "=r" (rip));
    asm volatile("mov %%cr2, %0;" : "=r" (virtual_address));
    present_bit = error_code & (0x1);
    access_bit = error_code & (0x2);
    cpl_bit = error_code & (0x4);
    current = get_current_ctx();

    if(present_bit)
    {
        printf("Protection Fault @ RIP = %x ; Error = %x ; UserVA = %x\n", rip, error_code, virtual_address);
        do_exit();
    }
    segment = get_segment(virtual_address, current);
    if(segment == -1)
    {
        printf("Error in Virtual Address @ RIP = %x ; Error = %x ; UserVA = %x\n", rip, error_code, virtual_address);
        do_exit();
    }
    if(segment == MM_SEG_RODATA && access_bit)
    {
        printf("Can't Write to Read-Only Data Segment @ RIP = %x ; Error = %x ; UserVA = %x\n", rip, error_code, virtual_address);
        do_exit();
    }

    // Since address is legitimate, we allocate the page for that address depending upon the segment access flags.
    check_or_alloc_address(virtual_address, current, 1, segment);

    // Restoring all the user registers, and setting the stack pointer at the value of the user RIP before calling return to user.
    asm volatile("mov %0, %%rsp;" :: "r" (top_rsp_value));
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
                   pop %%rax;        \    
                   mov %%rbp, %%rsp; \
                   pop %%rbp;        \
                   add $8, %%rsp;    \
                   iretq;"
                   ::);
    return 0;   /*GCC shut up!*/
}
