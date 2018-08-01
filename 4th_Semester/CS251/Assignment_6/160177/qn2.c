#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_THREADS 64

#define ACCOUNTS 10000

#define ERROR(s) printf("%s \n Usage: %s <path to initial accounts file> <path to transactions file> <no. of elements> <no. of threads>\n", s, argv[0]); exit(-1);

#define TDIFF(start, end) ((end.tv_sec - start.tv_sec) * 1000000UL + (end.tv_usec - start.tv_usec))

typedef struct account {
    int numb;
    double amt;
    int flag;
} acc;

typedef struct transaction {
    int type;
    double amt;
    int acc1;
    int acc2;
} trans;

acc *accounts;
trans *transactions;
pthread_mutex_t lock;
int trans_done = 0, num_trans;

void print(acc *a)
{
    for(int i=0;i<10000;i++)
        printf("%d %.2lf\n", 1001+i, a[i].amt);
}

void banking(int id, int type, int acc1, int acc2)
{
    switch(type)
    {
        case 1: accounts[acc1-1001].amt += (0.99 * transactions[id].amt);
                break;
        case 2: accounts[acc1-1001].amt -= (1.01 * transactions[id].amt);
                break;
        case 3: accounts[acc1-1001].amt *= 1.071;
                break;
        case 4: accounts[acc1-1001].amt -= (1.01 * transactions[id].amt);
                accounts[acc2-1001].amt += (0.99 * transactions[id].amt);
                break;
        default: printf("Invalid Type in a Transaction!\n");
                 exit(-1);
    }
}

void* bank(void *arg)
{
    int type, acc1, acc2, id;
    while(1)
    {
        pthread_mutex_lock(&lock);
        if(trans_done >= num_trans)
        {
            pthread_mutex_unlock(&lock);
            break;
        }

        acc1 = transactions[trans_done].acc1;
        acc2 = transactions[trans_done].acc2;
        type = transactions[trans_done].type;
        id = trans_done;

        if(accounts[acc1-1001].flag || (type == 4 && accounts[acc2-1001].flag))
        {
            pthread_mutex_unlock(&lock);
            continue;
        }

        trans_done++;
        accounts[acc1-1001].flag = 1;
        if(type == 4)
            accounts[acc2-1001].flag = 1;
        pthread_mutex_unlock(&lock);

        banking(id, type, acc1, acc2);

        pthread_mutex_lock(&lock);
        accounts[acc1-1001].flag = 0;
        if(type == 4)
            accounts[acc2-1001].flag = 0;
        pthread_mutex_unlock(&lock);
    }
}

int main(int argc, char **argv)
{
    int i;
    FILE *f;
    int num_threads, scrap;
    struct timeval start, end;

    if(argc != 5)
    {
        ERROR("invalid number of parameters");
    }
    
    num_threads = atoi(argv[4]);
    if(num_threads <= 0 || num_threads > MAX_THREADS)
    {
        ERROR("invalid number of threads");
    }
    pthread_t threads[num_threads];

    accounts = malloc(ACCOUNTS * sizeof(acc));

    // Reading accounts
    i = 0;
    f = fopen(argv[1], "r");
    while(i<10000)
    {
        fscanf(f, "%d %lf", &accounts[i].numb, &accounts[i].amt);
        accounts[i].flag = 0;
        i++;
    }
    fclose(f);

    num_trans = atoi(argv[3]);
    if(num_trans <= 0)
    {
        print(accounts);
        exit(0);
    }

    transactions = malloc(num_trans * sizeof(trans));
    if(!transactions)
    {
        ERROR("Invalid number of transactions, memory is not enough");
    }

    // Reading transactions
    i = 0;
    f = fopen(argv[2], "r");
    while(i<num_trans)
    {
        fscanf(f, "%d %d %lf %d %d", &scrap, &transactions[i].type, &transactions[i].amt, &transactions[i].acc1, &transactions[i].acc2);
        i++;
    }
    fclose(f);

    pthread_mutex_init(&lock, NULL);

    gettimeofday(&start, NULL);

    for(i=0;i<num_threads;i++)
    {
        if(pthread_create(&threads[i], NULL, bank, NULL) != 0)
        {
            perror("pthread_create");
            exit(-1);
        }
    }

    for(i=0;i<num_threads;i++)
        pthread_join(threads[i], NULL);

    print(accounts);

    gettimeofday(&end, NULL);
    printf("Time taken = %ld microsecs\n", TDIFF(start, end));

    free(accounts);
    free(transactions);

    return 0;
}
