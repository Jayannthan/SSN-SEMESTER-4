#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
int main(int argc, char *argv[])
{
    if (argc > 4)
        printf("Too many arguements\n");
    else if (argc < 2)
        printf("Two arguements required\n");
    else
    {
        int file_descriptor = open(argv[2], O_RDONLY);
        if (file_descriptor == -1)
            printf("File does not exist\n");
        else
        {
            if (argc == 3)
            {
                // printf("Normal Grep\n");
                char line[100], buf[1024];
                int l = 0, i = 0, nr, count = 0;
                nr = read(file_descriptor, buf, 1024);
                close(file_descriptor);
                while (l < nr)
                {
                    for (i = 0; buf[l] != '\n' && l < nr; i++, l++)
                    {
                        line[i] = buf[l];
                    }
                    line[i] = '\0';
                    l++;
                    if (strstr(line, argv[1]))
                        printf("%s\n", line);
                }
            }
            else if (argc > 3 && strcmp(argv[3], "c")==0)
            {
                // printf("Grep -c\n");
                char line[100], buf[1024];
                int l = 0, i = 0, nr, count = 0;
                nr = read(file_descriptor, buf, 1024);
                close(file_descriptor);
                while (l < nr)
                {
                    for (i = 0; buf[l] != '\n' && l < nr; i++, l++)
                    {
                        line[i] = buf[l]; // extracting lines
                    }
                    line[i] = '\0';
                    l++;
                    if (strstr(line, argv[1]))
                    {
                        count++;
                    }
                }
                printf("%d\n", count);
            }
        }
    }
    return 0;
}