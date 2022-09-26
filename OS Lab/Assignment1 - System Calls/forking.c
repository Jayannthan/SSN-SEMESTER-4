#include <stdio.h>
#include <unistd.h>
int main()
{
    printf("Before forking...\n\n");
    int id = fork();
    printf("After forking\n");
    if (id == 0)
        printf("Child process underway\n\n");
    else
        printf("Parent process underway\n\n");
    return 0;
}
