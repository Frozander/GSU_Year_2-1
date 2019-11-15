#include <stdio.h>
#include <unistd.h>

void main(void)
{
    int i;
    while(1)
        printf("\nJe suis le programme qui boucle PID: %d\n", getpid());
}