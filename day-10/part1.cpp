#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <set>

using ull = unsigned long long;

std::vector<std::pair<int, int>> get_next_possible_moves(char pipe)
{
    std::vector<std::pair<int, int>> next_possible_moves;

    switch (pipe) {
        case '|':
            next_possible_moves.push_back(std::make_pair(-1, 0));
            next_possible_moves.push_back(std::make_pair(1, 0));
            break;

        case '-':
            next_possible_moves.push_back(std::make_pair(0, -1));
            next_possible_moves.push_back(std::make_pair(0, 1));
            break;

        case 'L':
            next_possible_moves.push_back(std::make_pair(-1, 0));
            next_possible_moves.push_back(std::make_pair(0, 1));
            break;

        case 'J':
            next_possible_moves.push_back(std::make_pair(0, -1));
            next_possible_moves.push_back(std::make_pair(-1, 0));
            break;

        case '7':
            next_possible_moves.push_back(std::make_pair(1, 0));
            next_possible_moves.push_back(std::make_pair(0, -1));
            break;

        case 'F':
            next_possible_moves.push_back(std::make_pair(0, 1));
            next_possible_moves.push_back(std::make_pair(1, 0));
            break;

        case 'S':
            next_possible_moves.push_back(std::make_pair(1, 0));
            next_possible_moves.push_back(std::make_pair(0, 1));
            next_possible_moves.push_back(std::make_pair(-1, 0));
            next_possible_moves.push_back(std::make_pair(0, -1));
            break;

        default:
            break;
    }

    return next_possible_moves;
}

ull solve(std::ifstream &file)
{
    std::vector<std::string> grid;
    std::pair<int, int> start_pos;
    size_t y = 0, x = 0;
    
    // Parse input
    for (std::string line; std::getline(file, line); ++y) {
        for (x = 0; x != line.size(); ++x)
            if (line[x] == 'S')
                start_pos = std::make_pair(y, x); // Save starting S position

        grid.push_back(line);
    }

    y = start_pos.first;
    x = start_pos.second;

    std::set<std::pair<int, int>> found_pos;
    found_pos.insert(std::make_pair(y, x));

    size_t i = 0;
    bool reached_end = false;
    char curr_char = 'S';

    // Traverse the loop
    while (!reached_end) {
        bool found_next = false;
        ++i;

        for (auto [a, b] : get_next_possible_moves(curr_char)) {
            // Skip check if the move gets out of bounds
            if ((y == 0 && a == -1) || (y == grid.size() - 1 && a == 1) ||
                (x == 0 && b == -1) || (x == grid[y].size() - 1 && b == 1))
                continue;

            curr_char = grid[y + a][x + b];

            // End loop if it reaches the end
            if (i > 2 && curr_char == 'S') {
                reached_end = true;
                break;
            }

            // Check each possible move for a valid pipe
            for (auto [c, d] : get_next_possible_moves(curr_char)) {
                if (a != -c && b != -d)
                    continue;

                std::pair<int, int> curr_pos = std::make_pair(y + a, x + b);

                if (found_pos.find(curr_pos) != found_pos.end())
                    continue;

                y += a;
                x += b;
                found_pos.insert(curr_pos);
                found_next = true;
                curr_char = grid[y][x];
                break;
            }

            if (found_next)
                break;
        }
    }

    return i / 2;
}

int main(int argc, char *argv[])
{
    if (argc == 1) {
        std::cerr << "ERROR: you must pass a filename." << std::endl;
        return -1;
    }

    if (argc > 2) {
        std::cerr << "ERROR: too many arguments." << std::endl;
        return -1;
    }

    std::ifstream file(argv[1]);

    if (!file.is_open()) {
        std::cerr << "ERROR: cannot open file." << std::endl;
        return -1;
    }

    std::cout << solve(file) << std::endl;
    file.close();

    return 0;
}
