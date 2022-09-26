#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
int main(int argc, char *argv[])
{
    if (argc > 2)
        printf("Too many arguements\n");
    else if (argc < 1)
        printf("Atleast one arguement required\n");
    else
    {
        DIR *dir;
        struct dirent *entry;
        if ((dir = opendir(argv[1])) == NULL)
        {
            printf("CANNOT OPEN GIVEN DIRECTORY");
        }
            else 
        {
            printf("Contents of the given:\n");
            while ((entry = readdir(dir)) != NULL)
            {
                printf("  %s\n", entry->);
            }
            closedir(dir);
      }
    }
    return 0;
}