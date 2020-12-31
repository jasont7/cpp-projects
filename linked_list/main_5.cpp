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
    // test list of lists

    link_list<int> list1;
    link_list<int> list2;

    list1.push_front(1);
    list1.push_back(2);
    list1.push_back(3);

    list2.push_front(10);
    list2.push_back(20);
    list2.push_back(30);

    link_list<link_list<int>> listoflist;

    listoflist.push_front(list1);
    listoflist.push_back(list2);

    // see if apply works

    std::function<void(link_list<int>&)> fprint = [](link_list<int> &l) -> void {
        std::cout << "sublist: " ;
        l.print();
        return;
    };

    listoflist.apply(fprint);

    //let us also try it in am empty list
    listoflist.clear();
    listoflist.apply(fprint);

    //oh, I think i forgot to check if a list is emtpy

    std::cout << std::boolalpha << "is list empty? "    << listoflist.empty() << std::endl;

    listoflist.push_front(list1);
    std::cout << std::boolalpha << "is list empty? "    << listoflist.empty() << std::endl;

}
