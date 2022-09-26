#include <stdio.h>
#include <semaphore.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <time.h>

#define BUFSIZE 5

struct memory
{
	int buffer[BUFSIZE];
	int count;
	sem_t full;
	sem_t empty;
	sem_t mutex;
	int n;
	int nstatus;
};

struct memory *shmptr;

int main()
{
	srand(time(0));
	int shmid = shmget(111, sizeof(struct memory), IPC_CREAT | 0666);
	shmptr = (struct memory *)shmat(shmid, NULL, 0);
	sem_init(&(shmptr->full), 1, 0);
	sem_init(&(shmptr->empty), 1, BUFSIZE);
	sem_init(&(shmptr->mutex), 1, 1);
	printf("\n-------Producer and Consumer Problem-------\n");
	if (shmptr->nstatus == 0)
	{
		printf("Number of items : ");
		scanf("%d", &(shmptr->n));
		shmptr->nstatus = 1;
	}

	int c = 0;
	do
	{

		sem_wait(&(shmptr->full));
		sem_wait(&(shmptr->mutex));
		printf("Available items : ");
		for (int i = 0; i < shmptr->count; i++)
		{

			printf("%d ", shmptr->buffer[i]);
		}
		printf("\n");

		printf("Consumed %d\n", shmptr->buffer[0]);

		memmove(shmptr->buffer, shmptr->buffer + 1, sizeof(shmptr->buffer));
		shmptr->count--;
		c++;

		sem_post(&(shmptr->mutex));
		sem_post(&(shmptr->empty));
		sleep(3);
	} while (c < shmptr->n);

	printf("\nAll items consumed\n");

	shmdt(shmptr);
	shmctl(shmid, IPC_RMID, NULL);
	sem_destroy(&(shmptr->empty));
	sem_destroy(&(shmptr->full));
	sem_destroy(&(shmptr->mutex));

	exit(1);
}