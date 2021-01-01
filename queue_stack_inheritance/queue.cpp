#include "queue.hpp"
#include <iostream>
#include <vector>

// Pop operation to remove last element from stack.
void Queue::Pop() {
    if (IsEmpty()) {
        std::cout << "Cannot pop from empty Queue" << std::endl;
        exit(1);
    }
    data.erase(data.begin());
}