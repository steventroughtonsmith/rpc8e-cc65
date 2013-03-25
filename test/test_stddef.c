#include<stddef.h>
#include<stdio.h>

int main(void)
{
  struct user{
     char name[50];
     char alias[50];
     int level;
  };

  printf("level is the %d byte in the user structure.\n",
          offsetof(struct user,level));

  return 0;
}

