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

double time_it(SortMethod sort, char *type, int *array, int *sorted, int n, int verbose)
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
    if (verbose != 0) printf("%d %s elements: %.3lf ms\n",n, type, elapsed);
    return elapsed;
}

void benchmark(SortMethod *s, int verbose)
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

    printf("\nBenchmarking %s:\n\n", s->name);

    /* Random Array */
    s->perf[0] = time_it(*s, "random", arr_100_rand, arr_test_100, 100, verbose);
    s->perf[1] =time_it(*s, "random", arr_1000_rand, arr_test_1000, 1000, verbose);
    s->perf[2] =time_it(*s, "random", arr_10000_rand, arr_test_10000, 10000, verbose);
    printf("\n");

    /* Inverted Order Array */
    s->perf[3] = time_it(*s, "inverted", arr_100_reversed, arr_test_100, 100, verbose);
    s->perf[4] = time_it(*s, "inverted", arr_1000_reversed, arr_test_1000, 1000, verbose);
    s->perf[5] = time_it(*s, "inverted", arr_10000_rand, arr_test_10000, 10000, verbose);
    printf("\n");

    /* Ordered Array */
    s->perf[6] = time_it(*s, "ordered", arr_100_rand, arr_test_100, 100, verbose);
    s->perf[7] = time_it(*s, "ordered", arr_1000_rand, arr_test_1000, 1000, verbose);
    s->perf[8] = time_it(*s, "ordered", arr_10000_rand, arr_test_10000, 10000, verbose);
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

SortMethod *compare_times(SortMethod *methodlist, int method_count, int test_num)
{
    SortMethod *min = methodlist;
    SortMethod *temp;
    for (int i = 0; i < method_count; ++i)
    {
        temp = (methodlist + i);
        if (temp->perf[test_num] < min->perf[test_num])
            min = temp;
    }
    return min;
}

void find_best_performance(SortMethod *methodlist, int test_count, int method_count)
{
    SortMethod *bests[9];
    for (int i = 0; i < test_count; ++i)
    {
        bests[i] = compare_times(methodlist, method_count, i);
    }

    printf("Fastest for 100 randomised: %s\n", bests[0]->name);
    printf("Fastest for 1000 randomised: %s\n", bests[1]->name);
    printf("Fastest for 10000 randomised: %s\n", bests[2]->name);
    printf("\n");
    printf("Fastest for 100 reversed: %s\n", bests[3]->name);
    printf("Fastest for 1000 reversed: %s\n", bests[4]->name);
    printf("Fastest for 10000 reversed: %s\n", bests[5]->name);
    printf("\n");
    printf("Fastest for 100 ordered: %s\n", bests[6]->name);
    printf("Fastest for 1000 ordered: %s\n", bests[7]->name);
    printf("Fastest for 10000 ordered: %s\n", bests[8]->name);
}
