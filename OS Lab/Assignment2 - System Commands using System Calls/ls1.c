#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>

DIR *dir,*temp;
struct dirent *tmp;
void recursive(struct dirent *entry)
{
    if (entry == NULL)
    {
        return;
    }
    
    recursive(readdir(dir));
    printf("  %s\n", entry->d_name);
}

void normal(struct dirent *entry, int n)
{
    if (entry == NULL)
    {
        return;
    }
    for (int i = 0; i < n; i++)
    {
        printf("\t");
    }
    
    printf("  %s\n", entry->d_name);
    
    if (entry->d_type == DT_DIR && !(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 || (entry->d_name[0] == '.')))
    {
        temp = opendir(entry->d_name);
        tmp = readdir(temp);
        normal(&tmp, n + 1);
        closedir(temp);
    }
    normal(readdir(dir), n); 
}

int main(int argc, char *argv[])
{
    if (argc > 4)
        printf("Too many arguements\n");
    else if (argc < 1)
        printf("Atleast one arguement required\n");
    else
    {
        // printf("%d\n",argc);
        if (argc == 2)
        {
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
                    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 || (entry->d_name[0] == '.'))
                        continue;
                    printf("  %s\n", entry->d_name);
                }
                closedir(dir);
            }
        }
        else if (argc > 1 && strcmp(argv[2], "r") == 0)
        {
            // printf("ls -R\n");
            struct dirent *entry;
            if ((dir = opendir(argv[1])) == NULL)
            {
                printf("CANNOT OPEN GIVEN DIRECTORY");
            }
            else
            {
                printf("Contents of the given:\n");
                recursive(&entry);
                closedir(dir);
            }
        }
        else if (argc > 1 && strcmp(argv[2], "a") == 0)
        {
            // DIR *dir;
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
                    printf("  %s\n", entry->d_name);
                }
                closedir(dir);
            }
        }
        else if (argc > 1 && strcmp(argv[2], "R") == 0)
        {
            // DIR *dir;
            struct dirent *entry;
            if ((dir = opendir(argv[1])) == NULL)
            {
                printf("CANNOT OPEN GIVEN DIRECTORY");
            }
            else
            {
                printf("Contents of the given:\n");
                if((entry = readdir(dir)) != NULL)
                {
                    normal(&entry,0);
                }
                
                closedir(dir);
            }
        }
    }
    return 0;
}