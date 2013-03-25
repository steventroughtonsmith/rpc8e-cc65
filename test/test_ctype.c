#include <ctype.h>
#include <stdio.h>

void assert(int i)
{
    if (!i) {
        printf("  ***  Assert failed  ***  \n");
    }
}

int main(void)
{
    printf("\nTesting isalnum()\n");
    assert(isalnum('A')); 
    assert(isalnum('g'));
    assert(isalnum('5'));
    assert(!isalnum(' '));

    printf("Testing isalpha()\n");
    assert(isalpha('A')); 
    assert(isalpha('g'));
    assert(!isalpha('5'));
    assert(!isalpha(' '));

    printf("Testing iscntrl()\n");
    assert(!iscntrl('A')); 
    assert(!iscntrl('g'));
    assert(!iscntrl('5'));
    assert(iscntrl('\x10'));

    printf("Testing isdigit()\n");
    assert(!isdigit('A')); 
    assert(!isdigit('g'));
    assert(isdigit('5'));
    assert(!isdigit('\x10'));

    printf("Testing isgraph()\n");
    assert(isgraph('A')); 
    assert(!isgraph('\x20'));
    assert(isgraph('5'));
    assert(!isgraph('\x10'));

    printf("Testing islower()\n");
    assert(!islower('A')); 
    assert(islower('b'));
    assert(!islower('5'));
    assert(!islower('\x10'));

    printf("Testing isprint()\n");
    assert(isprint('A')); 
    assert(isprint('b'));
    assert(isprint(' '));
    assert(!isprint('\x10'));

    printf("Testing ispunct()\n");
    assert(!ispunct('A')); 
    assert(!ispunct('z'));
    assert(!ispunct(' '));
    assert(ispunct('.'));

    printf("Testing isspace()\n");
    assert(!isspace('A')); 
    assert(!isspace('z'));
    assert(isspace(' '));
    assert(isspace('\n'));

    printf("Testing isupper()\n");
    assert(isupper('A')); 
    assert(!isupper('z'));
    assert(!isupper(' '));
    assert(!isupper('\n'));

    printf("Testing isxdigit()\n");
    assert(isxdigit('A')); 
    assert(!isxdigit('z'));
    assert(!isxdigit(' '));
    assert(isxdigit('9'));

    printf("Testing tolower()\n");
    assert(tolower('A') == 'a'); 
    assert(tolower(' ') == ' ');
    assert(tolower('z') == 'z');
    assert(tolower('Z') == 'z');

    printf("Testing toupper()\n");
    assert(toupper('A') == 'A'); 
    assert(toupper(' ') == ' ');
    assert(toupper('z') == 'Z');
    assert(toupper('Z') == 'Z');

    return 0;
}
