#include "mylib.h"

// malloc için

// I would just inline most of these functions for performance sake
// Void fonksiyonlar test edilebilisin diye türlerini değiştirdim

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
    int exp = 1;
    int sum = 0;
    int remaining = value % exp;

    while (!(remaining == value))
    {
        sum += remaining;
        exp *= 10;
        remaining = value % exp;
    } 
    return sum;
}

int reverseNumber(int value)
{
    return 0;
}

void upperCase(char c)
{
    c += 'a' - 'A';
}

void downcase(char c)
{
    c -= 'a' - 'A';
}

int isUpperCase(char c)
{
    if (c >= 'A' && c <= 'Z')
        return 1;
    return 0;    
}

int factorial(int value)
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
        results[0] = 0;
    } else
    {
        double root1 = (-b + sqrt(delta)) / (2*a);
        double root2 = (-b - sqrt(delta)) / (2*a);

        results[0] = root1;
        results[1] = root2;
    }

    return results;
}