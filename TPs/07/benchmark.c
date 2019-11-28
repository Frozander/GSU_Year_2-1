#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <assert.h>

#include "benchmark.h"

int arrays_equal(int *sorted, int *answer, int size) {
    int i;
    for (i = 0; i < size; ++i) {
        if (sorted[i] != answer[i]) {
            return 0;
        }
    }
    return 1;
}

void print_array(int *array, int size) {
    int i;
    for (i = 0; i < size; ++i) {
        printf("%5d ", array[i]);
    }
    printf("\n");
}

void time_it(SortMethod sort, char *type, int *array, int *sorted, int n, int verbose)
{
    struct timeval start;
    struct timeval stop;
    double elapsed = 0;
    if (verbose == 2) print_array(array, n);
    gettimeofday(&start, NULL);
    (*sort.fptr)(array, n);
    gettimeofday(&stop, NULL);
    elapsed = (double) (stop.tv_sec - start.tv_sec) * 1000.0f + (stop.tv_usec - start.tv_usec) / 1000.0f;;
    assert(arrays_equal(sorted, array, n));
    if (verbose != 0) printf("%d %s elements: %.3f ms\n",n, type, elapsed);
}

void benchmark(SortMethod s, int verbose)
{
    int *arr_test_100 = fill_array_ordered(100);
    int *arr_test_1000 = fill_array_ordered(1000);
    int *arr_test_10000 = fill_array_ordered(10000);

    int *arr_100_rand  = fill_array(100);
    int *arr_1000_rand  = fill_array(1000);
    int *arr_10000_rand = fill_array(10000);

    int *arr_100_reversed  = fill_array_reversed(100);
    int *arr_1000_reversed  = fill_array_reversed(1000);
    int *arr_10000_reversed = fill_array_reversed(10000);

    int *arr_100_ordered  = fill_array_ordered(100);
    int *arr_1000_ordered  = fill_array_ordered(1000);
    int *arr_10000_ordered = fill_array_ordered(10000);

    printf("\nBenchmarking %s:\n\n", s.name);

    /* Random Array */
    time_it(s, "random", arr_100_rand, arr_test_100, 100, verbose);
    time_it(s, "random", arr_1000_rand, arr_test_1000, 1000, verbose);
    time_it(s, "random", arr_10000_rand, arr_test_10000, 10000, verbose);
    printf("\n");

    /* Inverted Order Array */
    time_it(s, "inverted", arr_100_reversed, arr_test_100, 100, verbose);
    time_it(s, "inverted", arr_1000_reversed, arr_test_1000, 1000, verbose);
    time_it(s, "inverted", arr_10000_rand, arr_test_10000, 10000, verbose);
    printf("\n");

    /* Ordered Array */
    time_it(s, "ordered", arr_100_rand, arr_test_100, 100, verbose);
    time_it(s, "ordered", arr_1000_rand, arr_test_1000, 1000, verbose);
    time_it(s, "ordered", arr_10000_rand, arr_test_10000, 10000, verbose);
    printf("\n");

    /* Free arrays */
    free(arr_test_100);
    free(arr_test_1000);
    free(arr_test_10000);
    free(arr_100_rand);
    free(arr_1000_rand) ;
    free(arr_10000_rand);
    free(arr_100_reversed) ;
    free(arr_1000_reversed) ;
    free(arr_10000_reversed);
    free(arr_100_ordered);
    free(arr_1000_ordered);
    free(arr_10000_ordered);
}