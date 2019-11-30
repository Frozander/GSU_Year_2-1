#ifndef __USR_SORT_H_
#define __USR_SORT_H_

#include <stdlib.h>

void swap(int *x, int *y);
int *fill_array(int n);
int *fill_array_reversed(int n);
int *fill_array_ordered(int n);
void bubble_sort(int *array, int n);
void insertion_sort(int *array, int n);
void selection_sort(int *array, int n);
int hoare_partition(int *array, int low, int high);
void quick_sort(int *array, int low, int high);
void qsort_wrapper(int *array, int n);
void merge(int *array, int low, int middle, int high);
void merge_sort(int *array, int low, int high);
void mergesort_wrapper(int *array, int n);
void shell_sort(int *array, int n);
int find_max(int *array, int n);
void bucket_sort(int *array, int n);

#endif
