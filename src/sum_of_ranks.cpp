#include "sum_of_ranks.h"


// MergeSort implementation (ascending order by sumOfRanks)
void SumOfRanks::mergeSort(std::vector<Cuber>& cubers, int low, int high) {
    if (low < high) {
        // Middle index to halve arrays
        int mid = low + (high - low) / 2;
        // Sort elements before middle and after middle
        mergeSort(cubers, low, mid);
        mergeSort(cubers, mid + 1, high);
        // Merge sorted both halves
        SumOfRanks::merge(cubers, low, mid, high);
    }
}


// MergeSort merge helper
void SumOfRanks::merge(std::vector<Cuber>& cubers, int low, int mid, int high) {
    // Calculate sizes of left and right subarrays
    int x = mid - low + 1;
    int y = high - mid;
    // Create left and right subarrays
    std::vector<Cuber> X(x), Y(y);
    // Add data to left and right subarrays
    for (int i=0; i < x; i++)
        X[i] = cubers[low + i];
    for (int j=0; j < y; j++)
        Y[j] = cubers[mid + 1 + j];
    
    // Initializes index for left subarray, right subarray, merged array, respectively
    int i = 0, j = 0, k = low;

    // Merge left and right subarrays back into cubers
    while (i < x && j < y) {
        // Compares sumOfRanks, with smaller sumOfRanks coming first
        if (X[i].sumOfRanks <= Y[j].sumOfRanks) {
            cubers[k] = X[i];
            i++;
        }
        else {
            cubers[k] = Y[j];
            j++;
        }
        k++;
    }
    // Add remaining elements from left subarray then right subarray
    while (i < x) {
        cubers[k] = X[i];
        i++;
        k++;
    }
    while (j < y) {
        cubers[k] = Y[j];
        j++;
        k++;
    }
}


// QuickSort function implementation (ascneding order by sumOfRanks)
void SumOfRanks::quickSort(std::vector<Cuber>& cubers, int low, int high) {
    if (low < high) {
        // Pivot based 
        int pivot = partition(cubers, low, high);
        // Sort elements before pivot and after pivot
        quickSort(cubers, low, pivot - 1);
        quickSort(cubers, pivot + 1, high);
    }
}

// QuickSort partition helper
int SumOfRanks::partition(std::vector<Cuber>& cubers, int low, int high) {
    // Choose the first cuber's sumOfRanks as pivot
    int pivot = cubers[low].sumOfRanks;
    // Initalize up (finds larger elements) and down (finds smaller elements) index
    int up = low, down = high;

    // Iterate up and down until they meet
    while (up < down) {
        // Increase up until cuber's sumOfRanks greater than pivot
        for (int j=up; j < high; j++) {
            if (cubers[up].sumOfRanks > pivot)
                break;
            up ++;
        }
        // Decrease down util cubers' sumOfRanks less than pivot
        for (int j=down; j> low; j--) {
            if (cubers[down].sumOfRanks < pivot)
                break;
            down --;
        }
        // If pointers haven't crossed, swap elements to place them on correct sides
        if (up < down)
            std::swap(cubers[up], cubers[down]);
    }
    // Swap pivot with down to correct positions
    std::swap(cubers[low], cubers[down]);
    return down;
}