#ifndef SORTING_H
#define SORTING_H

// INSERTION SORT
template <typename T, typename Compare>
void insertionSort(T arr[], int n, Compare comp)
{

    for (int i = 1; i < n; i++)
    {

        T key = arr[i];
        int j = i - 1;

        while (j >= 0 && comp(key, arr[j]))
        {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

// MERGE FUNCTION
template <typename T, typename Compare>
void merge(T arr[], T temp[],
           int left, int middle, int right,
           Compare comp)
{

    int i = left;
    int j = middle + 1;
    int k = left;

    while (i <= middle && j <= right)
    {

        if (comp(arr[j], arr[i]))
        {
            temp[k++] = arr[j++];
        }
        else
        {
            temp[k++] = arr[i++];
        }
    }

    while (i <= middle)
    {
        temp[k++] = arr[i++];
    }

    while (j <= right)
    {
        temp[k++] = arr[j++];
    }

    for (int x = left; x <= right; x++)
    {
        arr[x] = temp[x];
    }
}

// RECURSIVE MERGE SORT
template <typename T, typename Compare>
void mergeSortHelper(T arr[], T temp[],
                     int left, int right,
                     Compare comp)
{

    if (left >= right)
    {
        return;
    }

    int middle = left + (right - left) / 2;

    mergeSortHelper(arr, temp, left, middle, comp);
    mergeSortHelper(arr, temp, middle + 1, right, comp);

    merge(arr, temp, left, middle, right, comp);
}

// MAIN MERGE SORT FUNCTION
template <typename T, typename Compare>
void mergeSort(T arr[], int n, Compare comp)
{

    if (n <= 1)
    {
        return;
    }

    T *temp = new T[n];

    mergeSortHelper(arr, temp, 0, n - 1, comp);

    delete[] temp;
}

#endif