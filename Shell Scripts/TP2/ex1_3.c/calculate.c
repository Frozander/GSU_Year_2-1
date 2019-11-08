#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int a = atoi(argv[1]);
    int b = atoi(argv[3]);


    if (strcmp(argv[2], "+"))
        printf("%d %s %d = %d", a, argv[2], b, a + b);
    if (strcmp(argv[2], "-"))
        printf("%d %s %d = %d", a, argv[2], b, a - b);
    if (strcmp(argv[2], "."))
        printf("%d %s %d = %d", a, argv[2], b, a * b);
    if (strcmp(argv[2], "/"))
    {
        if (b == 0)
        {
            printf("Division by 0!\n");
            return(1);
        }
        printf("%d %s %d = %d", a, argv[2], b, a / b);

    }
    if (strcmp(argv[2], "%"))
    {
        if (b == 0)
        {
            printf("Division by 0!\n");
            return(1);
        }
        printf("%d %s %d = %d", a, argv[2], b, a % b);
    }
    if (strcmp(argv[2], "<="))
        printf("%d %s %d = %d", a, argv[2], b, a <= b);
    if (strcmp(argv[2], "<"))
        printf("%d %s %d = %d", a, argv[2], b, a < b);
    if (strcmp(argv[2], ">"))
        printf("%d %s %d = %d", a, argv[2], b, a > b);
    if (strcmp(argv[2], ">="))
        printf("%d %s %d = %d", a, argv[2], b, a >= b);
    if (strcmp(argv[2], "=="))
        printf("%d %s %d = %d", a, argv[2], b, a == b);
    
    return 0;
}
