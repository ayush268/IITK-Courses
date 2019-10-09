#include<init.h>
#include<memory.h>
static void exit(int);
static int main(void);


void init_start()
{
  int retval = main();
  exit(0);
}

/*Invoke system call with no additional arguments*/

static int _syscall0(int syscall_num)
{
  asm volatile ( "int $0x80;"
                 "leaveq;"
                 "retq;"
                :::"memory");
  return 0;   /*gcc shutup!*/
}

/*Invoke system call with one argument*/

static int _syscall1(int syscall_num, int exit_code)
{
  asm volatile ( "int $0x80;"
                 "leaveq;"
                 "retq;"
                :::"memory");
  return 0;   /*gcc shutup!*/
}

/*Invoke system call with two arguments*/

static u64 _syscall2(int syscall_num, u64 arg1, u64 arg2)
{
  asm volatile ( "int $0x80;"
                 "leaveq;"
                 "retq;"
                :::"memory");
  return 0;   /*gcc shutup!*/
}


static u64 write(u64 address, int length)
{
  return(_syscall2(SYSCALL_WRITE, address, length));
}

static u64 expand(u32 size, int flags)
{
  return(_syscall2(SYSCALL_EXPAND, size, flags));
}

static u64 shrink(u32 size, int flags)
{
  return(_syscall2(SYSCALL_SHRINK, size, flags));
}

static void exit(int code)
{
  _syscall1(SYSCALL_EXIT, code); 
}

static int getpid()
{
  return(_syscall0(SYSCALL_GETPID));
}

static int main()
{

    /* Original instructions */

//  unsigned long i;
//#if 0
//  unsigned long *ptr = (unsigned long *)0x100032;
//  i = *ptr;
//#endif
//  i = getpid();
//  exit(-5);
//  return 0;


    /* My Test Cases */

  //  u64 i;
  //char *p = "Hi Man!\n";
  //p += 32000;
  //write(p, 1024);
  //i = 2/0;


    /* Siddant Test Case */

    //write("hello\n", 6);
    //char* ptr = ( char* ) expand(8, MAP_WR);
	//*(ptr + 4096) = 'X';
	//write(ptr+4096,1);
	//shrink(8, MAP_WR);
	//*(ptr + 4096) = 'A';
    //write(ptr+4096,1);

    //exit(0);

    /* Vinayak Test Cases */

  //  void *ptr1;
  //char *ptr = (char *) expand(20, MAP_WR);
  //
  //if(ptr == NULL)
  //            write("Expand FAILED\n", 7);
  //
  //*(ptr + 8192) = 'A';   /*Page fault will occur and handled successfully*/
  //
  //write(ptr+8192,1); /*check if value is written properly */

  //ptr1 = (char *) shrink(100, MAP_WR);

  //if(ptr1 != NULL)
  //    write("Shrink not working\n",18);


  //*ptr = 'A';          /*Page fault will occur and handled successfully*/

  //ptr1 = (char*)shrink(20,MAP_WR);


  //if(ptr1==NULL)
  //    write("shrink not working\n",18);

  //  /*Page fault will occur and PF handler should termminate 
  //                 the process (gemOS shell should be back) by printing an error message*/
  //char *ptr2 = (char *) expand(12, MAP_RD);

  //if(ptr2==NULL)
  //  write("expand not working\n",18);

  //ptr = (char*)expand(5,MAP_WR);

  //long k =write(ptr+1,1);   /*write should get failed*/

  //if(k!=-1)
  //  write("write not working\n",17);

  //k=write("Hello\n",7);

  //if(k!=-1)
  //  write("write working\n",14);

  //u64* t = (u64*)(0x7FF000000+16);
  //*t = 64;

  //if(*t == 64)
  //  write("stack page fault handled\n",25);

  //int* ptr3 = (int *) expand(20, MAP_RD);

  //int x=*(ptr3+1);

  //if(x==0){
  //  write("read only page fault handled\n",29);
  //}

  //*(ptr3+1023)  = 100;   /*page fault will occur and not handled successfully"*/

  //exit(0);

    /* Sir's sample testcase */

  //void *ptr1;
  //char *ptr = (char *) expand(8, MAP_WR);
  //
  //write("here\n", 5);
  //if(ptr == NULL)
  //            write("FAILED\n", 7);
  //
  //*(ptr + 9000) = 'A';   /*Page fault will occur and handled successfully*/
  //
  //write(ptr+8990, 12);
  //ptr1 = (char *) shrink(7, MAP_WR);
  //*ptr = 'A';          /*Page fault will occur and handled successfully*/

  //*(ptr + 4096) = 'A';   /*Page fault will occur and PF handler should termminate 
  //                 the process (gemOS shell should be back) by printing an error message*/
  //exit(0);

}
