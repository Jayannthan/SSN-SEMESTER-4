#include <stdio.h>
#include <unistd.h>
int main()
{
    printf("Before forking- this line is printed once\n\n");
    int id = fork();
    printf("After forking\n");
    if (id == 0)
        printf("Child process underway- executed after parent\n\n");
    else
        printf("Parent process underway- executed first\n\n");
    return 0;
}
