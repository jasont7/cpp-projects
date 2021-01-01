#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>

template<typename T>
class Queue {
public:
    void push(T elem) {
        queue.push_back(elem);
    }

    T pop() {
        if (!size()) {
            std::cout << "Cannot pop from empty Queue" << std::endl;
            exit(1);
        }

        T firstElem {queue.at(0)};
        queue.erase(queue.begin());
        return firstElem;
    }

    int size() {
        return int(queue.size());
    }
private:
    std::vector<T> queue {};
};


int main() {
    Queue<int> istack;

    std::vector<int> int_contents{1, 2, 3, 4, 5};
    std::cout << "Pushing: ";
    for (auto num : int_contents) {
        std::cout << num << " ";
        istack.push(num);
    }
    std::cout << std::endl;

    std::cout << "Popping: ";
    while (istack.size() > 0)
        std::cout << istack.pop() << " ";
    std::cout << std::endl;


    Queue<std::string> stringstack;

    std::vector<std::string> string_contents{"Apple", "Banana", "Grapefruit", "Kiwi", "Pear"};
    std::cout << "Pushing: ";
    for (auto str : string_contents) {
        std::cout << str << " ";
        stringstack.push(str);
    }
    std::cout << std::endl;

    std::cout << "Popping: ";
    while (stringstack.size() > 0)
        std::cout << stringstack.pop() << " ";
    std::cout << std::endl;

    return 0;
}