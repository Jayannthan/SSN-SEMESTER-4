// A5Q2server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <unistd.h>
int main()
{
    int shmid = shmget(101, 1024, 0666 | IPC_CREAT);
    char *str = (char *)shmat(shmid, (void *)0, 0);
    printf("Waiting for client\n");
    while (str[0] == '\0')
        ;
    FILE *fp;
    fp = fopen(str, "r");
    if (fp == NULL)
        printf("File could not be opened\n");
    else
    {
        fseek(fp, 0, SEEK_END);
        int length = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        char c;
        int i = 0;
        while ((c = fgetc(fp)) != EOF)
        {
            str[i] = c;
            i++;
        }
        str[i] = '\0';
        fclose(fp);
        printf("Process completed\n");
    }
    shmdt(str);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
