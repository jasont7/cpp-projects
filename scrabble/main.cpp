#include <iostream>
#include "scrabble.hpp"
#include <cassert>
#include <unordered_set>
#include <algorithm>
#include <string>

words_set_type Compute_Permutations(std::string tiles) {
    words_set_type tempMap{};

    sort(tiles.begin(), tiles.end());

    do {
        tempMap.insert({tiles}); // easy way to remove duplicates
    } while (std::next_permutation(tiles.begin(), tiles.end()));

    return tempMap;
}

int main(int argc, char *argv[]) {
    assert(argc > 1);

    auto dict = Read_Dictionary(argv[1]);

    assert(dict.size() > 0); // make sure there is a dictionary

    std::string tiles;
    while (std::getline(std::cin, tiles)) {
        std::cout << "Tiles: [" << tiles << "]" << std::endl;
        words_set_type result = Find_Best_Words(dict, tiles);
        int i = 0;
        for (std::string w: result) {
            std::cout << "Solution: " << ++i << " [" << w << "] Score [" << Score(w) << "]" << std::endl;
        }
    }

    return 0;
}