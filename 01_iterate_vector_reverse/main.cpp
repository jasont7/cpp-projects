#include <iostream>
#include <vector>
#include <algorithm>

int main() {

    std::vector<int> vec {};
    int a {};

    while (true) {
        std::cout << "Enter a number: ";
        if (std::cin >> a) {
            vec.push_back(a);
        } else {
            std::cout << "Input was invalid." << std::endl;
            std::cout << "Number of Values Entered: " << vec.size() << std::endl;

            std::cout << "Values (forwards): ";
            for (unsigned long i {0}; i < vec.size(); i++) {
                std::cout << vec.at(i);
                if (i < vec.size()-1)
                    std::cout << ", ";
            }
            std::cout<< std::endl;

            std::cout << "Values (reverse): ";
            std::vector<int> rev_vec (vec.rbegin(), vec.rend());
            for (unsigned long i {0}; i < rev_vec.size(); i++) {
                std::cout << rev_vec.at(i);
                if (i < rev_vec.size()-1)
                    std::cout << ", ";
            }
            std::cout << std::endl;

            std::cout << "Values (sorted): ";
            std::sort (vec.begin(), vec.end());
            for (unsigned long i {0}; i < vec.size(); i++) {
                std::cout << vec.at(i);
                if (i < vec.size()-1)
                    std::cout << ", ";
            }
            std::cout << std::endl;

            break;
        }
    }

    return 0;
}