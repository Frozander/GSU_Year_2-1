#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "sorting.h"
#include "benchmark.h"

int main(int argc, char const *argv[])
{
    /*
    * Question 1-2-3 are done in benchmark.c
    * benchmark.c can test each algorithm
    * for all 9 arrays.
    */

    srand(clock());

    SortMethod all_methods[] = {
    {.name = "bubble_sort"      , .fptr = bubble_sort},
    {.name = "selection_sort"   , .fptr = selection_sort},
    {.name = "insertion_sort"   , .fptr = insertion_sort},
    {.name = "quick_sort"       , .fptr = qsort_wrapper},
    {.name = "shell_sort"       , .fptr = shell_sort},
    {.name = "merge_sort"       , .fptr = mergesort_wrapper},
    {.name = "bucket_sort"      , .fptr = bucket_sort}
    };

    int n = 7;

    for (int i = 0; i < n; ++i)
    benchmark(all_methods[i], 1);
    


    return 0;
}
