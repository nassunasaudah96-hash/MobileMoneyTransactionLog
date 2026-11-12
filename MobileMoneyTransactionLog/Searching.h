#ifndef SEARCHING_H
#define SEARCHING_H

template <typename T, typename Key, typename Compare>
int binarySearch(const T arr[], int n,
                 const Key &key, Compare comp)
{

    int low = 0;
    int high = n - 1;

    while (low <= high)
    {

        int middle = low + (high - low) / 2;

        int result = comp(arr[middle], key);

        if (result == 0)
        {
            return middle;
        }

        if (result < 0)
        {
            low = middle + 1;
        }
        else
        {
            high = middle - 1;
        }
    }

    return -1;
}

#endif