#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <iomanip>
#include <complex>
#include <vector>

#include "list.hpp"

// almost the same as test 3 but ordered


int main()
{
    link_list<std::string> list;

    std::string line;
    // read one string at a time and insert at the end of the list
    while (getline(std::cin, line)) {
        list.insert_ordered(line);
    }

    std::cout << "Capitals:" << std::endl;

    list.print();

    std::cout << std::endl;

    std::cout << std::boolalpha << "is Ottawa in the list? "    << list.exists("Ottawa") << std::endl;
    std::cout << std::boolalpha << "is Brazilia in the list? "  << list.exists("Brazilia") << std::endl;

    std::cout << "Size of list: " << list.size() << std::endl;

    if (list.front() != "Amsterdam") {
        std::cout << "Something is wrong. Front should be Amsterdam, not [" << list.front() << "]" << std::endl;
    }
    // remove a couple
    list.pop_front();
    list.pop_front();
    
    std::cout << "Size of list: " << list.size() << std::endl;
    list.print();

    // test the back
    if (list.back() != "Washington") {
        std::cout << "Something is wrong. Front should be Washington, not [" << list.back() << "]" << std::endl;
    }
    // insert one

    list.insert_ordered("Canberra");
    list.insert_ordered("Cairo");
    list.insert_ordered("Beijing");
    list.insert_ordered("Algiers");
    list.insert_ordered("Zagreb");
    list.insert_ordered("Vienna");

    std::cout << "Size of list: " << list.size() << std::endl;
    list.print();

    // empty it by hand

    for(auto i=list.size(); i>0;i--) {
        std::cout << "Front: " << std::setw(13) << std::left << list.front() << " Back: " << list.back() << std::endl;
        list.pop_front();
    }

    // empty it  again
    
    list.clear();
    std::cout << "Size of list: " << list.size() << std::endl;
    list.print();
 
   return 0;
}
