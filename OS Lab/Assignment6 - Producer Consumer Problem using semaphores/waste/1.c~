#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <sys/types.h>
#include <unistd.h>
extern int errno;
#define SIZE 10
#define SHMPERM 0666
int segid;
int empty_id;
int full_id;
int mutex_id;
char *buffer;
char *str;
sem_t *empty;
sem_t *full;
sem_t *mutex;
int p = 0, c = 0;

void produce()
{
    printf("\n!!!Producer %d starts!!!", getpid());

    int i = 0;
    while (1)
    {
        if (i >= strlen(str))
        {
            printf("\n!!!Producer %d exits!!!\n", getpid());
            wait(NULL);
            sleep(2);
            return;
        }
        printf("\n\tProducer %d acquires Empty ", getpid());
        sem_wait(empty);
        printf("\n\tProducer %d acquires Mutex ", getpid());
        sem_wait(mutex);
        buffer[p] = str[i];
        printf("\n\tProducer %d produced item : %c", getpid(), str[i]);
        i++;
        p++;
        printf("\n\tNo. of wriiten items in Buffer: %d", p);
        sem_post(mutex);
        printf("\n\tProducer %d released Mutex", getpid());
        sem_post(full);
        printf("\n\tProducer %d released Full", getpid());
        sleep(2);
    }
}

void consume()
{
    printf("\n!!!Consumer %d starts!!!", getpid());
    int i = 0;
    while (1)
    {
        if (i >= strlen(str))
        {
            printf("\n!!!Consumer %d exits!!!", getpid());
            sleep(2);
            return;
        }
        printf("\n\tConsumer %d acquires Full", getpid());
        sem_wait(full);
        printf("\n\tConsumer %d acquires Mutex", getpid());
        sem_wait(mutex);
        printf("\n\tConsumer %d consumed item : %c", getpid(), buffer[c]);
        buffer[c] = ' ';
        c++;
        printf("\n\tNo. of items read in Buffer: %d", c);
        i++;
        sem_post(mutex);
        printf("\n\tConsumer %d released  Mutex", getpid());
        sem_post(empty);
        printf("\n\tConsumer %d released  Empty", getpid());
        sleep(2);
    }
}

int main()
{
    printf("\n!!!Main starts!!!\n");
    pid_t m_pid;
    segid = shmget(IPC_PRIVATE, SIZE, IPC_CREAT | IPC_EXCL | SHMPERM);
    empty_id = shmget(IPC_PRIVATE, sizeof(sem_t), IPC_CREAT | IPC_EXCL | SHMPERM);
    full_id = shmget(IPC_PRIVATE, sizeof(sem_t), IPC_CREAT | IPC_EXCL | SHMPERM);
    mutex_id = shmget(IPC_PRIVATE, sizeof(sem_t), IPC_CREAT | IPC_EXCL | SHMPERM);
    buffer = shmat(segid, (char *)0, 0);
    empty = shmat(empty_id, (char *)0, 0);
    full = shmat(full_id, (char *)0, 0);
    mutex = shmat(mutex_id, (char *)0, 0);
    sem_init(empty, 1, SIZE);
    sem_init(full, 1, 0);
    sem_init(mutex, 1, 1);
    printf("\nEnter string for operation: ");
    str = (char *)malloc(20);
    scanf("%s", str);
    getchar();
    printf("\nString : %s\n", str);
    m_pid = fork();
    if (m_pid > 0)
    {
        produce();
    }
    else
    {
        consume();
    }
    shmdt(buffer);
    shmdt(empty);
    shmdt(full);
    shmdt(mutex);
    shmctl(segid, IPC_RMID, NULL);
    semctl(empty_id, 0, IPC_RMID, NULL);
    semctl(full_id, 0, IPC_RMID, NULL);
    semctl(mutex_id, 0, IPC_RMID, NULL);
    sem_destroy(empty);
    sem_destroy(full);
    sem_destroy(mutex);
    printf("\n!!!Main exits!!!\n");

    return (0);
}
