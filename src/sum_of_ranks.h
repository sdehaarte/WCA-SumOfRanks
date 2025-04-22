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

    void parseTSVFile(
        const std::string& filename,
        std::vector<Cuber> & cubers,
        std::unordered_map<std::string, size_t>& idToIndex,
        const std::unordered_map<std::string, std::string>& cuberName,
        std::unordered_map<std::string, std::unordered_map<std::string, size_t> >& eventRank,
        std::unordered_map<std::string, std::unordered_set<std::string> >& eventCubers,
        std::unordered_map<std::string, size_t>& eventLastRank);

    void loadCuberInfo(
        const std::string& filename,
        std::unordered_map<std::string, std::string>& cuberName);
    
    // implement SumOfRanks here

    std::vector<Cuber> loadAndCalculateSumOfRanks();

    void mergeSort(std::vector<Cuber>& cubers, int low, int high);

    void merge(std::vector<Cuber>& cubers, int low, int mid, int high);

    void quickSort(std::vector<Cuber>& cubers, int low, int high);

    int partition(std::vector<Cuber>& cubers, int low, int high);

    void outputJson(const std::vector<Cuber>& cubers, const std::string& outputPath, size_t N);
    void outputComparison(const std::vector<Cuber>& competitors);
}
