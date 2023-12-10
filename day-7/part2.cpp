#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using ull = unsigned long long;

struct play {
    play(std::string a, unsigned b):
        hand(a), bid(b), hand_type_val(get_hand_type_val()) {}

    bool operator<(const play &); // For sorting
    unsigned get_card_val(char);
    unsigned get_hand_type_val();

    std::string hand;
    unsigned bid, hand_type_val;
};

unsigned play::get_hand_type_val()
{
    std::unordered_map<char, size_t> card_counts;
    char max_card = this->hand[0];
    size_t max_card_count = 0;

    // Save cards along with their counts keeping track of the most common card
    for (char curr_card : this->hand)
        if (max_card_count < ++card_counts[curr_card] && curr_card != 'J') {
            max_card = curr_card;
            max_card_count = card_counts[curr_card];
        }

    size_t j_count = card_counts['J'];

    if (j_count == 5) // Account for JJJJJ
        return 7; // Five of a kind
    
    card_counts.erase('J');
    card_counts[max_card] += j_count;

    // Get the hand's type
    switch (card_counts.size()) {
        case 1:
            return 7; // Five of a kind

        case 2:
            for (auto a : card_counts)
                if (a.second == 4) 
                    return 6; // Four of a kind
            return 5; // Full house

        case 3:
            for (auto a : card_counts)
                if (a.second == 3) 
                    return 4;  // Three of a kind
            return 3; // Two pair
        
        case 4:
            return 2; // One pair

        default:
            return 1; // High card
    }
}

bool play::operator<(const play &rhs)
{
    if (this->hand_type_val != rhs.hand_type_val)
        return this->hand_type_val < rhs.hand_type_val;

    // In the case of a tie, compare each individual card for both hands against each other
    for (size_t i = 0; i != 5; ++i) {
        unsigned lhs_card = get_card_val(this->hand[i]),
                 rhs_card = get_card_val(rhs.hand[i]);

        if (lhs_card != rhs_card)
            return lhs_card < rhs_card;
    }

    return false;
}

unsigned play::get_card_val(char card)
{
    switch (card) {
        case 'A':
            return 13;
        case 'K':
            return 12;
        case 'Q':
            return 11;
        case 'T':
            return 10;
        case 'J':
            return 1;
        default:
            return (unsigned) card - '0';
    };
}

ull solve(std::ifstream &file)
{
    std::vector<play> plays;
    std::string line;

    // Parse input
    while (std::getline(file, line)) {
        std::istringstream curr_play{line};
        std::string hand, bid;
        curr_play >> hand >> bid;
        plays.push_back(play(hand, std::stoi(bid)));
    }

    // Sort data in order to get ranks
    sort(plays.begin(), plays.end());

    size_t i = 0;
    ull total = 0;

    for (play a : plays)
        total += a.bid * ++i;
    
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
