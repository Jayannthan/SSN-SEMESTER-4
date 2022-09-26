#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
struct Memory
{  int status;
   FILE* fp;
};
int main(void)
{  int id;
   struct Memory* mem;
   id=shmget(111,sizeof(struct Memory),IPC_CREAT|0666);
   if(id<0)
   {  printf("Error\n");
      return 0;
   }
   mem=(struct Memory*)shmat(id,0,0);
   if((int)mem==-1)
   {  printf("Error\n");
      return 0;
   }
   mem->status=-1;
   mem->fp=fopen("file.txt","r+");
   mem->status=0;
   printf("Start client\n");
   while(mem->status!=1)
     sleep(1);
   shmdt((void*)mem);
   shmctl(id,IPC_RMID,0);
   return 0;
}
