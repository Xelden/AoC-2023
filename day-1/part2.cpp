#include <cstddef>
#include <iostream>
#include <fstream>
#include <string>

using ull = unsigned long long;

ull solve(std::ifstream& input) {
    ull total = 0;

    const std::string numbers[9] = { "one", "two", "three", "four", "five",
                                     "six", "seven", "eight", "nine" };

    for (std::string line; std::getline(input, line); ) {
        size_t first = line.size() - 1, first_int = std::string::npos,
               last = 0, last_int = std::string::npos, pos = 0;

        for (size_t i = 0; i != 9; ++i) {
            pos = line.find(numbers[i]);
            if (pos != std::string::npos && pos < first) {
                first = pos;
                first_int = i;
            }
            
            pos = line.rfind(numbers[i]);
            if (pos != std::string::npos && pos > last) {
                last = pos;
                last_int = i;
            }
        }

        if (first_int != std::string::npos)
            line[first] = ++first_int + '0';

        if (last_int != std::string::npos)
            line[last] = ++last_int + '0';

        pos = 0;
        for (; !isdigit(line[pos]); ++pos);
        if (pos < first)
            first = pos;
        
        pos = line.size() - 1;
        for (; !isdigit(line[pos]); --pos);
        if (pos > last)
            last = pos;
        
        total += (line[first] - '0') * 10 + (line[last] - '0');
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
