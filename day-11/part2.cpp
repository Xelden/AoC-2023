#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using ull = unsigned long long;

ull get_distances(const std::vector<size_t> &galaxy_counts_vec)
{
    ull total = 0;
    size_t galaxy_count = 0, distances = 0;

    for (size_t curr_galaxy_count : galaxy_counts_vec)
        if (curr_galaxy_count == 0) {
            distances += 1e6 * galaxy_count;
        } else {
            total += distances * curr_galaxy_count;
            galaxy_count += curr_galaxy_count;
            distances += galaxy_count;
        }

    return total;
}

ull solve(std::ifstream &file)
{
    std::string line;
    std::getline(file, line); 

    std::vector<size_t> galaxy_counts_per_rows, galaxy_counts_per_cols(line.size());
    size_t x = 0;

    do {
        galaxy_counts_per_rows.push_back(0);

        x = 0;
        for (char a : line) {
            if (a == '#') {
                ++galaxy_counts_per_cols[x];
                ++galaxy_counts_per_rows.back();
            }
            ++x;
        }
    } while (std::getline(file, line));

    return get_distances(galaxy_counts_per_rows) + get_distances(galaxy_counts_per_cols); 
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

