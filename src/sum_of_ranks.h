#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>

struct Cuber {
    std::string wcaId;
    std::string name;
    int sumOfRanks;
    std::unordered_map<std::string, size_t> eventRanks;
    Cuber() : sumOfRanks(0) {}
    Cuber(const std::string& wcaId, const std::string& name, size_t sumOfRanks) : wcaId(wcaId), name(name), sumOfRanks(sumOfRanks) {}
};

namespace SorTools {

    void parseTSVFile(const std::string& filename,
        std::vector<Cuber>& cubers,
        std::unordered_map<std::string, size_t>& idToIndex,
        std::unordered_map<std::string, std::string>& cuberName,
        std::unordered_map<std::string, std::unordered_map<std::string, size_t>>& eventRank,
        std::unordered_map<std::string, std::unordered_set<std::string>>& eventCubers,
        std::unordered_map<std::string, size_t>& eventLastRank);
    std::vector<Cuber> loadAndCalculateSumOfRanks();

    void mergeSort(std::vector<Cuber>& cubers, int low, int high);
    void merge(std::vector<Cuber>& cubers, int low, int mid, int high);

    void quickSort(std::vector<Cuber>& cubers, int low, int high);
    int partition(std::vector<Cuber>& cubers, int low, int high);
    
    void outputJson(const std::vector<Cuber>& cubers, const std::string& outputPath);
    void outputComparison(const std::vector<Cuber>& competitors);
}