#include <stdio.h>
#include <math.h>
#include "mylib.h"

// to complile from terminal, run: gcc test.c mylib.c -o ApplicationName -lm
// to run the complied application, run: ./ApplicatioName

int main(void)
{
    // a remplir

    // Test 1
    char c1 = 'b';
    char c2 = 'G';
    char c3 = '1';
    int i1 = 2;
    int i2 = 13;
    int i3 = 15;

    // Test 1
    printf("Testing isLetter with %c: "), c1;
    if (isLetter(c1))
        printf(" PASSED\n");
    else printf(" FAILED\n");

    // test 2
    printf("Testing isDigit with %c: ", c3);
    if (isDigit(c3))
        printf(" PASSED\n");
    else printf(" FAILED\n");

    // test 3
    printf("Testing isEven with %d: ", i1);
    if (isEven(i1))
        printf(" PASSED\n");
    else printf(" FAILED\n");

    // test 4
    printf("Testing isEven with %d: ", i1);
    if (isEven(i1))
        printf(" PASSED\n");
    else printf(" FAILED\n");
    
    return 0;
}
