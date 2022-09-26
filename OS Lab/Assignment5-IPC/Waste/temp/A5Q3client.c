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
   char buff[200];
   struct Memory* mem;
   id=shmget(111,sizeof(struct Memory),00666);
   if(id<0)
   {  printf("Error\n");
      return 0;
   }
   mem=(struct Memory*)shmat(id,0,0);
   if((int)mem==-1)
   {  printf("Error\n");
      return 0;
   }
   while(ch!=1)
   {  while(mem->status!=0)
        sleep(1);
      printf("Server: %s\n",mem->m1);
      printf("Client: ");
      scanf("%[^\n]%*c",mem->m2);
      scanf("%d",&ch);
      mem->status=1;
   }
   shmdt((void*) mem);
   shmctl(id,IPC_RMID,0);
   return 0;
}
