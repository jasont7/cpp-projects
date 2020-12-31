#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <iomanip>
#include <complex>
#include <vector>
#include <utility>


#include "list.hpp"


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

    // now, let us make a list with the first character of each country

    std::function<char(std::string&)> first_char = [](std::string &st) {
        if (st.length() > 0) {
            return st.at(0);
        } else {
            return char(0);
        }
    };

    link_list<char> firstChar = list.map(first_char);
    firstChar.print();

    // map their length

    std::function<int(std::string&)> f_len = [](std::string &st) {
        return st.length();
    };
    auto len = list.map(f_len);
    len.print();
    // let us map empty list too
    link_list<std::string> empty {};
    auto len2 = empty.map(f_len);
    len2.print();

    {
        
        // let us create an imaginary number from the capitals
        // ordinal of first character (starting in A) is the imaginary part, the length is the real part
        
        std::cout << "List of Complex numbers" << std::endl;
        
        std::function<std::complex<double>(std::string&)> st_to_complex = [](std::string &st) {
            if (st.length() > 0) {
                return std::complex<double>(st.length(), int(st.at(0)-'A'));
            } else {
                return std::complex<double>(st.length(),0);
            }
        };
        
        auto l_complex = list.map(st_to_complex);
        
        // we need to do use do to print it
        
        l_complex.print();

        // let us convert them into polar coordinates, using a pair

        std::function<std::pair<double,double>(std::complex<double>&)> complex_to_polar = [](std::complex<double> &c) {
            return std::pair<double,double>(std::abs(c), std::arg(c));
        };
        
        auto l_polar = l_complex.map(complex_to_polar);

        // we need to use a lambda to print it
        std::cout << "In polar coordinates " << std::endl;
      
        int index {0};
        std::function<void(std::pair<double,double>)> p_pair = [&index](std::pair<double,double> p) {
            if (index++ != 0) {
                std::cout << " -> ";
            }
            std::cout << "(" << p.first << "," << p.second << ")";
        };
//        std::cout << std::fixed << std::setprecision(3);
        l_polar.apply(p_pair);
		std::cout << std::endl;

    }
    return 0;
}
