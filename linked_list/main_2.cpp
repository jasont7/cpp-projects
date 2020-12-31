#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <iomanip>
#include <complex>
#include <vector>

#include "list.hpp"

int main()
{

    link_list<std::string> list;

    std::string line;
    // read one string at a time and insert at the end of the list
    while (getline(std::cin, line)) {
        list.push_back(line);
    }

    std::cout << "Capitals:" << std::endl;

    list.print();

    std::cout << std::endl;

    std::cout << std::boolalpha << "is Ottawa in the list? "    << list.exists("Ottawa") << std::endl;
    std::cout << std::boolalpha << "is Brazilia in the list? "  << list.exists("Brazilia") << std::endl;

    std::cout << "Size of list: " << list.size() << std::endl;

    if (list.front() != "Tokyo") {
        std::cout << "Something is wrong. Front should be Tokyo, not [" << list.front() << "]" << std::endl;
    }
    // remove a couple
    list.pop_front();
    list.pop_front();
    
    std::cout << "Size of list: " << list.size() << std::endl;
    list.print();

    // test the back
    if (list.back() != "Stockholm") {
        std::cout << "Something is wrong. Front back be Stockholm, not [" << list.back() << "]" << std::endl;
    }
    // insert one
    list.push_front("CCCC");
    // test that we can use front as a LHS
    list.front() = "Canberra";

    list.push_front("Cairo");
    list.push_back("Beijing");
    list.push_back("XXXX");
    // test that we can use back as a LHS
    list.back() = "Vienna";

    std::cout << "Size of list: " << list.size() << std::endl;
    list.print();

    // empty it
    
    list.clear();
    std::cout << "Size of list: " << list.size() << std::endl;
    list.print();

    list.clear();
    std::cout << "Size of list: " << list.size() << std::endl;
    list.print();

    return 0;

}
