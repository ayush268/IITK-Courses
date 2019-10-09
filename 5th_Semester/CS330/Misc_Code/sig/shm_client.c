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
    int shm_id = shmget(shm_key, 4096, 0666);    
    if(shm_id < 0){
            perror("shmget");
            exit(-1);
    }
    printf("Got an handle to shared memory with key = %x, handle=%x mypid=%d \n", shm_key, shm_id, getpid());
    ptr = shmat(shm_id, NULL, 0);
    if(ptr == (void *) -1){
           perror("shmat");
           exit(-1);
    }
    printf("%s VA to shm is @ %lx\n", __FILE__, (unsigned long)ptr);


    /*Message format is as follows, {status, size, message}*/
     
    start = (int*) ptr;
    while(*start != READY)
         usleep(1000);
     
    printf("Msg from server #%s\n", (char*)ptr + 8);
    
    strcpy((char *)ptr+8, "Client message!");
    *start = CLIENT_PENDING;
    while(*start != EMPTY)
         usleep(1000);
    shmdt(ptr);
}
