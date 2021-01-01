#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>

std::vector<std::string> alliterations(std::vector<std::string> words) {
    std::vector<std::string> A {};

    std::string allit = words.at(0);
    unsigned i = 0, j = i+1;
    while (j < words.size()) {
        if (words.at(j).at(0) == words.at(i).at(0)) {  // check if word[i] is alliteration of word[j]
            allit += " " + words.at(j);
            j++;
        } else {
            if (allit.find(' ') != std::string::npos)  // More than 1 word
                A.push_back(allit);
            allit = words.at(j);
            i = j++;
        }
    }
    if (allit.find(' ') != std::string::npos)
        A.push_back(allit);
    return A;
}

std::map<std::string, int> frequencies(std::vector<std::string> words) {
    std::map<std::string, int> frequencies {};
    for (auto word : words) {
        if (frequencies.find(word) == frequencies.end())  // Word not in map
            frequencies.insert_or_assign(word, 1);
        else
            frequencies.at(word)++;
    }
    return frequencies;
}

int main() {
    // Make a vector of all words in the input
    std::vector<std::string> words {};
    std::string input_word {};
    while (std::cin >> input_word)
        words.push_back(input_word);
    if (words.size() <= 1)
        exit(0);

    // Print all alliterations
    std::vector<std::string> A {};
    A = alliterations(words);
    for (size_t i=0; i < A.size(); i++)
        std::cout << "Alliteration " << i+1 << ": " << A.at(i) << std::endl;

    // Get frequencies of all words in the alliterations
    std::map<std::string, int> freq_map {};
    std::vector<std::string> A_words {};
    for (auto line : A) {
        std::stringstream ss(line);
        std::string word {};
        while (ss >> word)
            A_words.push_back(word);
    }
    freq_map = frequencies(A_words);

    // Print frequencies
    std::cout << "\nWord Frequencies:" << std::endl;
    std::map<std::string, int> unique_words {};
    for (auto word : A_words) {
        if (unique_words.find(word) == unique_words.end()) {  // Word not in unique_words, is unique
            unique_words.insert_or_assign(word, 1);
            std::cout << word << ' ' << freq_map.at(word) << std::endl;
        }
    }

    return 0;
}