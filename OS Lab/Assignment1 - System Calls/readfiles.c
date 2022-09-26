#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
int main(int argc, char *argv[])
{
    
    if (argc > 2)
        printf("Too many arguements\n");
    else if (argc < 1)
        printf("Atleast one arguement required\n");
    else
    {
        int file_descriptor = open(argv[1], O_RDONLY);
        if (file_descriptor == -1)
            printf("File does not exist\n");
        else
        {
            printf("File descriptor is: %d\n", file_descriptor);
            char contents[100]; 
            read(file_descriptor, contents, 100);
            printf("File contents : %s\n", contents);
            close(file_descriptor);
        }
    }
    return 0;
}