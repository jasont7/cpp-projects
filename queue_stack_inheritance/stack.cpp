#include "stack.hpp"
#include <iostream>


// Push operation to insert an element on top of stack.
void Stack::Push(int x) {
    data.push_back(x);
}

// This function will return (true) if stack is empty, (false) otherwise
bool Stack::IsEmpty() {
    return data.size() == 0;
}

// Pop operation to remove an element from top of stack.
void Stack::Pop() {
    if (IsEmpty()) {
        std::cout << "Cannot pop from empty Stack" << std::endl;
        exit(1);
    }
    data.pop_back();
}

// print elements in container
void Stack::Print() {
    for (auto i : data) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}