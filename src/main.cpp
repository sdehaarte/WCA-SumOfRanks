#include "sum_of_ranks.h"
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <limits>

using namespace SumOfRanks;

void displayTopN(const std::vector<Cuber>& cuber, int n) {
    for (int i = 0; i < std::min(n, (int)cuber.size()); ++i) {
        std::cout << i + 1 << ". " << cuber[i].wcaId
                  << " - Total Rank: " << cuber[i].sumOfRanks << "\n";
    }
}

void compareSortAlgorithms(std::vector<Cuber>& cubers, int n) {
    std::vector<Cuber> ms_copy = cubers;
    std::vector<Cuber> qs_copy = cubers;

    std::cout << "Starting MergeSort...\n";
    auto startM = std::chrono::high_resolution_clock::now();
    mergeSort(ms_copy, 0, ms_copy.size() - 1);
    auto endM = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationM = endM - startM;
    std::cout << "MergeSort done, \n";

    std::cout << "Write MergeSort results to merge_sorted.json...\n";
    outputJson(ms_copy, "merge_sorted.json", n);

    std::cout << "Starting QuickSort...\n";
    auto startQ = std::chrono::high_resolution_clock::now();
    quickSort(qs_copy, 0, qs_copy.size() - 1);
    auto endQ = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationQ = endQ - startQ;
    std::cout << "QuickSort done.\n";

    std::cout << "Write QuickSort results to quick_sorted.json...\n";
    outputJson(qs_copy, "quick_sorted.json", n);

    std::cout << "MergeSort took: " << durationM.count() << " seconds\n";
    std::cout << "QuickSort took: " << durationQ.count() << " seconds\n";
}

int main(int argc, char* argv[]) {
    // defaulting to merge (because it actually works right now unlike quick...)
    std::string mode = "";
    std::string sort_type = "merge";
    int n = 100;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--mode" && i + 1 < argc) {
            mode = argv[++i];
        } else if (arg == "--sort" && i + 1 < argc) {
            sort_type = argv[++i];
        } else if (arg == "--n" && i + 1 < argc) {
            n = std::stoi(argv[++i]);
        }
    }

    if (mode.empty()) {
        std::cout << "Usage:\n"
                  << "  ./sor --mode sort [--sort quick|merge] [--n N]\n"
                  << "  ./sor --mode compare\n";
        return 1;
    }

    std::vector<Cuber> cubers = loadAndCalculateSumOfRanks();
    if (cubers.empty()) {
        std::cout << "Files not loaded\n";
        return 1;
    }

    // revisit the hardcoding? idk
    if (mode == "sort") {
        if (sort_type == "quick") {
            quickSort(cubers, 0, cubers.size() - 1);
            std::string outputFilename = "../output/ranks.json";
            outputJson(cubers, outputFilename, n);
        } 
        else {
            mergeSort(cubers, 0, cubers.size() - 1);
            std::string outputFilename = "../output/ranks.json";
            outputJson(cubers, outputFilename, n);
        }
        // displayTopN(cubers, n);
    } 
    else if (mode == "compare") {
    //    compareSortAlgorithms(cubers, n);
        outputComparison(cubers, "../output/compare.json");
    } 
    else {
        std::cout << "Invalid mode.\n";
        return 1;
    }

    return 0;
}