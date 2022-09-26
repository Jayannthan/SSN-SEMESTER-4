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
    if (signum == SIGUSR1)
    {
        printf("User2: ");
        puts(shmptr->buff);
    }
}

int main()
{
    int pid = getpid();
    int shmid = shmget(111, sizeof(struct memory), IPC_CREAT | 0666);
    shmptr = (struct memory *)shmat(shmid, NULL, 0);
    shmptr->pid1 = pid;
    shmptr->status = -1;
    signal(SIGUSR1, handler);
    while (1)
    {
        while (shmptr->status != 1)
            continue;
        sleep(1);
        printf("You: ");
        if (fgets(shmptr->buff, 100, stdin) != 0)
        {
            shmptr->status = 0;
            kill(shmptr->pid2, SIGUSR2);
        }
        else
        {
            printf("CHAT ENDED");
            shmdt((void *)shmptr);
            shmctl(shmid, IPC_RMID, NULL);
        }
    }
    shmdt((void *)shmptr);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
