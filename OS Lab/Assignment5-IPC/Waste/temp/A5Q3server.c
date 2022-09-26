#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
struct Memory
{  int status;
   char m1[400];
   char m2[400];
};
int main(void)
{  int id,ch=0;
   struct Memory* mem;
   id=shmget(111,sizeof(struct Memory),IPC_CREAT|0666);
   if(id<0)
   {  printf("Error getting\n");
      return 0;
   }
   mem=(struct Memory*)shmat(id,0,0);
   if((int)mem==-1)
   {  printf("Error attaching\n");
      return 0;
   }
   mem->status=-1;
   mem->status=0;
   while(ch!=1)
   {  while(mem->status!=1)
        sleep(1);
      printf("Server: ");
      scanf("%[^\n]%*c",mem->m1);
      printf("Client: %s\n",mem->m2);
      scanf("%d",&ch);
      mem->status=0;
   }
   mem->status=0;
   shmdt((void*)mem);
   shmctl(id,IPC_RMID,0);
   return 0;
}
