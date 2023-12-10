#include <cctype>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

using ull = unsigned long long;

ull solve(std::ifstream& input) {
    ull total = 0;

    for (std::string line; std::getline(input, line); ) {
        auto it = line.cbegin();
        for (; !isdigit(*it); ++it);
        
        auto ti = line.crbegin();
        for (; !isdigit(*ti); ++ti);

        total += (*it - '0') * 10 + (*ti - '0');
    }

    return total;
}

int main (int argc, char *argv[]) {
    if (argc == 1) {
        std::cerr << "ERROR: no file passed." << std::endl;
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

