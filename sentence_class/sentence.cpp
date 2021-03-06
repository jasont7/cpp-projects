#include <iostream>
#include <functional>
#include <string>
#include <vector>

class Sentence {
private:
    std::vector<std::string> words_;

    bool invalid_index(int pos) {
        return pos < 0 || pos >= word_count();
    }
public:
    /* Constructs an empty sentence.
     * This constructor is fully implemented.
     */
    Sentence() {}

    /* Copy the Sentence passed to it into a new Sentence.
     * This constructor is fully implemented.
     */
    Sentence(const Sentence& s) : words_ {s.words_} {}

    /* Returns the number words in the sentence.
     * This function is fully implemented.
     */
    int word_count() {
        return static_cast<int>(words_.size());
    }

    /*
     * Inserts "word" at the end of the sentence.
     */
    void append(const std::string& word) {
        std::string W {word};
        W.push_back('.');
        if (!words_.empty()) {
            words_.back().back() = ' ';
        } else {
            W.at(0) = toupper(W.at(0));
        }
        words_.push_back(W);
    }

    /*
     * Inserts "word" into the specified index position "pos".
     * If a word already exists at the index, then words should be shifted over to make room.
     * If "pos" is an invalid index, throw a std::invalid_argument exception.
     */
    void insert(const std::string& word, int pos) {
        if (pos == int(words_.size())) { // Insert back/empty
            append(word);
        } else if (pos == 0) { // Insert front
            std::string W {word};
            W.at(0) = toupper(W.at(0));
            W.push_back(' ');
            words_.at(0).at(0) = tolower(words_.at(0).at(0));
            words_.insert(words_.begin(), W);
        } else if (!invalid_index(pos)) { // Insert middle
            std::string W {word};
            W.push_back(' ');
            words_.insert(words_.begin()+pos, W);
        } else if (invalid_index(pos))
            throw std::invalid_argument("Invalid index");
    }

    /*
     * Erases the word at the specified index position "pos".
     * If "pos" is an invalid index, throw a std::invalid_argument exception.
     */
    void erase(int pos) {
        if (pos == 0 && !invalid_index(pos)) { // Erase front
            words_.erase(words_.begin());
            if (word_count() > 0)
                words_.at(0).at(0) = toupper(words_.at(0).at(0));
        } else if (!invalid_index(pos)) // Erase middle
            words_.erase(words_.begin() + pos);
        else
            throw std::invalid_argument("Invalid index");
    }

    /*
     * Returns the word at index "pos" if it's a valid index.
     * The returned word must reflect expected sentence formatting.
     * 		If "pos" = 0, then the word returned must be capitalized.
     * 		If "pos" = word_count()-1, then the word returned should have a period at the end.
     * If "pos" is an invalid index, throw a std::invalid_argument exception.
     */
    std::string at(int pos) {
        if (!invalid_index(pos)) {
            std::string word {words_.at(pos)};
            if (word.back() == ' ')
                word.pop_back();
            return word;
        } else
            throw std::invalid_argument("Invalid index");
    }

    /*
     * Returns a new sentence consisting of the words between [start, end).
     * The subsentence of "Vast active living intelligence system." between [2, 4) is "Living intelligence."
     */
    Sentence subsentence(int start, int end) {
        Sentence newSentence {};
        if (!invalid_index(start) && end <= word_count()) {
            if (start == end)
                throw std::invalid_argument("Invalid range");
            for (size_t i=start; i < end; i++) {
                std::string word = words_.at(i);
                word.pop_back();
                newSentence.append(word);
            }
        } else
            throw std::invalid_argument("Invalid range");
        return newSentence;
    }

    /*
     * Returns a std::string holding the properly formatted sentence.
     */
    std::string to_string() {
        std::string sentence {};
        for (const auto& word : words_)
            sentence += word;
        return sentence;
    }
};


Sentence bjarne_quote() {
    Sentence quote {};

    quote.append("within");
    quote.append("C++,");
    quote.append("there");
    quote.append("is");
    quote.append("a");
    quote.append("smaller");
    quote.append("and");
    quote.append("cleaner");
    quote.append("language");
    quote.append("struggling");
    quote.append("to");
    quote.append("get");
    quote.append("out");

    return quote;
}

void evaluate_exception(std::function<void()> test) {
    static std::string fail {"FAIL\n"};
    static std::string pass {"PASS\n"};

    try {
        test();
        std::cout << fail;
    } catch (std::invalid_argument& e) {
        std::cout << pass;
    }
}

void evaluate_test(bool result) {
    static std::string fail {"FAIL\n"};
    static std::string pass {"PASS\n"};

    if (result) {
        std::cout << pass;
    } else {
        std::cout << fail;
    }
}

int main() {
    Sentence empty_sentence {};
    Sentence quote_sentence {bjarne_quote()};

    std::cout << "Testing Exceptions\n";

    std::cout << "\t\"insert\" -1: ";
    evaluate_exception([&](){ empty_sentence.insert("ERROR", -1); });

    std::cout << "\t\"insert\" 1: ";
    evaluate_exception([&](){ empty_sentence.insert("ERROR", 1); });

    std::cout << "\t\"erase\" -1: ";
    evaluate_exception([&](){ empty_sentence.erase(-1); });

    std::cout << "\t\"erase\" 0: ";
    evaluate_exception([&](){ empty_sentence.erase(0); });

    std::cout << "\t\"erase\" 1: ";
    evaluate_exception([&](){ empty_sentence.erase(1); });

    std::cout << "\t\"at\" -1: ";
    evaluate_exception([&](){ empty_sentence.at(-1); });

    std::cout << "\t\"at\" 0: ";
    evaluate_exception([&](){ empty_sentence.at(0); });

    std::cout << "\t\"at\" 1: ";
    evaluate_exception([&](){ empty_sentence.at(1); });

    std::cout << "\t\"subsentence\" [-1 1): ";
    evaluate_exception([&](){ quote_sentence.subsentence(-1, 1); });

    std::cout << "\t\"subsentence\" [1 1): ";
    evaluate_exception([&](){ quote_sentence.subsentence(1, 1); });

    std::cout << "\t\"subsentence\" [0 1): ";
    evaluate_exception([&](){ empty_sentence.subsentence(-1, 1); });

    std::cout << "\t\"subsentence\" [3 100): ";
    evaluate_exception([&](){ quote_sentence.subsentence(3, 100); });

    std::cout << "\nTesting Functions\n";

    std::cout << "\t\"subsentence\" [8 10) and \"to_string\": ";
    evaluate_test(quote_sentence.subsentence(8, 10).to_string() == "Language struggling.");

    std::cout << "\t\"at\" 0: ";
    evaluate_test(quote_sentence.at(0) == "Within");

    std::cout << "\t\"at\" 1: ";
    evaluate_test(quote_sentence.at(1) == "C++,");

    std::cout << "\t\"at\" 12: ";
    evaluate_test(quote_sentence.at(12) == "out.");

    std::cout << "\t\"to_string\": ";
    evaluate_test(quote_sentence.to_string() == "Within C++, there is a smaller and cleaner language struggling to get out.");

    std::cout << "\t\"append\": ";
    empty_sentence.append("one");
    evaluate_test(empty_sentence.word_count() == 1 && empty_sentence.at(0) == "One.");

    std::cout << "\t\"insert\": ";
    empty_sentence.insert("zero", 0);
    evaluate_test(empty_sentence.word_count() == 2 && empty_sentence.at(0) == "Zero");

    std::cout << "\t\"insert\": ";
    empty_sentence.insert("two", 2);
    evaluate_test(empty_sentence.word_count() == 3 && empty_sentence.at(2) == "two.");

    std::cout << "\t\"erase\": ";
    empty_sentence.erase(0);
    evaluate_test(empty_sentence.word_count() == 2 && empty_sentence.at(0) == "One");

    std::cout << "\t\"erase\": ";
    empty_sentence.erase(1);
    evaluate_test(empty_sentence.word_count() == 1 && empty_sentence.at(0) == "One");

    return 0;
}