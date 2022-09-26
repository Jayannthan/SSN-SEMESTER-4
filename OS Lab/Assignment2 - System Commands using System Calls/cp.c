#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
int main(int argc, char *argv[])
{
    if (argc > 4)
        printf("Too many arguements\n");
    else if (argc < 2)
        printf("Atleast Two arguements required\n");
    else
    {
        int file_descriptor1 = open(argv[1], O_RDONLY);
        if (file_descriptor1 == -1)
            printf("Source File does not exist\n");
        else
        {
           
            char contents[100]; 
            int re=read(file_descriptor1, contents, 100);
            int file_descriptor2=creat(argv[2],S_IRUSR | S_IWUSR);
            if(file_descriptor2<0)
            {
                printf("!!!ERROR!!!\n");
            }
            else
            {
                int wr=write(file_descriptor2,contents,sizeof(contents));
                close(file_descriptor2);
                printf("\nSuccessfully Copied\n");
            }
            close(file_descriptor1);
        }
    }
    return 0;
}