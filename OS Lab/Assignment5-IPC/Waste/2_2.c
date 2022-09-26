#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <unistd.h>

int main()
{
    // key_t key = ftok("file1", 100);
    int shmid = shmget(111, 1024, 0666 | IPC_CREAT);
    char *str = (char *)shmat(shmid, (void *)0, 0);
    printf("Content stored in the shared memory is : %s\n", str);

    shmdt(str);

    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}