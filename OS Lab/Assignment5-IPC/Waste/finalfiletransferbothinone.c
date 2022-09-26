#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <unistd.h>
#include <fcntl.h>
#include<sys/wait.h>

int main() {

        int shmid = shmget(1,50,666|IPC_CREAT);
        char *str = (char*)shmat(shmid,(void*)0,0);

        printf("Enter file name : ");
        scanf("%s",str);

        printf("Waiting for file content from server...\n");
        sleep(1);

        if (strcmp(str, "File not found") == 0) {
                printf("File not found\n");
        }
        else {
                printf("Content received\n");
                printf("File Contents :\n%s",str);

                int fp;
                fp = creat("/root/file/tmp/content.txt", S_IRUSR|S_IWUSR);
                write(fp, str, sizeof(str));
                close(fp);
                printf("File written successfully!\n");
        }
        shmdt(str);

        shmctl(shmid,IPC_RMID, NULL);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <unistd.h>

int main() {

        int shmid = shmget(1,50,666|IPC_CREAT);
        char *str = (char*)shmat(shmid,(void*)0,0);

        while (str[0] == '\0');

        printf("File name received\n");

        FILE *fp;
        fp = fopen(str, "r");
        if (fp == NULL) {
                strcpy(str, "File not found\n");
        } else {
                printf("Reading the file...\n");
                char c;
                int i=0;
                while((c = fgetc(fp)) != EOF){
                        str[i] = c;
                        i++;
                }
                str[i] = '\0';
                printf("File content fetched successfully!\n");
                fclose(fp);
            }
    }