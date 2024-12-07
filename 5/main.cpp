#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

void print(int w) {
    std::cout << w << std::endl;
}

std::vector<int> split(std::string line, char delimiter) {
    std::vector<int> returnable;

    std::stringstream ss(line);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        returnable.push_back(stoi(token));
    }

    return returnable;
}

bool contains(std::vector<int> v, int x) {
    return std::find(v.begin(), v.end(), x) != v.end();
}

bool is_valid(std::vector<int> update_line, std::unordered_map<int, std::vector<int>> rules_map) {
    bool valid = true;

    for (int i = 0; i < update_line.size(); i++) {
        for (int j = i + 1; j < update_line.size(); j++) {
            if (contains(rules_map[update_line[i]], update_line[j])) {
                valid = false;
                break;
            }
        }

        if (!valid) {
            break;
        }
    }

    return valid;
}

void fix(std::vector<int> line, std::unordered_map<int, std::vector<int>> rules_map) {
    // Push to head whenever we run into an element that breaks the rules
    for (int i = 0; i < line.size(); i++) {
        for (int j = i + 1; j < line.size(); j++) {
            if (contains(rules_map[line[i]], line[j])) {
                // Push line[j] to head and delete it from the list
                line.emplace(line.begin(), line[j]);
                // line.erase(line.begin() + j + 1);
                return;
            }
        }
    }
}

void print_vec(std::vector<int> vec) {
    for(const auto elem : vec)
        std::cout << elem << ",";

    std::cout << std::endl;
}

int main() {
    std::ifstream inputfile("input.txt");
    if (!inputfile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    std::vector<int> rules;
    std::vector<std::string> updates;
    std::unordered_map<int, std::vector<int>> rule_map;

    while (std::getline(inputfile, line)) {
        if (line.empty()) {
            break;
        }
        rules = split(line, '|');

        if (rule_map.find(rules[0]) == rule_map.end()) {
            rule_map[rules[0]] = std::vector<int>();
        }

        rule_map[rules[1]].push_back(rules[0]);
    }

    while (std::getline(inputfile, line)) {
        updates.push_back(line);
    }

    // for (const auto& pair : rule_map) {
    //     std::cout << "Key: " << pair.first << "\n";
    //     for (int sec : pair.second) {
    //         std::cout << sec << ",";
    //     }
    //     std::cout << "\n";
    // }

    // Part one
    std::vector<int> update_line;
    std::vector<std::vector<int>> valid_lines;
    std::vector<std::vector<int>> invalid_lines;
    for (std::string update : updates) {
        update_line = split(update, ',');

        if (is_valid(update_line, rule_map))
            valid_lines.push_back(update_line);
        else
            invalid_lines.push_back(update_line);
    }

    int total = 0;
    for (const auto& line : valid_lines)
        total += line[line.size() / 2];

    print(total);

    // Part two
    bool attempt;
    int invalid_total = 0;
    for (std::vector<int> line : invalid_lines) {
        while (!is_valid(line, rule_map)) {
            attempt = false;
            // print_vec(line);
            for (int i = 0; i < line.size(); i++) {
                for (int j = i + 1; j < line.size(); j++) {
                    if (contains(rule_map[line[i]], line[j])) {
                        // Push line[j] to head and delete it from the list
                        line.emplace(line.begin(), line[j]);
                        line.erase(line.begin() + j + 1);
                        attempt = true;
                        break;
                    }
                }

                if (attempt)
                    break;
            }
            // print_vec(line);
        }
        std::cout << "LOL" << std::endl;
        invalid_total += line[line.size() / 2];
        print_vec(line);
    }

    // int invalid_total = 0;
    // for (const auto& line : invalid_lines) {
    //     print_vec(line);
    //     invalid_total += line[line.size() / 2];
    // }

    print(invalid_total);


    return 0;
}