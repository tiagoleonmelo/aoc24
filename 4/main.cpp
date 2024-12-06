#include <iostream>
#include <fstream>
#include <vector>

int get_hits(std::string word, std::vector<std::string> puzzle, int i, int j) {
    // Check up-right, right, down-right, down
    std::string upright = "";
    std::string right = "";
    std::string downright = "";
    std::string down = "";

    for (int tmp_i = 0; tmp_i < word.size(); tmp_i++)
    {
        if (!((j + tmp_i) >= puzzle[i].size()) & !((i - tmp_i) < 0)) {
            upright += puzzle[i - tmp_i][j + tmp_i];
        }

        if (!((j + tmp_i) >= puzzle[i].size())) {
            right += puzzle[i][j + tmp_i];
        }

        if (!((j + tmp_i) >= puzzle[i].size()) & !((i + tmp_i) >= puzzle.size())) {
            downright += puzzle[i + tmp_i][j + tmp_i];
        }

        if (!((i + tmp_i) >= puzzle.size())) {
            down += puzzle[i + tmp_i][j];
        }
    }

    int hits = 0;
    if (upright == word) {
        hits += 1;
    }
    
    if (right == word) {
        hits += 1;
    }

    if (downright == word) {
        hits += 1;
    }

    if (down == word) {
        hits += 1;
    }
    

    return hits;
}

int count_word_occurrences(std::string word, std::vector<std::string> puzzle) {
    std::string line;
    int hits = 0;
    for (int i = 0; i < puzzle.size(); i++) {
        for (int j = 0; j < puzzle[i].size(); j++) {
            if (puzzle[i][j] == word[0]) {
                // std::cout << puzzle[i][j] << std::endl;
                hits += get_hits(word, puzzle, i, j);
            }
        }
    }

    return hits;
}

int get_diagonal_hits(std::vector<std::string> puzzle, int i, int j) {
    // Check / and \ diagonals
    // They must be equal to SAM or MAS
    std::string backslash; // \

    std::string slash; // /

    try
    {
        backslash = std::string() + puzzle.at(i - 1).at(j - 1) + puzzle.at(i).at(j) + puzzle.at(i + 1).at(j + 1);
    }
    catch(const std::exception& e)
    {
        
    }
    
    try
    {
        slash = std::string() + puzzle.at(i - 1).at(j + 1) + puzzle.at(i).at(j) + puzzle.at(i + 1).at(j - 1);
    }
    catch(const std::exception& e)
    {
        
    }

    return int((backslash == "SAM" | backslash == "MAS") & (slash == "SAM" | slash == "MAS"));
}


int count_xmas_occurrences(std::vector<std::string> puzzle) {
    int hits = 0;
    for (int i = 0; i < puzzle.size(); i++) {
        for (int j = 0; j < puzzle[i].size(); j++) {
            if (puzzle[i][j] == 'A') {
                hits += get_diagonal_hits(puzzle, i, j);
            }
        }
    }

    return hits;
}

int main() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Error" << std::endl;
    }

    std::string line;
    std::vector<std::string> puzzle; 

    while (std::getline(file, line)) {
        puzzle.push_back(line);
    }

    // Part one
    std::vector<std::string> words_to_find = { "XMAS", "SAMX" };

    int total_xs = 0;
    for (std::string word : words_to_find) {
        total_xs += count_word_occurrences(word, puzzle);
    }

    std::cout << total_xs << std::endl;

    // Part two
    int total_xmas = count_xmas_occurrences(puzzle);

    std::cout << total_xmas << std::endl;    

}