//
// Created by Sensi on 4/17/25.
//

#include "sum_of_ranks.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <map>

std::vector<Cuber> SorTools::loadData(const std::string& tsvFilePath) {
}

void SorTools::calculateSumOfRanks(std::vector<Cuber>& cubers) {
    // 
    std::map<std::string, std::vector<std::pair<std::string, double>>> eventResults;

    for (auto& [event, results] : eventResults) {
        auto compareResult = [](const auto&a, const auto& b) { return a.second < b.second; };
        std::sort(results.begin(), results.end(), compareResult);
        for (int i = 0; i<results.size(); ++i) {
            for (Cuber& cuber : cubers) {
                if (cuber.wcaId == results[i].first) {
                    cuber.sumOfRanks += static_cast<int>(i+1);
                    break;
                }
            }
        }
    }
}

// QuickSort function implementation (ascneding order by sumOfRanks)
void SorTools::quickSort(std::vector<Cuber>& cubers, int low, int high) {
    if (low < high) {
        // Pivot based 
        int pivot = partition(cubers, low, high);

        // Sort elements before pivot and after pivot
        quickSort(cubers, low, pivot - 1);
        quickSort(cubers, pivot + 1, high);
    }
}

// QuickSort partition helper
int SorTools::partition(std::vector<Cuber>& cubers, int low, int high) {
    // Choose the first cuber's sumOfRanks as pivot
    int pivot = cubers[low].sumOfRanks;
    // Initalize up (finds larger elements) and down (finds smaller elements) index
    int up = low, down = high;

    // Iterate up and down until they meet
    while (up < down)
    {
        // Increase up until cuber's sumOfRanks greater than pivot
        for (int j=up; j < high; j++)
        {
            if (cubers[up].sumOfRanks > pivot)
                break;
            up ++;
        }
        // Decrease down util cubers' sumOfRanks less than pivot
        for (int j=down; j> low; j--)
        {
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

// MergeSort implementation (ascending order by sumOfRanks)
void SorTools::mergeSort(std::vector<Cuber>& cubers, int low, int high) {
    if (low < high)
    {
        // Middle index to halve arrays
        int mid = low + (high - low) / 2;

        // Sort elements before middle and after middle
        mergeSort(cubers, low, mid);
        mergeSort(cubers, mid + 1, high);

        // Merge sorted both halves
        merge(cubers, low, mid, high);
    }
}

// MergeSort merge helper
void SorTools::merge(std::vector<Cuber>& cubers, int low, int mid, int high) {
    // Calculate sizes of left and right subarrays
    int x = mid - low + 1;
    int y = high - mid;

    // Create left and right subarrays
    std::vector<Cuber> X(x), Y(y);

    // Add data to left and right subarrays
    for (int i=0; i < x; i++)
        X[i] = cubers[low + i];
    for (int j=0; j < y; j++)
        Y[j] = cubers[mid + low + j];
    
    // Initializes index for left subarray, right subarray, merged array, respectively
    int i = 0, j = 0, k = low;

    // Merge left and right subarrays back into cubers
    while (i < x && j < y)
    {
        // Compares sumOfRanks, with smaller sumOfRanks coming first
        if (X[i].sumOfRanks <= Y[j].sumOfRanks)
        {
            cubers[k] = X[i];
            i++;
        }
        else
        {
            cubers[k] = Y[j];
            j++;
        }
        k++;
    }

    // Add all remaining elements from left subarray
    while (i < x)
    {
        cubers[k] = X[i];
        i++;
        k++;
    }
    // Add all remaining elements from right subarray
    while (j < y)
    {
        cubers[k] = Y[j];
        j++;
        k++;
    }
}

void SorTools::outputJson(std::vector<Cuber>& cubers, const std::string& filename){ 

}
void SorTools::outputComparison(std::vector<Cuber>& competitors){

}