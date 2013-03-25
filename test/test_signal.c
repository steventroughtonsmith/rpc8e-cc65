#include<signal.h>
#include<stdio.h>

void catch_function(int);

int main(void)
{
    if(signal(SIGINT, catch_function)==SIG_ERR)
    {
        printf("An error occured while setting a signal handler.\n");
        return 0;
    }

    printf("Raising the interactive attention signal.\n");
    if(raise(SIGINT)!=0)
    {
        printf("Error raising the signal.\n");
        return 0;
    }
    printf("Exiting.\n");
    return 0;
}

void catch_function(int signal)
{
    printf("Interactive attention signal caught.\n");
}

