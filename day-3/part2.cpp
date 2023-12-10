#include <cctype>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <utility>
#include <vector>

using ull = unsigned long long;

ull solve(std::ifstream &file)
{
    std::vector<std::string> grid;
    std::vector<std::pair<size_t, size_t>> symbols_coords;
    size_t y = 0;

    // Traverse grid searching for '*'
    for (std::string line; std::getline(file, line); grid.push_back(line)) {
        for (size_t x = line.find("*"); x != std::string::npos; x = line.find("*", ++x))
            symbols_coords.push_back(std::make_pair(y, x));

        ++y;
    }

    ull gear_ratio_sum = 0;

    for (auto [i, j] : symbols_coords){
        std::set<std::pair<int, int>> unique_nums_coords;
        std::vector<int> adjacent_nums;

        // Constraints for corners and sides
        int upper_row = (i > 0) ? -1 : 0,
            lower_row = (i < grid.size() - 1) ? 1 : 0,
            left_col = (j > 0) ? -1 : 0,
            right_col = (j < grid[i].length() - 1) ? 1 : 0;

        // Search for any adjacent number
        for (int k = upper_row; k <= lower_row; ++k) {
            const std::string &curr_row = grid[k + i];
            for (int l = left_col; l <= right_col; ++l) {
                if (!isdigit(curr_row[l + j]))
                    continue;

                // Find the start position of the current number
                size_t first_dig_pos = l + j - 1, last_dig_pos = l + j + 1;
                for (; isdigit(curr_row[first_dig_pos]); --first_dig_pos);
                std::pair<int, int> curr_pos = {k + i, ++first_dig_pos};

                // Check that current number wasn't already found
                if (unique_nums_coords.find(curr_pos) != unique_nums_coords.end())
                    continue;

                for (; isdigit(curr_row[last_dig_pos]); ++last_dig_pos);

                unique_nums_coords.insert(curr_pos);
                std::string curr_num;

                // Add current number to the list
                for (size_t m = first_dig_pos; m != last_dig_pos; ++m)
                    curr_num.push_back(curr_row[m]);
                adjacent_nums.push_back(stoi(curr_num));

                l = 0;
            }
        }

        if (adjacent_nums.size() == 2)
            gear_ratio_sum += (adjacent_nums[0] * adjacent_nums[1]);
    }

    return gear_ratio_sum;
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
