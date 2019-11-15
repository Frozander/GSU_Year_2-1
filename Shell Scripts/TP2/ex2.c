#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sys/auxv.h"

#define TAILLE_MAX 10

void fill_array(size_t n, int *arr)
{
    size_t i;
    for (i = 0; i < n; ++i) arr[i] = rand() % 11;
}

void search(size_t n, int *arr, int pivot)
{
    size_t n_2 = n / 2;
    if (!n) return;
    printf("search %d...\n", pivot);
    if (n_2 >= 1) 
    {
        __pid_t pid;
        pid = fork();
        if (pid < 0)
        {
        fprintf(stderr, "ERROR: fork failed!\n");
        return;
        }
        if (pid == 0) 
        {
        size_t i;
        for (i = n_2; i < TAILLE_MAX; ++i) 
        {
            if (arr[i] == pivot) break;
        }
        if (i < n) 
        {
            printf("Hit %d (found in parent)\n", (int)i);
        }
        } else
        {
        size_t i;
        for (i = 0; i < n_2; ++i) 
        {
            if (arr[i] == pivot) break;
        }
        if (i < n_2) 
        {
            printf("Hit %d (found in child)\n", (int)i);
        }
        exit(0);
        }
    } else 
    {
        if (arr[0] == pivot)
        {
        printf("Hit 0 (found)\n");
        }
    }
}


int main(int argc, char const *argv[])
{
    unsigned int *seed;
    seed = (unsigned int *)getauxval(AT_RANDOM);
    srand(*seed);

    int *my_arr;
    size_t array_size = 20;

    my_arr = malloc(array_size * sizeof(int));

    fill_array(array_size, my_arr);

    search(array_size, my_arr, 3);
    search(array_size, my_arr, 4);

    free(my_arr);

    return 0;
}