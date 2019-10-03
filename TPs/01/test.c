#include <stdio.h>
#include "mylib.h"

// to complile from terminal, run: gcc test.c mylib.c -o ApplicationName -lm
// to run the complied application, run: ./ApplicatioName

// use compile.sh script (it uses clang, can be changed to gcc)

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
    int i4 = 1023;

    // Test 1
    printf("Testing isLetter with %c: ", c1);
    if (isLetter(c1))
        pass();
    else fail();

    // test 2
    printf("Testing isDigit with %c: ", c3);
    if (isDigit(c3))
        pass();
    else fail();

    // test 3
    printf("Testing isEven with %d: ", i1);
    if (isEven(i1))
        pass();
    else fail();

    // test 4
    printf("Testing isPrime with %d: ", i3);
    if (isPrime(i3) == 0) // testing with 15 so needs to return false
        pass();
    else fail();

    // test 5
    printf("Testing digitSum with %d: ", i4);
    if (digitSum(i4) == 6)
        pass();
    else fail();

    // test 6
    printf("Testing reverseNumber with %d: ", i4);
    if (reverseNumber(i4) == 3201)
        pass();
    else fail();

    // test 7
    printf("Testing upperCase with %c: ", c1);
    if (upperCase(c1) == 'B')
        pass();
    else fail();

    // test 8
    printf("Testing downcase with %c: ", c2);
    if (downcase(c2) == 'g')
        pass();
    else fail();

    // test 9
    printf("Testing factoriel with %d: ", 5);
    if (factoriel(5) == 120)
        pass();
    else fail();

    // test 10
    printf("Testing power with %d and %d: ", i2, i1);
    if (power(i2, i1) == i2 * i2)
        pass();
    else fail();

    // test 11
    printf("Testing add with %d and %d: ", i2, i1);
    if (add(i2, i1) == i1 + i2)
        pass();
    else fail();

    // test 11
    printf("Testing findroots with %d, %d and %d: ", 1, -7, 12);
    double * results_roots = findRoots(1, -7, 12);
    if (results_roots[0] == 4 && results_roots[1] == 3)
        pass();
    else fail();
    
    return 0;
}
