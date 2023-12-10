#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using ull = unsigned long long;

ull solve(std::ifstream& file)
{
    ull pow_sum = 0;

    for (std::string line; std::getline(file, line); ) {
        std::istringstream record(line.substr(line.find(':') + 1)); // Ignore the "Game n: " part
        unsigned cubes_min_rgb[3] = {0};

        for (std::string amount, color; record >> amount >> color; ) {
            // 'r' % 3 == 0, 'g' % 3 == 1, 'b' % 3 == 2
            unsigned &current_cubes_min = cubes_min_rgb[color[0] % 3], amount_int = std::stoi(amount);
            current_cubes_min = std::max(current_cubes_min, amount_int);
        }

        pow_sum += (cubes_min_rgb[0] * cubes_min_rgb[1] * cubes_min_rgb[2]);
    }

    return pow_sum;
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
