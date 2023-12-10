#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

using ull = unsigned long long;

ull solve(std::ifstream &file)
{
    ull total = 0;
    std::vector<std::pair<int, int>> cards; // first is score, second is copies
    size_t curr_card_num = 0;

    for (std::string line; std::getline(file, line); ) {
        ++curr_card_num;

        std::istringstream record{line.substr(line.find(":") + 1)};  // Ignore the "Card n: " part
        std::unordered_set<int> winning_nums;
        bool winning = true;
        size_t curr_score = 0;

        for (std::string nums; record >> nums; )
            if (nums == "|")
                winning = false;
            else if (winning)
                winning_nums.insert(std::stoi(nums));
            else 
                curr_score += winning_nums.find(std::stoi(nums)) != winning_nums.end();

        // Update the score for current card
        if (cards.size() < curr_card_num)
            cards.push_back(std::make_pair(curr_score, 1));
        else
            cards[curr_card_num - 1].first = curr_score;

        total += cards[curr_card_num - 1].second;

        // Update the copies of the next cards
        for (size_t i = curr_card_num + 1; i <= curr_card_num + curr_score; ++i) {
            if (cards.size() < i)
                cards.push_back(std::make_pair(i, 1));

            cards[i - 1].second += cards[curr_card_num - 1].second;
        }
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
