#ifndef __USR_BENCHMARK_H_
#define __USR_BENCHMARK_H_

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define T_CONST 1000.0 / CLOCKS_PER_SEC

typedef struct {
  /* Algoritmanin adi, ornek: "Insertion Sort" */
  char *name;
  /* Algoritmanin siralama hizi (max 16) */
  double perf[9];
  /* Algoritmayi gercekleyen fonksiyonu gosterecek pointer */
  void (*fptr) (int *, int);
  /* Performansi olculsun mu? */
} SortMethod;

extern int *fill_array(int);
extern int *fill_array_reversed(int);
extern int *fill_array_ordered(int);

extern void qsort_wrapper(int *, int);
extern void mergesort_wrapper(int *, int);
extern void bucket_sort(int *, int);
extern void shell_sort(int *, int);
extern void bubble_sort(int *, int);
extern void insertion_sort(int *, int);

int arrays_equal(int *sorted, int *answer, int size);
void print_array(int *array, int size);
void benchmark(SortMethod *s, int verbose);
SortMethod *compare_times(SortMethod *methodlist, int method_count, int test_num);
void find_best_performance(SortMethod *methodlist, int test_count, int method_count);

#endif
