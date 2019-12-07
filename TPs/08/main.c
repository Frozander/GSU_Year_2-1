#include <stdio.h>
#include <stdlib.h>

#include "encryption.h"
#include "tests.h"

int main(int argc, char const *argv[])
{
    if (argc == 2 && !strcmp(argv[1], "--test"))
        test();
    else printf("Usage: program --test\n");
    
    return 0;
}
