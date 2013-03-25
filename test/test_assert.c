#include <assert.h>
#include <stdio.h>

int main(void)
{
    printf("Testing assert(1)\n");
    assert(1);
    printf("Testing assert(NULL)\n");
    assert(NULL);
    printf("Testing finished\n");

    return 0;
}
