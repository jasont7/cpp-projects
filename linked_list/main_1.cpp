#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <iomanip>
#include <complex>
#include <vector>

#include "list.hpp"


int main() {

    // Let us test an empty list
    link_list<std::string> emptyList;
    
    std::cout << "Print empty list:" << std::endl;
    emptyList.print();

    std::cout << "Empty list size:" << emptyList.size() << std::endl;

    emptyList.clear();

    std::cout << "Empty list size:" << emptyList.size() << std::endl;


    // doing a front should return an exception
    try {
        auto x = emptyList.front();
    } catch (const std::runtime_error& e) {
        std::cout << "Good: Exception thrown when trying to pop from empty list" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Not good: Exception is not runtime error" << std::endl;
    }

    try {
        emptyList.pop_front();
    } catch (const std::runtime_error& e) {
        std::cout << "Good: Exception thrown when trying to pop from empty list" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Not good: Exception is not runtime error" << std::endl;
    }

}