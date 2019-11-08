#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int i;
    char command[100];

    strcat(command, "./calculate");
    for (i = 1; i < argc; i++)
    {
        strcat(command, " ");
        strcat(command, argv[i]);
    }
    strcat(command, "\n");

    //printf("%s", command);
    system(command);
    return 0;
}
