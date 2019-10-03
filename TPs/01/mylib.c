#include "mylib.h"

// sqrt için
#include "math.h"

// malloc için
#include "stdlib.h"

// printf için
#include "stdio.h"

// Void fonksiyonlar test edilebilisin diye türlerini değiştirdim

void fail()
{
    printf("\033[0;31m");
    printf(" FAILED\n");
    printf("\033[0m");
}

void pass()
{
    printf("\033[0;32m");
    printf(" PASSED\n");
    printf("\033[0m");
}

int isLetter(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return 1;
    return 0;
}

int isDigit(char c)
{
    if (c >= '0' && c <= '9')
        return 1;
    return 0;
}

int isEven(int value)
{
    if (!(value % 2))
        return 1;
    return 0;
}

int isPrime(int value)
{
    for (unsigned int i = 2; i < value; i++)
        if (!(value % i)) return 0;
    return 1;
}

int digitSum(int value)
{
    int sum = 0;
    int rem;
    while (value > 0)
    {
        rem = value % 10;
        sum += rem;
        value /= 10;
    } 
    return sum;
}

int reverseNumber(int value)
{
    // Lets have an int 132
    int reversed = 0;
    while (value != 0)
    {
        reversed *= 10;
        reversed += value % 10;
        value /= 10;
    }
    return reversed;
}

char upperCase(char c)
{
    if (c >= 'A' && c <= 'Z') return c;
    c += 'A' - 'a';
    return c;
}

char downcase(char c)
{
    if (c >= 'a' && c <= 'z') return c;
    c -= 'A' - 'a';
    return c;
}

int isUpperCase(char c)
{
    if (c >= 'A' && c <= 'Z')
        return 1;
    return 0;    
}

int factoriel(int value)
{
    int sum = 1;
    for (; value > 0; value--)
        sum *= value;
    return sum;
}

int power(int base, int degree)
{
    if (degree <= 0)
        return 1;
    return (base * power(base, degree - 1));
}

int add(int value1, int value2)
{
    return value1 + value2;
}

double* findRoots(int a , int b, int c)
{
    double delta = b*b - 4*a*c;
    double* results = malloc(sizeof(double) * 2);

    if (delta < 0)
    {
        results[0] = 0;
        results[1] = 0;
    } else
    {
        double root1 = (-b + sqrt(delta)) / (2*a);
        double root2 = (-b - sqrt(delta)) / (2*a);

        results[0] = root1;
        results[1] = root2;
    }

    return results;
}

int hailstoneNumbers(int value) // Bunu stack kullanmadan nasıl kontrol edeceğimi bulamadım
{
    while (value != 1)
    {
        if (value % 2)
            value /= 2;
        else
            value = 3 * value + 1;
    }
    return 1;
}

int isPalindromeNumber(int value)
{
    if (value == reverseNumber(value))
        return 1;
    return 0;
}

int isPalindromeText(char *c, int size)
{
    for (int i = 0; i < size / 2; i++)
        if (c[i] != c[size - i - 1])
            return 0;
    return 1;
}

int isVowel(char c)
{
    char vowels[] = {'a', 'e', 'i', 'o'};
    c = downcase(c); // Sanity and shorter array
    for (char i = 0; i < 4; i++)
        if (c == vowels[i])
            return 1;
    return 0;
}

int exist(int *arr, int size, int value)
{
    for (int i = 0; i < size; i++)
        if (arr[i] == value)
            return 1;
    return 0;    
}

int getIndex(int *arr, int size, int value)
{
    for (int i = 0; i < size; i++)
        if (arr[i] == value)
            return i;
    return -1;
}

int count(int *arr, int size, int value)
{
    int counter = 0;
    for (int i = 0; i < size; i++)
        if (arr[i] == value)
            counter++;
    return counter;
}