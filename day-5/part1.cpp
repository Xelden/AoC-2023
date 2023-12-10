#include <algorithm>
#include <cctype>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using ull = unsigned long long;

ull solve(std::ifstream &file)
{
    struct map {
        std::vector<ull> values = {0, 0, 0, 0, 0, 0, 0, 0};
    };

    std::vector<map> maps; // Order is seed, soil, fert, water, light, temp, hum, loc;
    // std::unordered_set<int> seeds;

    std::string line, seed_num;
    std::getline(file, line);
    std::istringstream seeds_str{line.substr(line.find(' ') + 1)};
    size_t i = 0;

    while (seeds_str >> seed_num) {
        int num_int = std::stoull(seed_num);
        maps.push_back(map());
        maps.back().values[i] = num_int;
    }

    // std::cout << "before: " << std::endl;
    // for (auto a : maps) {
    //     for (auto b : a)
    //         std::cout << b << " ";
    //     std::cout << std::endl;
    // }

    while (std::getline(file, line) && i <= 8) {
        // std::cout << line << std::endl;
        std::istringstream record{line};
        std::string num;
        record >> num;

        if (!isdigit(num[0])) {
            if (num[0] == '\0' && i < 7) {
                ++i;
                for (auto &map : maps) {
                    if (map.values[i] == 0)
                        map.values[i] = map.values[i - 1];
                }
            }

            continue;
        }

        std::string dest_range_start = num, src_range_start, range_len;
        record >> src_range_start >> range_len;

        ull src_range_start_int = std::stoull(src_range_start),
            range_len_int = std::stoull(range_len),
            dest_range_start_int = std::stoull(dest_range_start);

        // std::cout << dest_range_start << " " << src_range_start << " " << range_len << std::endl;

        for (ull j = 0; j <= range_len_int - 1; ++j) {
            ull curr_num = src_range_start_int + j;
            auto seed_match = maps.begin();

            for (; seed_match != maps.end(); ++seed_match)
                if ((*seed_match).values[i - 1] == curr_num)
                    break;

            if (seed_match == maps.end())
                continue;

            (*seed_match).values[i] = curr_num + dest_range_start_int - src_range_start_int;
        }
    }

    ull lowest_loc = maps[0].values[7];

    for (auto it = maps.cbegin(); it != maps.cend(); ++it) {
        if (it->values[7] < lowest_loc)
            lowest_loc = it->values[7];
    }

    // std::cout << i << std::endl;

    // std::cout << "seed " << "soil " << "fert " << "wate " << "ligh " << "temp " << "humi " << "loca " << std::endl;
    // for (auto a : maps) {
    //     for (auto b : a.values)
    //         std::cout << b << "   ";
    //     std::cout << std::endl;
    // }

    return lowest_loc;
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
