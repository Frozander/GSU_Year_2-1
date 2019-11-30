#include "sorting.h"

void swap(int *x, int *y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

int *fill_array(int n)
{
    int i, j;
    int tmp;
    int *array = malloc(sizeof(int) * n);
    for (i = 0; i < n; ++i)
        array[i] = i;

    // Shuffle
    for (i = n - 1; i > 1; --i)
    {
        j = rand() % (i + 1);
        swap(&array[i], &array[j]);
    }

    return array;
}

int *fill_array_reversed(int n)
{
    int i, j;
    int *array = malloc(sizeof(int) * n);
    for (i = 0; i < n; ++i)
        array[i] = n - i - 1;
    return array;
}

int *fill_array_ordered(int n)
{
    int i, j;
    int *array = malloc(sizeof(int) * n);
    for (i = 0; i < n; ++i)
        array[i] = i;
    return array;
}

void bubble_sort(int *array, int n)
{
    int i, j;
    int swapped;
    for (i = 0; i < n - 1; ++i)
    {
        swapped = 0;
        for (j = 0; j < n - i - 1; ++j)
            if (array[j] > array[j + 1])
            {
                swap(&array[j], &array[j + 1]);
                swapped = 1;
            }
        if (!swapped)
            break;
    }
}

void selection_sort(int *array, int n)
{
    int min, j, k;

    for (j = 0; j < n; ++j)
    {
        min = j;

        for (k = j; k < n; ++k)
        {
            if (array[k] < array[min])
                min = k;
        }

        swap(&array[min], &array[j]);
    }
}

void insertion_sort(int *array, int n)
{
    int i, j;
    int pivot;
    for (i = 0; i < n; ++i)
    {
        pivot = array[i];
        j = i - 1;

        while (j >= 0 &&  array[j] > pivot)
        {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = pivot;
    }
}


int hoare_partition(int *array, int low, int high)
{
    int pivot = array[low];
    int l = low - 1;
    int r = high + 1;
    while (1)
    {
        do
        {
            ++l;
        } while (array[l] < pivot);
        do
        {
            --r;
        } while (array[r] > pivot);
        if (l >= r)
            return r;
        swap(&array[l], &array[r]);
    }
}

void quick_sort(int *array, int low, int high)
{
    if (low < high)
    {
        int partition_index = hoare_partition(array, low, high);

        quick_sort(array, low, partition_index);
        quick_sort(array, partition_index + 1, high);
    }
}

void qsort_wrapper(int *array, int n)
{
    quick_sort(array, 0, n - 1);
}

void merge(int *array, int low, int middle, int high) {

    int i, counter_left, counter_right, k;
    int left_size = middle - low + 1;
    int right_size = high - middle;

    int* tempArrLeft = malloc(sizeof(int) * left_size);
    int* tempArrRight = malloc(sizeof(int) * right_size);

    for(i = 0; i < left_size; ++i)
        tempArrLeft[i] = array[low + i];

    for(i = 0; i < right_size; ++i)
        tempArrRight[i] = array[middle + 1 + i];

    counter_left = 0;
    counter_right = 0;
    k = low;

    while((counter_left < left_size) && (counter_right < right_size)){

    if (tempArrLeft[counter_left] < tempArrRight[counter_right]) {
        array[k] = tempArrLeft[counter_left];
        ++counter_left;
    } else
    {
        array[k] = tempArrRight[counter_right];
        ++counter_right;
    }

    ++k;
    }
    while(counter_left < left_size){
        array[k] = tempArrLeft[counter_left];
        ++counter_left;
        ++k;
    }
    while(counter_right < right_size){
        array[k] = tempArrRight[counter_right];
        ++counter_right;
        ++k;
    }
}

void merge_sort(int *array, int low, int high) {
    if (low < high) {
        int middle = low + (high - low)/2;
        merge_sort(array, low, middle);
        merge_sort(array, middle + 1, high);
        merge(array, low, middle, high);
    }
}

void mergesort_wrapper(int *array, int n)
{
    merge_sort(array, 0, n - 1);
}

void shell_sort(int *array, int n) {
    int gaps[] = {701, 301, 132, 57, 23, 10, 4, 1};
    int i, j, k, gapsize, temp;

    for(i = 0; i < 8; ++i)
    {
    gapsize = gaps[i];

    for(j = gapsize; j < n; ++j)
    {
        temp = array[j];
        k = j;
        while(k >= gapsize && array[k - gapsize] > temp){
            array[k] = array[k -gapsize];
            k -= gapsize;
        }
        array[k] = temp;
    }

    }
}

int find_max(int *array, int n)
{
    int max = array[0];
    for (int i = 1; i < n; ++i)
    if (array[i] > max)
        max = array[i];
    return max;
}

void bucket_sort(int *array, int n)
{
    int bucket[n];
    const int max = find_max(array, n);
    for (int i = 0; i <= max; ++i)
    {
        bucket[i] = 0;
    }
    for (int i = 0; i < n; ++i)
    {
        bucket[array[i]]++;
    }
    for (int i = 0, j = 0; i <= max; ++i)
    {
        while (bucket[i] > 0)
        {
            array[j++] = i;
            bucket[i]--;
        }
    }
}
