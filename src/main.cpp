#include "sum_of_ranks.h"
#include <string>
#include <iostream>

int main() {
    std::unordered_map<std::string, Cuber> avgPlayers;
    std::unordered_map<std::string, Cuber> singlePlayers;
    int maxRank1 = 0, maxRank2 = 0;

    parseTSVFile("Preprocessed_RanksAverage.tsv", avgPlayers, maxRank1, "_avg");
    parseTSVFile("Preprocessed_RankSingle.tsv", singlePlayers, maxRank2, "_single");

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