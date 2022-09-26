/*Develop an application for getting a name in parent and convert it into uppercase in child using shared memory.*/
#include <sys/ipc.h>
# define NULL 0
#include <sys/shm.h>
#include <sys/types.h>
# include<unistd.h>
# include<stdio.h>
# include<string.h>
# include<stdlib.h>
# include<string.h>
#include <sys/wait.h>
#include <stdio_ext.h>
int main()
{
	// ftok to generate unique key
	int key = ftok("abc",67);

	// shmget returns an identifier in shmid
	int shmid = shmget(key,1024,0666|IPC_CREAT);

	// shmat to attach to shared memory
	char *str = (char*) shmat(shmid,(void*)0,0);

	printf("Data read from memory: %s\n",(str));
    
	for (int i = 0; str[i]!='\0'; i++)
	{
		if(str[i] >= 'a' && str[i] <= 'z')
		{
			str[i] = str[i] -32;
		}
	}
	printf("Data converted to uppercase: %s\n",(str));
    
	//detach from shared memory
	shmdt(str);
	
	// destroy the shared memory
	shmctl(shmid,IPC_RMID,NULL);
	
	return 0;
}
