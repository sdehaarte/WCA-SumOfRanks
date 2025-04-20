#include "sum_of_ranks.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <chrono>

void SorTools::parseTSVFile(const std::string& filename,
    std::vector<Cuber>& cubers,
    std::unordered_map<std::string, size_t>& idToIndex,
    std::unordered_map<std::string, std::string>& cuberName,
    std::unordered_map<std::string, std::unordered_map<std::string, size_t>>& eventRank,
    std::unordered_map<std::string, std::unordered_set<std::string>>& eventCubers,
    std::unordered_map<std::string, size_t>& eventLastRank) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open " << filename << std::endl;
        return;
    }
    std::string line;
    std::getline(file, line);
    size_t lineNum = 1;
    while (std::getline(file, line)) {
        std::stringstream ss(line);

        size_t best, worldRank, continentRank, countryRank;
        std::string cuberId, eventId;
        ss >> best >> cuberId >> eventId >> worldRank >> continentRank >> countryRank;

        if (idToIndex.find(cuberId) == idToIndex.end()) {
            auto it = cuberName.find(cuberId);
            std::string name = (it != cuberName.end()) ? it->second : "Unknown";
            cubers.emplace_back(cuberId, name, 0);
            idToIndex[cuberId] = cubers.size() - 1;
        }

        // Store rank data
        size_t cuberIndex = idToIndex[cuberId];
        eventRank[eventId][cuberId] = worldRank;
        eventCubers[eventId].insert(cuberId);
        eventLastRank[eventId] = std::max(eventLastRank[eventId], worldRank);
    }
    file.close();
}

std::vector<Cuber> SorTools::loadAndCalculateSumOfRanks() {
    const std::string& averageFilePath = "../data/Preprocessed_RanksAverage.tsv";
    const std::string& singleFilePath = "../data/Preprocessed_RanksSingle.tsv";
    const std::string& personsFilePath = "../data/WCA_export_Persons.tsv";
    const std::vector<std::string> eventIds = { "222", "333", "444", "555", "666", "777", "333oh", "333bf", "333fm", "333mbf", "minx", "pyram", "skewb", "sq1", "clock", "444bf", "555bf" };

    // Vector with all Cubers
    std::vector<Cuber> cubers;
    std::unordered_map<std::string, size_t> idToIndex;
    std::unordered_map<std::string, std::string> cuberName;
    
    // Parse Persons TSV
    std::ifstream file(personsFilePath);
    if (!file) {
        std::cerr << "Couldn't open " << personsFilePath << "\n";
        return cubers;
    }
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name, gender, wcaId, countryId;
        size_t subid;
        std::getline(ss, name, '\t');
        std::getline(ss, gender, '\t');
        std::getline(ss, wcaId, '\t');
        ss >> subid;
        std::getline(ss, countryId, '\t');
        // Use first occurence of wcaId (ignore subid)
        if (cuberName.find(wcaId) == cuberName.end()) {
            cuberName[wcaId] = name;
        }
    }
    file.close();

    std::unordered_map<std::string, std::unordered_map<std::string, size_t>> eventRank;
    // Last rank of each event {EventId, Last Rank}
    std::unordered_map<std::string, size_t> eventLastRank;
    // Cubers participating in each event {EventId, CuberIds}
    std::unordered_map<std::string, std::unordered_set<std::string>> eventCubers;

    parseTSVFile(singleFilePath, cubers, idToIndex, cuberName, eventRank, eventCubers, eventLastRank);
    parseTSVFile(averageFilePath, cubers, idToIndex, cuberName, eventRank, eventCubers, eventLastRank);

    for (const auto& eventId : eventIds) {
        for (Cuber& cuber : cubers) {
            if (eventCubers[eventId].count(cuber.wcaId)) {
                cuber.sumOfRanks += eventRank[eventId][cuber.wcaId];
            } else {
                cuber.sumOfRanks += eventLastRank[eventId] + 1;
            }
        }
    }
    return cubers;
}

// MergeSort implementation (ascending order by sumOfRanks)
void SorTools::mergeSort(std::vector<Cuber>& cubers, int low, int high) {
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

// Generates ranks to output path
void SorTools::outputJson(const std::vector<Cuber>& cubers, const std::string& outputPath) {
    std::ofstream file(outputPath);
    if (!file) {
        std::cerr << "Couldn't open " << outputPath << "\n";
        return;
    }
    file << "{\"ranks\":[";
    for (size_t i = 0; i < cubers.size(); ++i) {
        const auto& cuber = cubers[i];
        if (i > 0) file << ", ";
        file << "{\"wcaId\": \"" << cuber.wcaId
             << "\", \"name\": \"" << cuber.name
             << "\", \"rank\": " << (i + 1)
             << ", \"sumOfRanks\": " << cuber.sumOfRanks
             << "}";
    }
    file << "]}";
    file.close();
}


void SorTools::outputComparison(const std::vector<Cuber>& competitors) {

}