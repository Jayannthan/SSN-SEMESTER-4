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

    char f_name[30];
    printf("Enter the file name : ");
    int s = scanf("%s", f_name);
    FILE *fd;
    fd = fopen(f_name, "r");
    fseek(fd, 0, SEEK_END);
    int len = ftell(fd);
    fseek(fd, 0, SEEK_SET);
    char ch;
    int i = 0;
    while ((ch = fgetc(fd)) != EOF)
    {
        *(str + i) = ch;
        i++;
    }
    *(str + i) = '\0';
    fclose(fd);

    printf("Data stored in shared memory :  %s\n", str);

    shmdt(str);
    return 0;
}