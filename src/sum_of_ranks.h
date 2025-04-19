//
// Created by Sensi on 4/17/25.
//

#pragma once

#include <unordered_map>
#include <string>

struct Cuber {
    std::string wcaId;
    int sumOfRanks;
    std::string country;
    std::string continent;

    Cuber(const std::string& wcaId, int sumOfRanks, const std::string& country, const std::string& continent) : wcaId(wcaId), sumOfRanks(sumOfRanks), country(country), continent(continent) {}
};

namespace SorTools {

    std::vector<Cuber> loadData(const std::string& tsvFilePath);
    void calculateSumOfRanks(std::vector<Cuber>& cubers);

    void quickSort(std::vector<Cuber>& cubers, int low, int high);
    int partition(std::vector<Cuber>& cubers, int low, int high);

    void mergeSort(std::vector<Cuber>& cubers, int low, int high);
    void merge(std::vector<Cuber>& cubers, int low, int mid, int high);

    void outputJson(std::vector<Cuber>& cubers, const std::string& filename);
    void outputComparison(std::vector<Cuber>& competitors);
}