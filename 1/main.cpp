#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

int count(std::vector<int> list, int find) {
    int occurrences = 0;

    for (int item : list){
        if (item > find) {
            break;
        } else if (item == find) {
            occurrences++;
        }
    }

    return occurrences;
}

int main() {

    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Error" << std::endl;
    }

    std::string line;
    std::vector<int> firstWords;
    std::vector<int> secondWords;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string firstWord, secondWord;
        ss >> firstWord >> secondWord; // Extract first and second word
        firstWords.push_back(stoi(firstWord));
        secondWords.push_back(stoi(secondWord));
    }

    std::sort(firstWords.begin(), firstWords.end());
    std::sort(secondWords.begin(), secondWords.end());

    // Part one
    int distance = 0;
    for (int i = 0; i < firstWords.size(); i++)
    {
        distance += std::abs(firstWords[i] - secondWords[i]);
    }
    std::cout << distance << std::endl;

    // Part two
    int sim = 0;
    for(const auto& word : firstWords) {
       sim += word * count(secondWords, word);
    }
    std::cout << sim << std::endl;

    return 0;

}