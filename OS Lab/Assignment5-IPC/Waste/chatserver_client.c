#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

struct memory
{
    char buff[100];
    int status, pid1, pid2;
};

struct memory *shmptr;
void handler(int signum)
{
    if (signum == SIGUSR2)
    {
        printf("User1: ");
        puts(shmptr->buff);
    }
}

int main()
{
    int pid = getpid();
    int shmid = shmget(111, sizeof(struct memory), IPC_CREAT | 0666);
    shmptr = (struct memory *)shmat(shmid, NULL, 0);
    shmptr->pid2 = pid;
    shmptr->status = -1;
    signal(SIGUSR2, handler);
    while (1)
    {
        while (shmptr->status == 1)
            continue;
        sleep(1);
        printf("You: ");
        fgets(shmptr->buff, 100, stdin);
        shmptr->status = 1;
        kill(shmptr->pid1, SIGUSR1);
    }
    shmdt((void *)shmptr);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
