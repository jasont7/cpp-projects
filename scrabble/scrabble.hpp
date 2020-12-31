#ifndef __SCRABBLE_HPP__

#include <map>
#include <set>
#include <string>

typedef std::map<std::string, int> dict_type;
typedef std::set<std::string> words_set_type;

words_set_type Compute_Permutations(std::string tiles);

int Score(const std::string &word);
dict_type Read_Dictionary(const std::string &filename);
words_set_type Find_Best_Words(const dict_type &dict, std::string &tiles);

#endif