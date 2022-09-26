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
   char buff[200];
   struct Memory* mem;
   FILE* fp1=fopen("newfile.txt","w");
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
   while(mem->status!=0)
     sleep(1);
   while(fscanf(mem->fp,"%s",buff)!=EOF)
   {  printf("%s",buff); 
      fprintf(fp1,buff);
   }
   fclose(fp1);
   fclose(mem->fp);
   shmdt((void*) mem);
   shmctl(id,IPC_RMID,0);
   mem->status=1;
   return 0;
}
