#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <string>

struct Cuber {
    std::string wcaId;
    std::string name;
    int sumOfRanks;
    Cuber() : sumOfRanks(0) {}
    Cuber(const std::string& wcaId, const std::string& name, size_t sumOfRanks) : wcaId(wcaId), name(name), sumOfRanks(sumOfRanks) {}
};

namespace SumOfRanks {

    void parseTSVFile(const std::string& filename,
        std::vector<Cuber>& cubers,
        std::unordered_map<std::string, size_t>& idToIndex,
        std::unordered_map<std::string, std::string>& cuberName,
        std::unordered_map<std::string, std::unordered_map<std::string, size_t>>& eventRank,
        std::unordered_map<std::string, std::unordered_set<std::string>>& eventCubers,
        std::unordered_map<std::string, size_t>& eventLastRank);
    std::vector<Cuber> loadAndCalculateSumOfRanks();

    // MergeSort implementation (ascending order by sumOfRanks)
    void mergeSort(std::vector<Cuber>& cubers, int low, int high) {
        if (low < high) {
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
    void merge(std::vector<Cuber>& cubers, int low, int mid, int high) {
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
    void quickSort(std::vector<Cuber>& cubers, int low, int high) {
        if (low < high) {
            // Pivot based 
            int pivot = partition(cubers, low, high);

            // Sort elements before pivot and after pivot
            quickSort(cubers, low, pivot - 1);
            quickSort(cubers, pivot + 1, high);
        }
    }

    // QuickSort partition helper
    int partition(std::vector<Cuber>& cubers, int low, int high) {
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

    
    void outputJson(const std::vector<Cuber>& cubers, const std::string& outputPath);
    void outputComparison(const std::vector<Cuber>& competitors);
}

const std::vector<std::string> allEvents = {
    "222_avg", "333_avg", "333fm_avg", "333oh_avg","444_avg",
    "555_avg", "666_avg","777_avg", "clock_avg", "minx_avg",
    "pyram_avg", "skewb_avg","sq1_avg",

    "333bf_single", "333_mbf_single", "444bf_single","555bf_single",
};

void parseTSVFile(const std::string& filename, std::unordered_map<std::string, Cuber>& players, int& maxRank, const std::string& suffix) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file " << filename << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);

    while (getline(file, line)) {
        std::istringstream ss(line);
        int best, worldRank, continentRank, countryRank;
        std::string personId, eventId;
        ss >> best >> personId >> eventId >> worldRank >> continentRank >> countryRank;

        std::string eventKey = eventId + suffix;

        if (players.find(personId) == players.end()) {
            players[personId] = Player{personId};
        }

        players[personId].eventRanks[eventKey] = worldRank;

        if (worldRank > maxRank) {
            maxRank = worldRank;
        }
    }
}

// Combine avg and single players, and calculate total rank

// Implement Merge Sort Algorithm

// Implement Quick Sort Algorithm

// run both and compare Algorithm

// Implement performance

void displayTopN(const std::vector<Cuber>& cubers, int n) {
    for (int i = 0; i < std::min(n, (int)cubers.size()); ++i) {
        std::cout << i + 1 << ". " << cubers[i].wcaId
                  << " - Total Rank: " << cubers[i].sumOfRanks << "\n";
    }
}