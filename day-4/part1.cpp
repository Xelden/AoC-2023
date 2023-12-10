#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <math.h>

using ull = unsigned long long;

ull solve(std::ifstream &file)
{
    ull total_score = 0;

    for (std::string line; std::getline(file, line); ) {
        std::istringstream record{line.substr(line.find(":") + 1)};  // Ignore the "Card n: " part
        std::unordered_set<int> winning_nums;
        bool winning = true;
        unsigned curr_score = 0;

        for (std::string nums; record >> nums; )
            if (nums == "|")
                winning = false;
            else if (winning)
                winning_nums.insert(std::stoi(nums));
            else
                curr_score += winning_nums.find(std::stoi(nums)) != winning_nums.end();

        if (curr_score)
            total_score += std::pow(2, curr_score - 1);
    }

    return total_score;
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
