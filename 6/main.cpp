#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>

int count_x(std::vector<std::vector<char>> map) {
    int total = 0;
    for (auto row : map) {
        for (char c : row) {
            if (c == 'X')
                total++;
        }
    }

    return total;
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

bool go_up(std::vector<std::vector<char>> &map, int i, int j) {
    // Returns true if we are still within the map (aka if we hit a box)
    int tmp_i = i;
    while (true) {
        if (map[tmp_i][j] == '#') {
            // Turn right on previous position
            map[tmp_i + 1][j] = '>';
            return true;
        }

        map[tmp_i][j] = 'X';

        if ((tmp_i - 1) < 0)
            return false;

        tmp_i--;
    }
}

bool go_right(std::vector<std::vector<char>> &map, int i, int j) {
    // Returns true if we are still within the map (aka if we hit a box)
    int tmp_i = i;
    int tmp_j = j;
    while (true) {
        if (map[tmp_i][tmp_j] == '#') {
            // Turn right on previous position
            map[tmp_i][tmp_j - 1] = 'v';
            return true;
        }

        map[tmp_i][tmp_j] = 'X';

        if ((tmp_j + 1) >= map[tmp_i].size())
            return false;

        tmp_j++;
    }
}

bool go_down(std::vector<std::vector<char>> &map, int i, int j) {
    // Returns true if we are still within the map (aka if we hit a box)
    int tmp_i = i;
    int tmp_j = j;
    while (true) {
        std::cout << tmp_i << " " << j << std::endl;

        if (map[tmp_i][j] == '#') {
            // Turn right on previous position
            map[tmp_i - 1][j] = '<';
            return true;
        }

        map[tmp_i][j] = 'X';

        if ((tmp_i + 1) >= map.size())
            return false;

        tmp_i++;
    }
}

bool go_left(std::vector<std::vector<char>> &map, int i, int j) {
    // Returns true if we are still within the map (aka if we hit a box)
    int tmp_i = i;
    int tmp_j = j;
    while (true) {
        if (map[tmp_i][tmp_j] == '#') {
            // Turn right on previous position
            map[tmp_i][tmp_j + 1] = '^';
            return true;
        }

        map[tmp_i][tmp_j] = 'X';

        if ((tmp_j - 1) < 0)
            return false;

        tmp_j--;
    }
}

bool pursue_direction(char direction, std::vector<std::vector<char>> &map, int i, int j) {
    if (direction == '^') {
        return go_up(map, i, j);
    } else if (direction == '>') {
        go_right(map, i, j);
    } else if (direction == 'v') {
        go_down(map, i, j);
    } else if (direction == '<') {
        go_left(map, i, j);
    }

    std::cout << map[i][j] << std::endl;

    return true;
}

std::tuple<int, int> get_direction(std::vector<std::vector<char>> map) {
    std::vector<char> possible_directions = { '^', '>', '<', 'v' };
    for (char direction : possible_directions) {
        for (int i = 0; i < map.size(); i++) {
            for (int j = 0; j < map[0].size(); j++) {
                if (map[i][j] == direction) {
                    return std::make_tuple(i, j);
                }
            }
        }
    }

    return std::make_tuple(-1, -1);
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

    // Find ^
    std::tuple<int, int> coords;
    bool within_map;
    int i, j;
    while (true) {
        std::tie(i, j) = get_direction(map);
        print_map(map);

        if(i == -1)
            break;

        within_map = pursue_direction(map[i][j], map, i, j);

        print_map(map);
        if (!within_map) {
            break;
        }
    }

    int count = count_x(map);
    std::cout << count << std::endl;

    return 0;
}