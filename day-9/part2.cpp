#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using ll = long long;

ll solve(std::ifstream &file)
{
    ll total = 0;

    // Parse each line
    for (std::string line; std::getline(file, line); ) {
        std::vector<std::vector<ll>> sequences;
        std::vector<ll> curr_sequence;

        // Parse numbers
        std::istringstream iss{line};
        std::string number;
        while (iss >> number)
            curr_sequence.push_back(std::stoll(number));

        // Calculate differences
        for (size_t zero_count = 0, i = 0; curr_sequence.size() != zero_count; ++i) {
            sequences.push_back(curr_sequence);
            zero_count = 0;
            curr_sequence.clear();

            for (auto it = sequences[i].cbegin() + 1; it != sequences[i].cend(); ++it) {
                ll curr_num = *it - *(it - 1);
                curr_sequence.push_back(curr_num);
                zero_count += (curr_num == 0);
            }
        }

        // Calculate first values
        ll curr_val = 0;
        for (auto rit = sequences.crbegin(); rit != sequences.crend(); ++rit)
            curr_val = rit->front() - curr_val;

        total += curr_val;
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
