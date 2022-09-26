#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#define null 0
#define SIGUSR3 SIGWINCH

struct memory
{
    int status, id1, id2, id3;
    char buff[200];
};

struct memory *shmptr;

void client(int signum)
{
    if (signum == SIGUSR2)
    {
        printf("server:%32s\n", shmptr->buff);
    }
}

int main()
{

    char temp[500];

    int id = getpid();
    int shmid = shmget(111, sizeof(struct memory), IPC_CREAT | 0666);

    shmptr = (struct memory *)shmat(shmid, null, 0);

    shmptr->status = 1;
    shmptr->id2 = id;

    signal(SIGUSR2, client);

    printf("\nCHAT APP\n");

    do
    {
        fgets(shmptr->buff, 200, stdin);
        strcpy(temp, "1:");
        strcat(temp, shmptr->buff);
        strcpy(shmptr->buff, temp);
        kill(shmptr->id1, SIGUSR1);
    } while (1);

    shmdt((void *)shmptr);
    shmctl(shmid, IPC_RMID, null);
}
