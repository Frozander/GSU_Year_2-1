#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#include "encryption.h"
#include "tests.h"

unsigned long mix(unsigned long a, unsigned long b, unsigned long c)
{
    a=a-b;  a=a-c;  a=a^(c >> 13);
    b=b-c;  b=b-a;  b=b^(a << 8);
    c=c-a;  c=c-b;  c=c^(b >> 13);
    a=a-b;  a=a-c;  a=a^(c >> 12);
    b=b-c;  b=b-a;  b=b^(a << 16);
    c=c-a;  c=c-b;  c=c^(b >> 5);
    a=a-b;  a=a-c;  a=a^(c >> 3);
    b=b-c;  b=b-a;  b=b^(a << 10);
    c=c-a;  c=c-b;  c=c^(b >> 15);
    return c;
}

int main(int argc, char const *argv[])
{
    unsigned long seed = mix(clock(), time(NULL), getpid());
    srand(seed);

    if (argc == 2 && !strcmp(argv[1], "--test"))
        test();
    else printf("Usage: program --test\n");

    return 0;
}
