#include <algorithm>
#include <cctype>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <list>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using ull = unsigned long long;

ull solve(std::ifstream &file)
{
    std::list<std::pair<ull, ull>> ranges;

    std::string line, seed_range_start, seed_range_len;
    std::getline(file, line);
    std::istringstream seeds_str{line.substr(7)}; // Ignore the "seeds : " part

    while (seeds_str >> seed_range_start >> seed_range_len) {
        ull seed_range_start_int = std::stoull(seed_range_start),
            seed_range_len_int = std::stoull(seed_range_len);
        ranges.push_back(std::make_pair(seed_range_start_int, seed_range_start_int + seed_range_len_int - 1));
    }


    size_t i = 0;

    std::vector<std::pair<std::pair<ull, ull>, std::pair<ull, ull>>> curr_src_dest_ranges;

    while (std::getline(file, line) || i <= 8) {
        std::istringstream record{line};
        std::string num;
        record >> num;

        if (isdigit(num[0])) {
            std::string dest_range_start = num, src_range_start, range_len;
            record >> src_range_start >> range_len;

            ull src_range_start_int = std::stoull(src_range_start),
                range_len_int = std::stoull(range_len),
                dest_range_start_int = std::stoull(dest_range_start);

            curr_src_dest_ranges.push_back(std::make_pair(
                std::make_pair(src_range_start_int, src_range_start_int + range_len_int - 1),
                std::make_pair(dest_range_start_int, dest_range_start_int + range_len_int - 1)
            ));

            continue;
        }

        if (++i != 8) {
            std::string newline;
            std::getline(file, newline);
        }

        if (i == 1)
            continue;

        std::list<std::pair<unsigned long long, unsigned long long>> new_ranges;
        std::sort(curr_src_dest_ranges.begin(), curr_src_dest_ranges.end());
        ranges.sort();

        for (auto csdr_it = curr_src_dest_ranges.cbegin(); csdr_it != curr_src_dest_ranges.cend(); ++csdr_it) {
            ull a1 = csdr_it->first.first,
                b1 = csdr_it->first.second,
                a2 = csdr_it->second.first;

            for (auto it = ranges.begin(); it != ranges.end(); ++it) {
                if (((a1 < it->first && a1 < it->second) && (b1 < it->first && b1 < it->second)))
                    break;

                if (((a1 > it->first && a1 > it->second) && (b1 > it->first && b1 > it->second)))
                    continue;

                if (a1 > it->first) {
                    new_ranges.push_back(std::make_pair(it->first, a1 - 1));
                    it->first = a1;
                } 

                if (b1 < it->second) {
                    auto new_sec = it->second;
                    ++it;
                    ranges.insert(it, std::make_pair(b1 + 1, new_sec));
                    --it; --it;
                    it->second = b1;
                }

                auto len = a2 - a1, new_a = it->first + len, new_b = it->second + len;

                new_ranges.push_back(std::make_pair(new_a, new_b));
            }
        }

        if (!new_ranges.empty()) {
            auto it = ranges.crbegin();
            for (; it != ranges.crend(); ++it)
                if (it->first > curr_src_dest_ranges.back().first.second)
                    break;
            

            if (it != ranges.crend()) {
                for (; it != ranges.crbegin(); --it)
                    new_ranges.push_back(*it);

                new_ranges.push_back(*it);
            }

            ranges = new_ranges;
        }

        curr_src_dest_ranges.clear();
    }

    ranges.sort();

    return ranges.front().first;
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
