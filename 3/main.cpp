#include <iostream>
#include <fstream>
#include <regex>
#include <vector>

int main() {
    // Go through line
    // When you find mul(
    // Next tokens need to be number comma number closing parenthesis
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Error" << std::endl;
    }

    std::regex const expr("mul\\((\\d+),(\\d+)\\)");
    std::string line;
    std::getline(file, line);
    std::cout << line << std::endl;

    // Part one
    std::sregex_iterator beginning(line.begin(), line.end(), expr);
    std::sregex_iterator ending;

    std::vector<int> results;
    for (auto it = beginning; it != ending; ++it) {
        std::smatch match = *it;

        results.push_back(stoi(match[1]) * stoi(match[2]));
    }

    int total = 0;
    for (int result : results) {
        total += result;
    }

    std::cout << total << std::endl;

    // Part two
    line.append("do()"); // Make sure it ends on a do() ;)

    // Delete all text between don't() and do()
    std::regex const remove("don't\\(\\).*?do\\(\\)");
    std::string replaced = std::regex_replace(line, remove, "");
    std::cout << replaced << std::endl;

    std::sregex_iterator replaced_beginning(replaced.begin(), replaced.end(), expr);
    std::sregex_iterator replaced_ending;

    std::vector<int> replaced_results;
    for (auto it = replaced_beginning; it != replaced_ending; ++it) {
        std::smatch match = *it;

        replaced_results.push_back(stoi(match[1]) * stoi(match[2]));
    }

    int replaced_total = 0;
    for (int result : replaced_results) {
        replaced_total += result;
    }

    std::cout << replaced_total << std::endl;



}