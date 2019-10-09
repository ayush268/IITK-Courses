#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<pthread.h>
#include<sys/time.h>
#include<unistd.h>

#define THREADS 1
#define BLOCK_SIZE 64

#define TDIFF(start, end) ((end.tv_sec - start.tv_sec) * 1000000UL + (end.tv_usec - start.tv_usec))

pthread_mutex_t lock;
static char *dataptr;
static unsigned long *optr;


unsigned long calculate_and_store_hash(char *ptr, char *endptr)
{
    unsigned long hashval = 0;
    int count = BLOCK_SIZE/sizeof(unsigned long);
    while(count--){
         if((endptr - ptr) < sizeof(unsigned long))
                break;
         hashval += *((unsigned long *)ptr);
         ptr += sizeof(unsigned long);
    }
    sleep(1);
    return hashval;
}

void *hashit(void *arg)
/*Argument is the end pointer*/
{
   char *cptr;
   unsigned long *chash;
   char *endptr = (char *)arg;

   while(1){
        pthread_mutex_lock(&lock);
        if(dataptr >= endptr){
              pthread_mutex_unlock(&lock);
              break;
        }
        cptr = dataptr;
        dataptr += BLOCK_SIZE;
        
        chash = optr;
        optr++;
        pthread_mutex_unlock(&lock);
   
        /*Perform the real calculation*/
        *chash = calculate_and_store_hash(cptr, endptr); 
  }
  pthread_exit(NULL); 
}

int main(int argc, char **argv)
{
     int fd, ctr;
     unsigned long size, bytes_read = 0, hash_count;
     struct timeval start, end;
     char *buff, *cbuff;
     unsigned long *hashes;
     int num_threads;
     num_threads = atoi(argv[2]);
     pthread_t threads[num_threads];

    if(argc != 3){
            printf("Usage: %s <fileneme>\n", argv[0]);
            exit(-1);         
    }  
    fd = open(argv[1], O_RDONLY);
    if(fd < 0){
           printf("Can not open file\n");
           exit(-1);
    } 
    
    size = lseek(fd, 0, SEEK_END);
    if(size <= 0){
           perror("lseek");
           exit(-1);
    }
    
    if(lseek(fd, 0, SEEK_SET) != 0){
           perror("lseek");
           exit(-1);
    }
   
    buff = malloc(size);
    if(!buff){
           perror("mem");
           exit(-1);
    }   
   /*Read the complete file into buff
     XXX Better implemented using mmap */
   
    do{
         unsigned long bytes;
         cbuff = buff + bytes_read;
         bytes = read(fd, cbuff, size - bytes_read);
         if(bytes < 0){
             perror("read");
             exit(-1);
         }
        bytes_read += bytes;
     } while(size != bytes_read);

     hash_count = size / BLOCK_SIZE;
     if(size % BLOCK_SIZE)
          ++hash_count;

     hashes = malloc(sizeof(unsigned long) * hash_count);
     if(!hashes){
           perror("mem");
           exit(-1);
     }   
     
     dataptr = buff;
     optr = hashes;

     pthread_mutex_init(&lock, NULL);
  
     cbuff = buff + size;

     gettimeofday(&start, NULL);

     for(ctr=0; ctr < num_threads; ++ctr){
        if(pthread_create(&threads[ctr], NULL, hashit, cbuff) != 0){
              perror("pthread_create");
              exit(-1);
        }
 
     }
     
     for(ctr=0; ctr < num_threads; ++ctr)
           pthread_join(threads[ctr], NULL);
 
    
     for(ctr=0; ctr < hash_count; ++ctr)
           printf("block# %d hash %lx\n", ctr, hashes[ctr]);

     gettimeofday(&end, NULL);
     printf("Time taken = %ld microsecs\n", TDIFF(start, end));
     
     free(hashes);
     free(buff);
     close(fd);
}

