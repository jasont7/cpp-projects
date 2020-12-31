#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> filterSet(std::vector<int> set_1, std::vector<int> set_2) {

    std::vector<int> filtered {};

    size_t s1_size = set_1.size();
    size_t i {0};
    while (i < set_2.size()) {
        if (set_2.at(i) == set_1.at(0)) {
            if (i+s1_size > set_2.size()) {
                filtered.push_back(set_2.at(i));
                i++;
                continue;
            }

            bool foundSet = true;
            for (size_t j=i+1, k=1; j < i+s1_size && k < s1_size; j++, k++) {
                if (set_2.at(j) != set_1.at(k))
                    foundSet = false;
            }
            if (foundSet)
                i = i + s1_size;
            else {
                filtered.push_back(set_2.at(i));
                i++;
            }
        } else {
            filtered.push_back(set_2.at(i));
            i++;
        }
    }

    return filtered;
}

int main() {

    std::vector<int> set_1 {};
    std::vector<int> set_2 {};

    int n {};
    bool foundNeg1 {false};
    while (std::cin >> n) {
        if (n == -1) {
            foundNeg1 = true;
            continue;
        }

        if (!foundNeg1)
            set_1.push_back(n);
        else
            set_2.push_back(n);
    }

    std::vector<int> filtered_set {};
    if (set_1.size() > set_2.size())
        filtered_set = set_2;
    else
        filtered_set = filterSet(set_1, set_2);

    std::cout << "Data Set 1:";
    for (auto el : set_1)
        std::cout << " " << el;
    std::cout << std::endl;

    std::cout << "Data Set 2:";
    for (auto el : set_2)
        std::cout << " " << el;
    std::cout << std::endl;

    std::cout << "Filtered:";
    for (auto el : filtered_set) {
        std::cout << " " << el;
    }
    std::cout << std::endl;

    return 0;
}