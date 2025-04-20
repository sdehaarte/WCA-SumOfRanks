#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>

struct Player {
    std::string personId;
    std::unordered_map<std::string, int> eventRanks;
    int totalRank = 0;
};

const std::vector<std::string> allEvents = {
    "222_avg", "333_avg", "333fm_avg", "333oh_avg","444_avg",
    "555_avg", "666_avg","777_avg", "clock_avg", "minx_avg",
    "pyram_avg", "skewb_avg","sq1_avg",

    "333bf_single", "333_mbf_single", "444bf_single","555bf_single",
};

void parseTSVFile(const std::string& filename, std::unordered_map<std::string, Player>& players, int& maxRank, const std::string& suffix) {
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

void displayTopN(const std::vector<Player>& players, int n) {
    for (int i = 0; i < std::min(n, (int)players.size()); ++i) {
        std::cout << i + 1 << ". " << players[i].personId
                  << " - Total Rank: " << players[i].totalRank << "\n";
    }
}

int main() {
    std::unordered_map<std::string, Player> avgPlayers;
    std::unordered_map<std::string, Player> singlePlayers;
    int maxRank1 = 0, maxRank2 = 0;

    parseTSVFile("WCA_export_RanksAverage.tsv", avgPlayers, maxRank1, "_avg");
    parseTSVFile("WCA_export_RankSingle.tsv", singlePlayers, maxRank2, "_single");

        std::cout << "\nMenu:\n";
        std::cout << "1. Sort using Merge Sort\n";
        std::cout << "2. Sort using Quick Sort\n";
        std::cout << "3. Compare Merge Sort vs Quick Sort\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            mergeSort(players, 0, players.size() - 1);
            int n;
            std::cout << "Enter number of players: ";
            std::cin >> n;
            displayTopN(players, n);
        } else if (choice == 2) {
            quickSort(players, 0, players.size() - 1);
            int n;
            std::cout << "Enter number of players: ";
            std::cin >> n;
            displayTopN(players, n);
        } else if (choice == 3) {
            // call compare algorithm function
        } else if (choice == 4) {
            std::cout << "Ending Program...";
        } else {
            std::cout << "Invalid Choice!\n";
        }
    return 0;
}