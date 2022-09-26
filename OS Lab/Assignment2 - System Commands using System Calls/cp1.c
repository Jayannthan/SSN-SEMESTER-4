#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        printf("Opening file1:\n");
        int file_descriptor1 = open(argv[1], O_RDONLY);
        if (file_descriptor1 == -1)
            printf("Source File does not exist\n");
        else
        {
            char contents[100]; 
            printf("Reading file1:\n");
            int re=read(file_descriptor1, contents, 100);
            printf("Checking for i:\n");
            if(argc>3 && strcmp(argv[3],"i")==0)
            {
                printf("Found i:\n");
                printf("Creating file2:\n");
                
                int file_descriptor2=creat(argv[2],S_IRUSR | S_IWUSR);
                if(file_descriptor2<0)
                {
                    printf("!!!ERROR!!!\n");
                }
                else
                {
                    
                    printf("copying into file2:\n");
                    int wr=write(file_descriptor2,contents,sizeof(contents));
                    
                    printf("Closing file2:\n");
                    close(file_descriptor2);
                    printf("\nSuccessfully Copied\n");
                }
                close(file_descriptor1);
            }
            else
            {
                
                printf("i not found:\n");
                
                printf("Checking file2:\n");
                int file_descriptor2=open(argv[2],O_WRONLY);
                if(!(file_descriptor2<0))
                {
                    char ch;
        			printf("Overwrite %s file?(y/n) ",argv[2]);
        			scanf(" %c",&ch);
        			if(!(ch=='y'||ch=='Y'))
        			{
        				close(file_descriptor2);
                        close(file_descriptor1);
                        
        			}
                    else
                    {
                        
                    printf("Creating file2:\n");
                        int file_descriptor2=creat(argv[2],S_IRUSR | S_IWUSR);
                        if(file_descriptor2<0)
                        {
                            printf("!!!ERROR!!!\n");
                        }
                        else
                        {
                            
                    printf("writing into file2:\n");
                            int wr=write(file_descriptor2,contents,sizeof(contents));
                            close(file_descriptor2);
                            printf("\nSuccessfully Copied\n");
                        }
                        close(file_descriptor1);
                    }
		        }
                else
                {
                    printf("Creating file2:\n");
                
                int file_descriptor2=creat(argv[2],S_IRUSR | S_IWUSR);
                if(file_descriptor2<0)
                {
                    printf("!!!ERROR!!!\n");
                }
                else
                {
                    
                    printf("copying into file2:\n");
                    int wr=write(file_descriptor2,contents,sizeof(contents));
                    
                    printf("Closing file2:\n");
                    close(file_descriptor2);
                    printf("\nSuccessfully Copied\n");
                }
                close(file_descriptor1);
                }
            }
        }
    }
    return 0;
}