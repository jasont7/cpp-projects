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

    link_list<std::string> emptyList;
    
    std::cout << "Print empty list:" << std::endl;

    emptyList.print();

    std::cout << std::boolalpha << "are they equal? "    << (list == emptyList) << std::endl;
    std::cout << std::boolalpha << "are they different? "    << (list != emptyList) << std::endl;

    std::cout << std::boolalpha << "is list equal to itself? "    << (list == emptyList) << std::endl;
    std::cout << std::boolalpha << "is list different to itself? "    << (list != emptyList) << std::endl;

    std::cout << std::boolalpha << "is empty equal to itself? "    << (emptyList == emptyList) << std::endl;
    std::cout << std::boolalpha << "is empty different to itself? "    << (emptyList != emptyList) << std::endl;

    //copy the list

    auto list2 {list};

    list.print();
    list2.print();

    std::cout << std::boolalpha << "are they equal? "    << (list == list2) << std::endl;
    std::cout << std::boolalpha << "are they different? "    << (list != list2) << std::endl;

    list2.pop_front();
    list2.pop_front();

    list.print();
    list2.print();

    std::cout << std::boolalpha << "are they equal? "    << (list == list2) << std::endl;
    std::cout << std::boolalpha << "are they different? "    << (list != list2) << std::endl;

    list.pop_front();
    list.pop_front();

    list.print();
    list2.print();

    std::cout << std::boolalpha << "are they equal? "    << (list == list2) << std::endl;
    std::cout << std::boolalpha << "are they different? "    << (list != list2) << std::endl;

    {
        // let us do a list of integers
        link_list<int> list;
        list.insert_ordered(1);
        list.insert_ordered(2);
        list.insert_ordered(3);
        
        link_list<int> list2;
        list2.insert_ordered(2);
        list2.insert_ordered(1);
        list2.insert_ordered(3);

        list.print();
        list2.print();

        std::cout << std::boolalpha << "are they equal? "    << (list == list2) << std::endl;
        std::cout << std::boolalpha << "are they different? "    << (list != list2) << std::endl;
        
        list2.insert_ordered(-10);

        list.print();
        list2.print();

        std::cout << std::boolalpha << "are they equal? "    << (list == list2) << std::endl;
        std::cout << std::boolalpha << "are they different? "    << (list != list2) << std::endl;

        list = list2;
        list.print();
        list2.print();
        
        std::cout << std::boolalpha << "are they equal? "    << (list == list2) << std::endl;
        std::cout << std::boolalpha << "are they different? "    << (list != list2) << std::endl;

        //empty the first list
        list.clear();
        
        list.print();
        list2.print();
        
        std::cout << std::boolalpha << "are they equal? "    << (list == list2) << std::endl;
        std::cout << std::boolalpha << "are they different? "    << (list != list2) << std::endl;

        //empty the second list
        list2.clear();
        
        list.print();
        list2.print();
        
        std::cout << std::boolalpha << "are they equal? "    << (list == list2) << std::endl;
        std::cout << std::boolalpha << "are they different? "    << (list != list2) << std::endl;


    }

    return 0;
    
}
