#include <stdio.h>

#include <unistd.h>

#include <stdlib.h>

#include <errno.h>

#include <sys/types.h>
// #include <sys/wait.h>

int main()
{

    int i, pid;
    pid = fork();

    if (pid == -1)
    {

        printf("fork failed");

        exit(0);
    }
    else if (pid == 0)
    {

        printf("\n child process starts");

        for (i = 0; i < 5;i++)
        {

            printf("\n child process d is called ", 1);
        }
        printf("\n child process ends");
    }
    else
    {

        wait(0);
        printf("\n Parent process ends");
    }

    exit(0);
}