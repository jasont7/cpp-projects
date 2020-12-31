#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <fstream>
#include <cassert>
#include "scrabble.hpp"


int Score(const std::string &word) {
    static std::map<char, int> scoreTable {
            {'a',1},{'e',1},{'i',1},{'l',1},{'n',1},{'o',1},{'r',1},
            {'s',1},{'t',1},{'u',1},{'d',2},{'g',2},{'b',3},{'c',3},
            {'m',3},{'p',3},{'f',4},{'h',4},{'v',4},{'w',4},{'y',4},
            {'k',5},{'j',8},{'x',8},{'q',10},{'z',10}
    };

    int score {};
    for (auto c : word) {
        score += scoreTable.at(c);
    }
    return score;
}


dict_type Read_Dictionary(const std::string &filename) {
    dict_type dict;
    std::ifstream file {};
    file.open(filename);

    int numWords {};
    std::string word {};
    while (std::getline(file, word)) {
        dict[word] = Score(word);
        numWords++;
    }
    std::cout << "Read " << numWords << " words." << std::endl;
    return dict;
}

words_set_type Find_Best_Words(const dict_type &dict, std::string &tiles) {
    words_set_type bestWords;
    std::map<int, std::set<std::string>> scores {};
    int highestScore {};
    scores[highestScore] = {};

    words_set_type permutations {Compute_Permutations(tiles)};
    for (auto &p : permutations) {
        std::string sequence {p};
        while (!sequence.empty()) {
            if (dict.find(sequence) != dict.end()) { // sequence is a valid word
                int wordScore {Score(sequence)};
                if (wordScore >= highestScore) {
                    highestScore = wordScore;
                    if (scores.find(wordScore) != scores.end())
                        scores.at(wordScore).insert(sequence);
                    else
                        scores[wordScore] = {sequence};
                }
                break; // only first valid sequence is needed
            }
            sequence.pop_back();
        }
    }
    bestWords = scores.at(highestScore);
    return bestWords;
}