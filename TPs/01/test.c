#include <stdio.h>
#include "mylib.h"
//srand için
#include "stdlib.h"
#include "time.h"

// to complile from terminal, run: gcc test.c mylib.c -o ApplicationName -lm
// to run the complied application, run: ./ApplicatioName

// use compile.sh script (it uses clang, can be changed to gcc)

int main(void)
{
    // For randomness' sake
    srand(time(NULL));

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
    printf("Testing findRoots with %d, %d and %d: ", 1, -7, 12);
    double * results_roots = findRoots(1, -7, 12);
    if (results_roots[0] == 4 && results_roots[1] == 3)
        pass();
    else fail();

    // test 12
    printf("Testing hailstoneNumbers with %d: ", 5);
    if (hailstoneNumbers(5))
        pass();
    else fail();

    // test 13
    printf("Testing palindromeNumber with %d: ", 1221);
    if (isPalindromeNumber(1221))
        pass();
    else fail();

    // test 14
    printf("Testing palindromeText with %s: ", "racecar");
    if (isPalindromeText("racecar", 7))
        pass();
    else fail();

    // test 15
    printf("Testing isVowel with %c: ", 'a');
    if (isVowel('a'))
        pass();
    else fail();

    // Array for testing
    int my_arr[] = { 1, 0, 5, 6, 8, 8, 1, 0 };

    // test 16
    printf("Testing exist with %d: ", 5);
    if (exist(my_arr, 8, 5))
        pass();
    else fail();

    // test 17
    printf("Testing getIndex with %d: ", 0);
    if (getIndex(my_arr, 8, 0) == 1)
        pass();
    else fail();

    // test 18
    printf("Testing count with %d: ", 8);
    if (count(my_arr, 8, 8) == 2)
        pass();
    else fail();

    // test 19
    printf("Testing findMax with my_arr: ");
    if (my_arr[findMax(my_arr, 8)] == 8)
        pass();
    else fail();

    // test 20
    printf("Testing findMax2 with my_arr: ");
    if (my_arr[findMax2(my_arr, 8)] == 6)
        pass();
    else fail();

    // test 21
    printf("Testing findMin with my_arr: ");
    if (my_arr[findMin(my_arr, 8)] == 0)
        pass();
    else fail();

    // test 22
    printf("Testing findMin2 with my_arr: ");
    if (my_arr[findMin2(my_arr, 8)] == 1)
        pass();
    else fail();

    // test 23
    printf("Testing sumArray with my_arr: ");
    if (sumArray(my_arr, 8) == 29)
        pass();
    else fail();

    // test 24
    printf("Testing averageArr with my_arr: ");
    if (averageArr(my_arr, 8) == 29 / 8)
        pass();
    else fail();

    // test 25
    printf("Testing deviationArr with my_arr: ");
    double min_err = 3.2763356055203 - 1.1583595620532;
    double max_err = 3.2763356055203 + 1.1583595620532;
    if (deviationArr(my_arr, 8) >= min_err && deviationArr(my_arr, 8) <= max_err)
        pass();
    else fail();

    // Matrix for future tests
    int** matrix;
    int** mat_trans;

    // test 26
    printf("Testing fillMatrix: ");
    int tester = 1;
    matrix = fillMatrix(matrix, 3, 3);
    pass(); // Eğer segfault vermezse çalıştığından dolayı 'if' gerekmiyor

    printf("Testing printMatrix with 3x3 matrix: \n");
    printMatrix(matrix, 3, 3);

    printf("Testing transposeMatrix with 3x3 matrix: \n");
    mat_trans = transposeMatrix(matrix, 3, 3);
    printMatrix(mat_trans, 3, 3);

    pass();
    
    return 0;
}
