#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

using ull = unsigned long long;

ull solve(std::ifstream& file)
{
    int bag[3] = { 12, 13, 14 };
    ull id_sum = 0;

    for (std::string line; std::getline(file, line); ) {
        std::istringstream record{line.substr(5)}; // Ignore the "Game" part
        std::string id;

        record >> id;
        id.pop_back();
        id_sum += std::stoi(id);

        for (std::string amount, color; record >> amount >> color; ) {
            if (!std::isalpha(color.back()))
                color.pop_back();

            // 'r' % 3 == 0, 'g' % 3 == 1, 'b' % 3 == 2
            if (std::stoi(amount) > bag[color[0] % 3]) {
                id_sum -= std::stoi(id);
                break;
            }
        }
    }

    return id_sum;
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
