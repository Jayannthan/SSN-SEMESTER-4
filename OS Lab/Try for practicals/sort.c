#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        printf("Check args");
        exit(0);
    }
    int pid = fork();
    if (pid == 0)
    {
        if (argc == 3)
        {
            int fd = open(argv[1], O_RDONLY);
            if (fd == -1)
            {
                printf("File cannot be read");
                exit(0);
            }
            char content[100][100], character;
            int i = 0, l = 0;
            while (read(fd, &character, sizeof(char)) != 0)
            {
                if (character != '\n')
                {
                    content[l][i] = character;
                    i++;
                }
                else
                {
                    content[l][i] = '\0';
                    l++;
                    i = 0;
                }
            }
            for (int j = 1; j < l; j++)
            {
                for (int k = 0; k < (l - j); k++)
                {
                    if (strcmp(content[k + 1], content[k]) < 0)
                    {
                        char s[100];
                        strcpy(s, content[k]);
                        strcpy(content[k], content[k + 1]);
                        strcpy(content[k + 1], s);
                    }
                }
            }
            for (int k = 0; k <= l; k++)
            {
                printf("%s\n", content[k]);
            }
        }
    }
    else if (pid > 0)
    {
        wait(NULL);
        if (argc == 4 && argv[3][0] == r)
        {
            int fd = open(argv[1], O_RDONLY);
            if (fd == -1)
            {
                printf("File cannot be read");
                exit(0);
            }
            char content[100][100], character;
            int i = 0, l = 0;
            while (read(fd, &character, sizeof(char)) != 0)
            {
                if (character != '\n')
                {
                    content[l][i] = character;
                    i++;
                }
                else
                {
                    content[l][i] = '\0';
                    l++;
                    i = 0;
                }
            }
            for (int j = 1; j < l; j++)
            {
                for (int k = 0; k < (l - j); k++)
                {
                    if (strcmp(content[k + 1], content[k]) > 0)
                    {
                        char s[100];
                        strcpy(s, content[k]);
                        strcpy(content[k], content[k + 1]);
                        strcpy(content[k + 1], s);
                    }
                }
            }
            for (int k = 0; k <= l; k++)
            {
                printf("%s\n", content[k]);
            }
        }
    }
}