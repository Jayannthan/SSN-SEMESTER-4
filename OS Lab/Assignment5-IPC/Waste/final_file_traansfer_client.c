
// A5Q2client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int shmid = shmget(101, 1024, 0666 | IPC_CREAT);
    char *str = (char *)shmat(shmid, (void *)0, 0);
    printf("Enter file name : ");
    scanf("%s", str);
    sleep(5);
    printf(" :\n%s", str);
    FILE *filepointer;
    filepointer = fopen("filecopy.txt", "w+");
    if (filepointer == NULL)
        printf("File could not be opened\n");
    else
    {
        filepointerrintf(filepointer, "%s", str);
        printf("File has been written\n");
        fclose(filepointer);
    }
    shmdt(str);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
