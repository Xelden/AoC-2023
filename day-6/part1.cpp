#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using ull = unsigned long long;

ull solve(std::ifstream &file)
{
    // Parse input
    std::string line1, line2, time, dis;

    std::getline(file, line1);
    std::istringstream time_line{line1.substr(11)};

    std::getline(file, line2);
    std::istringstream dis_line{line2.substr(11)};

    ull total = 1;

    // Calculate roots for each race and update total
    while (time_line >> time && dis_line >> dis) {
        ull time_int = std::stoull(time),
            dis_int = std::stoull(dis),
            root = std::sqrt(time_int*time_int - 4 * (dis_int + 1)),
            upper = (time_int + root) / 2,
            lower = time_int - upper;

        total *= upper - lower + 1;
    }

    return total;
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
