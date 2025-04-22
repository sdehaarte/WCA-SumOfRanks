#include "sum_of_ranks.h"
#include <iostream>
#include <string>
#include <vector>
#include <chrono>

using namespace SumOfRanks;

void displayTopN(const std::vector<Cuber>& cuber, int n) {
    for (int i = 0; i < std::min(n, (int)cuber.size()); ++i) {
        std::cout << i + 1 << ". " << cuber[i].wcaId
                  << " - Total Rank: " << cuber[i].sumOfRanks << "\n";
    }
}

void compareSortAlgorithms(std::vector<Cuber>& cubers) {
    std::vector<Cuber> ms_copy = cubers;
    std::vector<Cuber> qs_copy = cubers;

    auto startM = std::chrono::high_resolution_clock::now();
    mergeSort(ms_copy, 0, ms_copy.size() - 1);
    auto endM = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationM = endM - startM;

    auto startQ = std::chrono::high_resolution_clock::now();
    quickSort(qs_copy, 0, qs_copy.size() - 1);
    auto endQ = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationQ = endQ - startQ;

    std::cout << "MergeSort took: " << durationM.count() << " seconds\n";
    std::cout << "QuickSort took: " << durationQ.count() << " seconds\n";
}

int main() {
    std::vector<Cuber> cubers = loadAndCalculateSumOfRanks();
    // implenment loading the files and oadAndCalculateSumOfRanks
    if (cubers.empty()) {
        std::cout << "Files not loaded";
        return 1;
    }

    while (true) {
        std::cout << "\nMenu:\n";
        std::cout << "1. Sort using Merge Sort\n";
        std::cout << "2. Sort using Quick Sort\n";
        std::cout << "3. Compare Merge Sort vs Quick Sort\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            mergeSort(cubers, 0, cubers.size() - 1);
            int n;
            std::cout << "Enter number of cubers to display: ";
            std::cin >> n;
            displayTopN(cubers, n);
        } else if (choice == 2) {
            quickSort(cubers, 0, cubers.size() - 1);
            int n;
            std::cout << "Enter number of cubers to display: ";
            std::cin >> n;
            displayTopN(cubers, n);
        } else if (choice == 3) {
            compareSortAlgorithms(cubers);
        } else if (choice == 4) {
            std::cout << "Ending Program...\n";
            break;
        } else {
            std::cout << "Invalid Choice!\n";
        }
    }
    return 0;
}