#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>

void print_vec(std::vector<char> vec) {
    for(const auto elem : vec)
        std::cout << elem << ",";

    std::cout << std::endl;
}

long long calculate(std::vector<int> numbers, std::vector<char> ops) {
    long long total = numbers[0];
    // Given N numbers and N-1 ops, combine everything
    for (int i = 0; i < numbers.size() - 1; i++) {
        if (ops[i] == '+') {
            total += numbers[i + 1];
        } else if (ops[i] == '*') {
            total *= numbers[i + 1];
        }
    }

    return total;
}

bool brute_force(long long target, int m, std::vector<int> numbers) {
    int totalCombinations = 1 << m; // 2^m combinations
    std::vector<char> charArray(m, '*'); // Default to '*' for all slots


    for (int i = 0; i < totalCombinations; ++i) {
        for (int j = 0; j < m; ++j) {
            // Check if the j-th bit of i is set (1) or not (0)
            if ((i >> j) & 1) {
                charArray[m - j - 1] = '+'; // If bit is 1, use '+'
            } else {
                charArray[m - j - 1] = '*'; // If bit is 0, use '*'
            }
        }

        print_vec(charArray);

        if (calculate(numbers, charArray) == target) {
            return true;
        }
    }

    return false;
}

bool solve(long long target, std::vector<int> numbers) {
    // If the product of everything is smaller than the test, its a fail
    // std::vector<char> ops;
    // int result;
    // for (int i = 0; i < numbers.size() - 1; i++) {
    //     ops.push_back('*');
    // }

    // result = calculate(numbers, ops);
    // if (result < target) {
    //     return false;
    // } else if (result == target) {
    //     return true;
    // }

    // // If the sum of everything is bigger than the test, its a fail
    // ops = std::vector<char>();
    // for (int i = 0; i < numbers.size() - 1; i++) {
    //     ops.push_back('+');
    // }

    // result = calculate(numbers, ops);
    // if (result > target) {
    //     return false;
    // } else if (result == target) {
    //     return true;
    // }   

    // Try out every different combination
    // Generate 2^(numbers.size() - 1) combinations
    return brute_force(target, numbers.size() - , numbers);
}

int main() {
    // Define the unordered map to store int keys and vector<int> values
    std::unordered_map<long long, std::vector<int>> data;

    // Open the input file
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Error: Could not open the file." << std::endl;
        return 1; // Exit the program with an error code
    }

    std::string line;
    // Read the file line by line
    while (std::getline(inputFile, line)) {
        std::istringstream lineStream(line);
        long long key;
        char colon;
        lineStream >> key >> colon; // Read the key and the colon

        std::vector<int> values;
        int value;
        // Read all the integers following the colon
        while (lineStream >> value) {
            values.push_back(value);
        }

        // Store the key-value pair in the unordered_map
        data[key] = values;
    }

    inputFile.close();

    // Print the unordered map to verify
    for (const auto& pair : data) {
        std::cout << pair.first << ": ";
        std::cout << std::endl;
    }

    bool valid;
    std::vector<long long> valid_n;
    for (const auto& pair : data) {
        for (const auto& val : pair.second) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
        valid = solve(pair.first, pair.second);
        if (valid) {
            valid_n.push_back(pair.first);
        }
    }

    long long total = 0;
    for (long long v : valid_n)
        total += v;

    std::cout << total << std::endl;


    return 0;
}
