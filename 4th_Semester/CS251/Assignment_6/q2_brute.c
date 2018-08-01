#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<pthread.h>
#include<assert.h>

#define fill(a) (memset((a), 0, sizeof (a)))
#define rep(i,n) for(int i=0;i<(n);++i)
#define repA(i,a,n) for(int i=(a);i<=(n);++i)
#define repD(i,a,n) for(int i=(a);i>=(n);--i)

const int MAX_THREADS=64;
const int MAX=11009;
int nt=1,THREADS=1;

pthread_mutex_t lock;
int cur=0;

struct thread_param{
  pthread_t tid;
  int num;
  int pos;
};
struct account {
  int id;
  double m;
  int use;
};
struct transaction {
  int ty;
  double m;
  int a,b;
};
struct transaction *txn;//variable
struct account acc[11009];


void calculate_and_execute(struct transaction *trans, struct account *a,struct account *b){
  if(trans->ty==1)a->m+=trans->m*0.99000000000000000000000000000;
  else if(trans->ty==2)a->m-=trans->m*1.0100000000000000000000000000;
  else if(trans->ty==3)a->m*=1.071000000000000000000000000000;
  else if(trans->ty==4){
    a->m-=trans->m*1.0100000000000000000000000000;
    b->m+=trans->m*0.99000000000000000000000000000;
  }
}

void brute_force(){
  struct transaction trans;
  struct account a1,b1;

  rep(i,nt){
    trans=txn[i];

    int ia = trans.a,ib;
    if(trans.ty == 4)
        ib = trans.b;

    double a1 = acc[ia].m;
    double b1;
    if(trans.ty == 4)
        b1=acc[ib].m;

    double mm = txn[i].m;

 //   if(a1-acc[ia].m>0.01||a1-acc[ia].m < -0.01)printf("ouch\n");

    assert(trans.ty <= 4 && trans.ty >= 1);

    if(trans.ty==1){
      acc[ia].m += mm*0.99;

      a1 += mm*0.99;
    }
    else if(trans.ty==2){
      acc[ia].m -= mm*1.01;

      a1 -= mm*1.01;
    }
    else if(trans.ty==3){
      acc[ia].m *= 1.071;

      a1 *= 1.071;
    }
    else if(trans.ty==4){

      acc[ia].m -= mm*1.01;
      acc[ib].m += mm*0.99;

      a1 -= mm*1.01;
      b1 += mm*0.99;
    }

    if(acc[ia].m-a1>0.01 || acc[ia].m-a1< -0.01) 
         printf("%.4lf %.4lf\n",acc[ia].m,a1);
    /*if(trans.ty == 4)
    {
        if(acc[ib].m-b1>0.01||acc[ib].m-b1< -0.01)
               printf("%.4lf %.4lf\n",acc[ib].m,b1);
    }*/
  }
}

void readAcc(char* file,int num){
  FILE* facc;
  facc = fopen(file, "r");
  if(facc==NULL){printf("Can not open account file\n");exit(-1);}

  int i=0,tt=0,iid=0;
  fscanf(facc, "%d", &iid);acc[iid].id=iid;
  fscanf(facc, "%lf", &acc[iid].m);
  acc[iid].use=0;
  // printf("first->%d::%lf\n",acc[iid].id,acc[iid].m);
  // printf("%d %.2lf\n",acc[iid].id,acc[iid].m);
  i++;
  while (!feof(facc)&&i<num)
  {
    fscanf(facc, "%d", &iid);acc[iid].id=iid;
    if(iid==0){printf("Not enough accounts in file\n");exit(-1);}
    fscanf(facc, "%lf", &acc[iid].m);
    acc[iid].use=0;
    // printf("%d %.2lf\n",acc[iid].id,acc[iid].m);
    i++;
  }
  // printf("last->%d::%lf\n",acc[iid].id,acc[iid].m);
  if(i<num){printf("Not enough accounts in file\n");exit(-1);}

  fclose(facc);
}
void readTrans(char* file,int num){
  nt=num;
  FILE * ftxn;
  ftxn = fopen(file, "r");
  if(ftxn==NULL){printf("Can not open transaction file\n");exit(-1);}

  int i=0,tt=0;
  fscanf (ftxn, "%d", &tt);//tmp value
  fscanf(ftxn, "%d", &txn[i].ty);
  fscanf(ftxn, "%lf", &txn[i].m);
  fscanf(ftxn, "%d", &txn[i].a);
  fscanf(ftxn, "%d", &txn[i].b);
  // printf("%d %d %.2lf %d %d\n",tt,txn[i].ty,txn[i].m,txn[i].a,txn[i].b);
  i++;
  while (!feof(ftxn)&&i<num)
  {
    fscanf (ftxn, "%d", &tt);//tmp value
    if(tt==0){printf("Not enough transactions in file\n");exit(-1);}
    fscanf(ftxn, "%d", &txn[i].ty);
    fscanf(ftxn, "%lf", &txn[i].m);
    fscanf(ftxn, "%d", &txn[i].a);
    fscanf(ftxn, "%d", &txn[i].b);
    // printf("%d %d %.2lf %d %d\n",tt,txn[i].ty,txn[i].m,txn[i].a,txn[i].b);
    i++;
  }
  if(i<num){printf("Not enough transactions in file\n");exit(-1);}
  fclose(ftxn);
}

int main(int argc, char **argv)
{
    if(argc!=5){printf("Usage: %s <accounts> <transaction> #transaction #threads\n", argv[0]);exit(-1);}
    rep(i,MAX)acc[i].id=0,acc[i].m=0,acc[i].use=0;
    readAcc(argv[1],10000);



    txn=(struct transaction*)malloc((atoi(argv[3])+1)*sizeof(struct transaction));
    if(txn==NULL){perror("mem");exit(-1);}
    readTrans(argv[2],atoi(argv[3]));

    THREADS=atoi(argv[4]);
    if(THREADS>MAX_THREADS){printf("Use less than %d threads.\n",MAX_THREADS);exit(-1);}

    brute_force();

    FILE* out=fopen("output_brute1.txt","w");
    rep(i,MAX)if(acc[i].id!=0)fprintf(out, "%d %.2lf\n",acc[i].id,acc[i].m);
    fclose(out);
    free(txn);

    return 0;
}
