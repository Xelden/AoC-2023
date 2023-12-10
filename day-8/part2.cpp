#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

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

    std::vector<std::string> start_nodes;

    for (auto [a, b] : map)
        if (a[2] == 'A')
            start_nodes.push_back(a);
    
    std::vector<ull> moves_vec;

    for (std::string node : start_nodes) {
        std::string curr_node = node;
        size_t total_moves = 0, curr_move = 0;

        while (curr_node[2] != 'Z') {
            curr_node = instructions[curr_move] == 'L' ? map[curr_node].first : map[curr_node].second;
            ++total_moves;

            if (++curr_move == instructions.size())
                curr_move = 0;
        }

        moves_vec.push_back(total_moves);
    }

    ull lcm = 1;
    for (ull a : moves_vec)
        lcm = std::lcm(lcm, a);

    return lcm;
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
