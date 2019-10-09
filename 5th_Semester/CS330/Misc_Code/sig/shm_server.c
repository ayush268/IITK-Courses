#include  <stdio.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include  <string.h>

enum{
         EMPTY,
         READY,
         CLIENT_PENDING
};

main()
{
    key_t shm_key=0x8754;
    void *ptr;
    int *start;
    struct shmid_ds stat;
    int shm_id = shmget(shm_key, 4096, IPC_CREAT | 0666);    
    if(shm_id < 0){
            perror("shmget");
            exit(-1);
    }
    printf("Shared memory with key = %x created with handle=%x mypid=%d\n", shm_key, shm_id, getpid());
    ptr = shmat(shm_id, NULL, 0);
    if(ptr == (void *) -1){
           perror("shmat");
           exit(-1);
    }
    printf("%s VA to shm is @ %lx\n", __FILE__, (unsigned long)ptr);

    /*Message format is as follows, {status, size, message}*/
    start = (int*) ptr;
    *start = EMPTY;
    *(start + 1) = 16;

    strcpy((char *)ptr+8, "Server message!");
    *start = READY;
     
    while(*start != CLIENT_PENDING)
         usleep(1000);
     
    printf("Msg from client #%s\n", (char*)ptr + 8);

    /*SHM statistics*/
    #if 1
      if(shmctl(shm_id, IPC_STAT, &stat) < 0){
          perror("shmctl");
          exit(-1);
      }
     printf("creator pid=%d last attach pid=%d, #attached=%lu\n", stat.shm_cpid, stat.shm_lpid, stat.shm_nattch);
    #endif
    *start = EMPTY;
    shmdt(ptr);
    
    printf("I am detaching from SHM\n");
    shmctl(shm_id, IPC_RMID, NULL);
}
