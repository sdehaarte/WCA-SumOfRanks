#include "sum_of_ranks.h"
#include <string>
#include <iostream>

int main(int argc, char* argv[]) {
    // Mode either sort or compare (default is sort)
    std::string mode = "sort";
    // Sort either merge or quick
    std::string sortAlgorithm = "merge";

    for (int i=1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--mode" && i + 1 < argc) {
            i += 1;
            mode = argv[i];
        } 
        else if (arg == "--sort" && i + 1 < argc) {
            i += 1;
            sortAlgorithm = argv[i];
        }
    }

    std::cout << "test";
    std::vector<Cuber> cubers = SorTools::loadAndCalculateSumOfRanks();
    std::cout << "test";

    if (mode == "sort") {
        if (sortAlgorithm == "merge") {
            SorTools::mergeSort(cubers, 0, cubers.size() - 1);
            SorTools::outputJson(cubers, "../output/result.json");
        }
        else if (sortAlgorithm == "quick") {
            SorTools::quickSort(cubers, 0, cubers.size() - 1);
            SorTools::outputJson(cubers, "../output/result.json");

        }
    } 
    else if (mode == "compare") {
        // SorTools::compareAlgorithms(cubers, )
    }
    else {
        std::cerr << "Invalid arguments";
    }
    return 0;
}