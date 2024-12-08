#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>

std::vector<std::tuple<int, int>> find_coords(char c, std::vector<std::vector<char>> map) {
    std::vector<std::tuple<int, int>> ret;
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == c) {
                ret.push_back(std::make_tuple(i, j));
            }
        }
    }

    return ret;
}

void print_map(std::vector<std::vector<char>> map) {
    for (auto row : map) {
        for (char c : row) {
            std::cout << c;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool plot(int x, int y, std::vector<std::vector<char>> &map) {
    if ((x < 0) | (x >= map[0].size()) | (y < 0) | (y >= map.size())) {
        return false;
    } else if (map[x][y] == '#') {
        return false;
    } else if (map[x][y] != '.') {
        return true;
    }

    map[x][y] = '#';
    return false;
}

bool contains(std::tuple<int, int> coord, std::vector<std::tuple<int, int>> arr) {
    for (auto const& c : arr) {
        if (c == coord)
            return true;
    }

    return false;
}

int main() {
    std::ifstream file("input.txt");

    if(!file.is_open()) {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    std::string line;
    std::vector<std::vector<char>> map;
    while(std::getline(file, line)) {
        std::vector<char> data(line.begin(), line.end());
        map.push_back(data);
    }
    print_map(map);

    // For each symbol in [a-z][A-Z][0-9]
    // Find the coordinates of each occurrence
    // Plot [x0 - (x1 - x0), y0 - (y1 - y0)]
    //      [x1 + (x1 - x0), y1 + (y1 - y0)]
    // For each pair found

    std::vector<char> symbols;

    // Add lowercase letters (a-z)
    for(char c = 'a'; c <= 'z'; ++c) {
        symbols.push_back(c);
    }

    // Add uppercase letters (A-Z)
    for(char c = 'A'; c <= 'Z'; ++c) {
        symbols.push_back(c);
    }

    // Add digits (0-9)
    for(char c = '0'; c <= '9'; ++c) {
        symbols.push_back(c);
    }

    // Part one
    std::vector<std::tuple<int, int>> coords;
    std::vector<std::tuple<int, int>> factored_in;
    int i0, j0, i1, j1;
    int x, y;
    int total = 0;
    bool plotted;
    for (char c : symbols) {
        // std::cout << c << std::endl;
        coords = find_coords(c, map);

        for (int k = 0; k < coords.size(); k++) {
            for (int l = k + 1; l < coords.size(); l++) {
                std::tie(i0, j0) = coords[k];
                std::tie(i1, j1) = coords[l];
                // std::cout << i0 << "," << j0 << std::endl;
                // std::cout << i1 << "," << j1 << std::endl;
                // std::cout << std::endl;

                x = i0 - (i1 - i0);
                y = j0 - (j1 - j0);
                plotted = plot(x, y, map);
                if (plotted & !contains(std::make_tuple(x, y), factored_in)) {
                    total++;
                    factored_in.push_back(std::make_tuple(x, y));
                }

                x = i1 + (i1 - i0);
                y = j1 + (j1 - j0);
                plotted = plot(x, y, map);
                if (plotted & !contains(std::make_tuple(x, y), factored_in)) {
                    total++;
                    factored_in.push_back(std::make_tuple(x, y));
                }
            }
        }
    }

    print_map(map);

    for (auto row : map) {
        for (char c : row) {
            if (c == '#')
                total++;
        }
    }
    std::cout << total << std::endl << std::endl << std::endl;

    // Part two
    // Add diff until diff isnt out of bounds
    // Then add number of occurrences if its larger than 1
    total = 0;
    factored_in = std::vector<std::tuple<int, int>>();
    int n;
    for (char c : symbols) {
        // std::cout << c << std::endl;
        coords = find_coords(c, map);

        for (int k = 0; k < coords.size(); k++) {
            for (int l = k + 1; l < coords.size(); l++) {
                std::tie(i0, j0) = coords[k];
                std::tie(i1, j1) = coords[l];
                // std::cout << i0 << "," << j0 << std::endl;
                // std::cout << i1 << "," << j1 << std::endl;
                // std::cout << std::endl;

                n = 0;
                while (true) {
                    x = i0 - (i1 - i0) * n;
                    y = j0 - (j1 - j0) * n;
                    if ((x < 0) | (x >= map[0].size()) | (y < 0) | (y >= map.size()))
                        break;
                        
                    plotted = plot(x, y, map);
                    if (plotted & !contains(std::make_tuple(x, y), factored_in)) {
                        total++;
                        factored_in.push_back(std::make_tuple(x, y));
                    }
                    n++;
                }

                n = 0;
                while (true) {
                    x = i1 + (i1 - i0) * n;
                    y = j1 + (j1 - j0) * n;
                    if ((x < 0) | (x >= map[0].size()) | (y < 0) | (y >= map.size()))
                        break;
                        
                    plotted = plot(x, y, map);
                    if (plotted & !contains(std::make_tuple(x, y), factored_in)) {
                        total++;
                        factored_in.push_back(std::make_tuple(x, y));
                    }
                    n++;
                }
            }
        }
    }

    print_map(map);
    for (auto row : map) {
        for (char c : row) {
            if (c == '#')
                total++;
        }
    }
    std::cout << total << std::endl;

}