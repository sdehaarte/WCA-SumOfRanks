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
    
    // implement SumOfRanks here

    std::vector<Cuber> loadAndCalculateSumOfRanks() {
        std::vector<Cuber> cubers;
        std::unordered_map<std::string, size_t> idToIndex;
        std::unordered_map<std::string, std::string> cuberName;
        std::unordered_map<std::string, std::unordered_map<std::string, size_t> > eventRank;
        std::unordered_map<std::string, std::unordered_set<std::string> > eventCubers;
        std::unordered_map<std::string, size_t> eventLastRank;

        loadCuberInfo("../data/WCA_export_Persons.tsv", cuberName);
        parseTSVFile("../data/Preprocessed_RanksSingle.tsv", cubers, idToIndex, cuberName, eventRank, eventCubers, eventLastRank);
        parseTSVFile("../data/Preprocessed_RanksAverage.tsv", cubers, idToIndex, cuberName, eventRank, eventCubers, eventLastRank);

        return cubers;
    };

    
    void mergeSort(std::vector<Cuber>& cubers, int low, int high);

    void merge(std::vector<Cuber>& cubers, int low, int mid, int high);

    void quickSort(std::vector<Cuber>& cubers, int low, int high);

    int partition(std::vector<Cuber>& cubers, int low, int high);

    void outputJson(const std::vector<Cuber>& cubers, const std::string& outputPath, size_t N) {
        std::ofstream file(outputPath);
        if (!file) {
            std::cerr << "Couldn't open " << outputPath << "\n";
            return;
        }
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

    void outputComparison(const std::vector<Cuber>& competitors) {

    }
}
