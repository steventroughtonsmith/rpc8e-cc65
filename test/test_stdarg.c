#include<stdarg.h>
#include<stdio.h>

void sum(char *, int, ...);

int main(void)
{
    sum("The sum of 10+15+13 is %d.\n",3,10,15,13);
    return 0;
}

void sum(char *string, int num_args, ...)
{
    int sum=0;
    va_list ap;
    int loop;

    va_start(ap,num_args);
    for(loop=0;loop<num_args;loop++)
        sum+=va_arg(ap,int);

    printf(string,sum);
    va_end(ap);
}

