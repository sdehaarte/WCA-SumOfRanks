#include "sum_of_ranks.h"

namespace SumOfRanks {

    void parseTSVFile(
        const std::string& filename,
        std::vector<Cuber> & cubers,
        std::unordered_map<std::string, size_t>& idToIndex,
        const std::unordered_map<std::string, std::string>& cuberName,
        std::unordered_map<std::string, std::unordered_map<std::string, size_t> >& eventRank,
        std::unordered_map<std::string, std::unordered_set<std::string> >& eventCubers,
        std::unordered_map<std::string, size_t>& eventLastRank)
    {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        std::string line;
        std::getline(file, line);

        while (std::getline(file, line)) {
            std::istringstream ss (line);

            size_t best, worldRank, continentRank, countryRank;
            std::string cuberId, eventId;

            ss >> best >> cuberId >> eventId >> worldRank >> continentRank >> countryRank;

            if (idToIndex.find(cuberId) == idToIndex.end()) {
                std::string name;
                std::unordered_map<std::string, std::string>::const_iterator it = cuberName.find(cuberId);
                if (it != cuberName.end()) {
                    name = it->second;
                } else {
                    name = "Unknown";
                }
                idToIndex[cuberId] = cubers.size();
                cubers.push_back(Cuber(cuberId, name, 0));
            }

            size_t idx = idToIndex[cuberId];
            eventRank[eventId][cuberId] = worldRank;
            eventCubers[eventId].insert(cuberId);
            eventLastRank[eventId] = std:: max(eventLastRank[eventId], worldRank);
        }
    }

    void loadCuberInfo(
        const std::string& filename,
        std::unordered_map<std::string, std::string>& cuberName)
    {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Error opening file: " << filename << '\n';
            return;
        }

        std::string line;
        std::getline(file, line);

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string name, gender, id, subid, country;

            std::getline(ss, name, '\t');
            std::getline(ss, gender, '\t');
            std::getline(ss, id, '\t');
            std::getline(ss, subid, '\t');
            std::getline(ss, country, '\t');

            if(cuberName.find(id) == cuberName.end()) {
                cuberName[id] = name;
            }
        }
    }
    
    // Loads persons tsv, preprocessed tsv, and calculates sum of ranks
    std::vector<Cuber> loadAndCalculateSumOfRanks() {
        const std::vector<std::string> eventIds = { "222", "333", "444", "555", "666", "777", "333oh", "333bf", "333fm", "333mbf", "minx", "pyram", "skewb", "sq1", "clock", "444bf", "555bf" };
        std::vector<Cuber> cubers;
        std::unordered_map<std::string, size_t> idToIndex;
        std::unordered_map<std::string, std::string> cuberName;
        std::unordered_map<std::string, std::unordered_map<std::string, size_t> > eventRank;
        std::unordered_map<std::string, std::unordered_set<std::string> > eventCubers;
        std::unordered_map<std::string, size_t> eventLastRank;

        loadCuberInfo("../data/WCA_export_Persons.tsv", cuberName);
        parseTSVFile("../data/Preprocessed_RanksSingle.tsv", cubers, idToIndex, cuberName, eventRank, eventCubers, eventLastRank);
        parseTSVFile("../data/Preprocessed_RanksAverage.tsv", cubers, idToIndex, cuberName, eventRank, eventCubers, eventLastRank);

        // Calculates Sum of Ranks
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
            } else {
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

    // Generates ranks in json format to an output path
    void outputJson(const std::vector<Cuber>& cubers, const std::string& outputPath, size_t N) {
        std::ofstream file(outputPath);
        if (!file) {
            std::cerr << "Couldn't open " << outputPath << "\n";
            return;
        }
        // Prints the first N or size of cubers (whichever is smaller)
        file << "{\"ranks\":[";
        for (size_t i = 0; i < std::min(N, cubers.size()); ++i) {
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

    // Generate performance stats in json format to an output path (refers to compareSortAlgorithms function)
    void outputComparison(const std::vector<Cuber>& unsorted_cubers, const std::string& outputPath) {
        // Create copies of same unsorted vector of Cubers
        std::vector<Cuber> ms_copy = unsorted_cubers;
        std::vector<Cuber> qs_copy = unsorted_cubers;

        auto startM = std::chrono::high_resolution_clock::now();
        mergeSort(ms_copy, 0, ms_copy.size() - 1);
        auto endM = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> durationM = endM - startM;

        auto startQ = std::chrono::high_resolution_clock::now();
        quickSort(qs_copy, 0, qs_copy.size() - 1);
        auto endQ = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> durationQ = endQ - startQ;

        std::ofstream file(outputPath);
        if (!file) {
            std::cerr << "Couldn't open " << outputPath << "\n";
            return;
        }
        // Outputs duration taken for each sort respectively
        file << "{\"mergeSort\":" << durationM.count()
            << ", \"quickSort\": " << durationQ.count()
            << "}";
    }
}