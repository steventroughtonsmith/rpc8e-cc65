#include <limits.h>
#include <stdio.h>

int main(void)
{
    printf("CHAR_BIT: %d\n", CHAR_BIT);
    printf("SCHAR_MIN: %d\n", SCHAR_MIN);
    printf("SCHAR_MAX: %d\n", SCHAR_MAX);
    printf("UCHAR_MAX: %d\n", UCHAR_MAX);
    printf("CHAR_MIN: %d\n", CHAR_MIN);
    printf("CHAR_MAX: %d\n", CHAR_MAX);
    // MB_LEN_MAX is not defined
    //printf("MB_LEN_MAX: %d\n", MB_LEN_MAX);
    printf("SHRT_MIN: %d\n", SHRT_MIN);
    printf("SHRT_MAX: %d\n", SHRT_MAX);
    printf("USHRT_MAX: %d\n", USHRT_MAX);
    printf("INT_MIN: %d\n", INT_MIN);
    printf("INT_MAX: %d\n", INT_MAX);
    printf("UINT_MAX: %d\n", UINT_MAX);
    printf("LONG_MIN: %d\n", LONG_MIN);
    printf("LONG_MAX: %d\n", LONG_MAX);
    printf("ULONG_MAX: %d\n", ULONG_MAX);

    return 0;
}
