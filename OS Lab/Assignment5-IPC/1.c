#include <sys/ipc.h>
#define NULL 0
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio_ext.h>

int main()
{
    int pid = fork();
    if (pid == 0)
    {
        int shmid = shmget(111, 1024, 0666 | IPC_CREAT);
        char *str = (char *)shmat(shmid, (void *)0, 0);
        printf("Data to be written in memory:");

        fgets(str, 100, stdin);
        // printf("Data written in memory: %s\n", str);
        shmdt(str);
    }
    else
    {
        wait(NULL);
        int shmid = shmget(111, 1024, 0666 | IPC_CREAT);
        char *str = shmat(shmid, (void *)0, 0);
        printf("\nActual Data read from memory: %s\n", str);

        for (int i = 0; str[i] != '\0'; i++)
        {
            if (str[i] >= 'a' && str[i] <= 'z')
            {
                str[i] = str[i] - 32;
            }
        }

        printf("Data to be displayed from memory: %s\n", str);
        shmdt(str);
        shmctl(shmid, IPC_RMID, NULL);
    }
}
