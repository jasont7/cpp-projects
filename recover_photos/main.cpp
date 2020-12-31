#include <iostream>
#include <cassert>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>

#include "recover-photos.hpp"

int big_endian_2_bytes_to_int(const std::string& value) {
    if (value.length() != 2) {
        throw std::runtime_error("Convert_Number_2_bytes should be called with strings of length 2");
    }
    assert(value.length() == 2);
    unsigned char *temp = (unsigned char*)(&value[0]);

    return (temp[0] << 8) + (temp[1]);
}

int main(int argc, char *argv[]) {
    if (argc != 3 || !(argv[2] == std::string{"recover"} || argv[2] == std::string{"scan"})){
        std::cout << "Usage " << argv[0] << " <filename> (recover|scan))\n";
        exit(1);
    }
    bool recover = false;
    recover = argv[2] == std::string{"recover"};

    std::cerr << "Reading from file " << argv[1] << std::endl;

    int recovered = Recover_Photos(argv[1], recover);

    std::cout << "Processed " << recovered << " photo(s)." << std::endl;

    return 0;
}