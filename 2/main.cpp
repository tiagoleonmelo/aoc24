#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

int isSafe(std::vector<int> report) {
    bool ascending = report[0] < report[1];
    int safe = -1;
    for(int i = 0; i < report.size() - 1; i++) {
        int diff;
        if (ascending) {
            diff = report[i + 1] - report[i];
        } else {
            diff = report[i] - report[i + 1];
        }

        if (diff < 1 | diff > 3) {
            safe = i;
            break;
        }
    }

    return safe;
}

std::vector<int> removeElementByIndex(const std::vector<int>& vec, size_t indexToRemove) {
    std::vector<int> result;
    result.reserve(vec.size() - 1);

    std::copy_if(vec.begin(), vec.end(), std::back_inserter(result),
                 [&, currentIndex = 0](const int&) mutable {
                     return currentIndex++ != indexToRemove;
                 });

    return result;
}

int main() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Error" << std::endl;
    }

    std::string line;
    std::vector<std::vector<int>> matrix; 

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string word;
        std::vector<int> tmp;
        while (ss >> word) { // Extract word from the stream.
            tmp.push_back(stoi(word));
        }
        matrix.push_back(tmp);
    }
    
    // Part one
    std::vector<bool> safeties;
    bool safe;
    for (std::vector<int> report : matrix) {
        if (isSafe(report) == -1) {
            safeties.push_back(true);
        }
    }
    std::cout << safeties.size() << std::endl;

    // Part two
    std::vector<bool> dampenedSafeties;
    for (std::vector<int> report : matrix) {
        for(int ii = 0; ii < report.size(); ii++) {
            std::vector<int> copy;
            if (isSafe(removeElementByIndex(report, ii)) == -1) {
                dampenedSafeties.push_back(1);
                break;
            }
        }
    }
    std::cout << dampenedSafeties.size() << std::endl;    

    return 0;
}