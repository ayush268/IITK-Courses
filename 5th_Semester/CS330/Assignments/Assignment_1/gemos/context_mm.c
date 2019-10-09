#include<context.h>
#include<memory.h>
#include<lib.h>

#define STACK 0
#define CODE 1
#define DATA 2

static void alloc(struct exec_context *ctx, struct mm_segment *seg, u64 start_addr, u32 segment)
{
  u32 bits = seg->access_flags;
  u32 offset[5];
  offset[4] = (start_addr >> 39) & (0x1FF);
  offset[3] = (start_addr >> 30) & (0x1FF);
  offset[2] = (start_addr >> 21) & (0x1FF);
  offset[1] = (start_addr >> 12) & (0x1FF);
  u64 *actual_addr[5], *addr[5], pte[5], pfn[5];
  pfn[4] = ctx->pgd; 
  addr[4] = (u64 *)(osmap(pfn[4]));
  for(int i=4; i>1; i--)
  {
    actual_addr[i] = addr[i]+offset[i];
    if(!(*actual_addr[i] & (0x1)))
    {
      pfn[i-1] = os_pfn_alloc(OS_PT_REG);
      addr[i-1] = (u64 *)(osmap(pfn[i-1]));
      for(u32 j=0;j<512;j++)
        *(addr[i-1]+j)=0;
      pte[i] = (pfn[i-1] << 12) | (0x005 | (bits & (0x2)));
      *(actual_addr[i]) = pte[i];
    }
    else
    {
      pfn[i-1] = *actual_addr[i] >> 12;
      addr[i-1] = (u64 *)(osmap(pfn[i-1]));
      *actual_addr[i] |= (0x005 | (bits & (0x2)));
    }
  }
  actual_addr[1] = addr[1]+offset[1];
  pfn[0] = (segment == DATA) ? ctx->arg_pfn : os_pfn_alloc(USER_REG);
  pte[1] = (pfn[0] << 12) | (0x005 | (bits &(0x2)));
  *(actual_addr[1]) = pte[1];
}

void prepare_context_mm(struct exec_context *ctx)
{
  u64 pfn = os_pfn_alloc(OS_PT_REG);
  ctx->pgd = pfn;
  u64 *addr = (u64*)osmap(pfn);
  for(u32 i=0;i<512;i++)
    *(addr+i)=0;
  alloc(ctx, &ctx->mms[MM_SEG_CODE], ctx->mms[MM_SEG_CODE].start, CODE);
  alloc(ctx, &ctx->mms[MM_SEG_STACK], ctx->mms[MM_SEG_STACK].end-0x1000, STACK);
  alloc(ctx, &ctx->mms[MM_SEG_DATA], ctx->mms[MM_SEG_DATA].start, DATA);
  return;
}

void cleanup_context_mm(struct exec_context *ctx)
{
  u64 start_addr[3];
  start_addr[0] = ctx->mms[MM_SEG_STACK].end-0x1000;
  start_addr[1] = ctx->mms[MM_SEG_CODE].start;
  start_addr[2] = ctx->mms[MM_SEG_DATA].start;
  u32 offset[3][5];
  for(int i=0;i<3;i++)
  {
    offset[i][4] = (start_addr[i] >> 39) & (0x1FF);
    offset[i][3] = (start_addr[i] >> 30) & (0x1FF);
    offset[i][2] = (start_addr[i] >> 21) & (0x1FF);
    offset[i][1] = (start_addr[i] >> 12) & (0x1FF);
  }
  u64 *actual_addr[5], *addr[5], pte[5], pfn[5];
  pfn[4] = ctx->pgd;
  addr[4] = (u64 *)(osmap(pfn[4]));
  for(int i=0;i<=4;i++)
    for(int j=0;j<3;j++)
      for(int k=4;k>=i;k--)
      {
        if(k==i && (i==0 || (*actual_addr[k+1] & (0x1))))
        {
          if(i==0) os_pfn_free(USER_REG, pfn[k]); else os_pfn_free(OS_PT_REG, pfn[k]);
          *actual_addr[k+1] &= ~(1UL);
          continue;
        }
        actual_addr[k] = addr[k]+offset[j][k];
        if(*actual_addr[k] & (0x1))
        {
          pfn[k-1] = *actual_addr[k] >> 12;
          addr[k-1] = (u64 *)(osmap(pfn[k-1]));
        }
      }
  os_pfn_free(OS_PT_REG, pfn[4]);
  return;
}
