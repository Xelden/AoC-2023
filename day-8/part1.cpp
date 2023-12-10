#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <sstream>
#include <string>
#include <utility>

using ull = unsigned long long;

ull solve(std::ifstream &file)
{
    std::map<std::string, std::pair<std::string, std::string>> map;
    std::string line, instructions;

    std::getline(file, instructions);
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::string node, left, right;
        std::istringstream iss{line};
        iss >> node >> left >> left >> right;
        map.insert(std::make_pair(node, std::make_pair(left.substr(1, 3), right.substr(0, 3))));
    }

    size_t moves = 0, curr_move = 0;
    std::string curr_node = "AAA";

    while (curr_node != "ZZZ") {
        curr_node = instructions[curr_move] == 'L' ? map[curr_node].first : map[curr_node].second;
        ++moves;

        if (++curr_move == instructions.size())
            curr_move = 0;
    }

    return moves;
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
