#include <stdio.h>
#include <stdlib.h>

#include "mylib.h"

int main(int argc, char const *argv[])
{
    double a, b;
    printf("Enter first number: ");
    scanf("%lf", &a);

    printf("Enter second number: ");
    scanf("%lf", &b);

    printf("The + of %.1lf and %.1lf is %.1lf\n", a, b, add(a, b));
    return 0;
}
