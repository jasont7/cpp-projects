#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

#include "recover-photos.hpp"

// use this function to convert the length of the record (2 bytes!)
int big_endian_2_bytes_to_int(const std::string &value);


std::string Process_Photo(const std::string &buf, long int currentOffset) {
    std::string photo {};
    long int offset {currentOffset};

    // skip records until finding the record 0xFF 0xDA (Start of Scan)
    while (offset < int(buf.size())) {
        if (buf.substr(offset, 2) == "\xFF\xDA") {
            int len {big_endian_2_bytes_to_int(buf.substr(offset+2, 2))};
            offset += 2+len;
            break;
        }

        if (buf.substr(offset+2, 1) == "\xFF") { // record with no length
            offset += 2;
        } else {
            int len {big_endian_2_bytes_to_int(buf.substr(offset+2, 2))};
            offset += 2+len;
        }
    }

    // skip image data until reaching the End-of-Image record
    while (offset < int(buf.size())) {
        if (buf.substr(offset, 2) == "\xFF\xD9")
            break;
        offset++;
    }

    // offset now contains the end of the photo; compute its length and store data
    if (buf.substr(offset, 2) == "\xFF\xD9") {
        offset += 2;
        long int photoLength = offset - currentOffset;
        photo = buf.substr(currentOffset, photoLength);
    }

    return photo;
}

std::stringstream Output_Photo(const std::string &photo, long int currentOffset) {
    std::stringstream output {};
    long int offset {0};

    // skip records until finding the record 0xFF 0xDA (Start of Scan)
    while (offset < int(photo.size())) {
        if (photo.substr(offset, 2) == "\xFF\xDA") {
            int len {big_endian_2_bytes_to_int(photo.substr(offset+2, 2))};
            output << "Record " << std::hex << big_endian_2_bytes_to_int(photo.substr(offset, 2))
                   << " of length " << std::setw(8) << std::dec << std::right << len << " at offset "
                   << std::setw(8) << std::right << (currentOffset + offset) << std::endl;
            offset += 2+len;
            break;
        }

        if (photo.substr(offset+2, 1) == "\xFF") { // record with no length
            output << "Record " << std::hex << big_endian_2_bytes_to_int(photo.substr(offset, 2))
                   << " of length " << std::setw(8) << std::dec << std::right << 0 << " at offset "
                   << std::setw(8) << std::right << (currentOffset + offset) << std::endl;
            offset += 2;
        } else {
            int len {big_endian_2_bytes_to_int(photo.substr(offset+2, 2))};
            output << "Record " << std::hex << big_endian_2_bytes_to_int(photo.substr(offset, 2))
                   << " of length " << std::setw(8) << std::dec << std::right << len << " at offset "
                   << std::setw(8) << std::right << (currentOffset + offset) << std::endl;
            offset += 2+len;
        }
    }

    output << "Data starts at byte offset " << (currentOffset + offset) << std::endl;

    // skip image data until reaching the End-of-Image record
    while (offset < int(photo.size())) {
        if (photo.substr(offset, 2) == "\xFF\xD9")
            break;
        offset++;
    }
    output << "Record ffd9 of length " << std::setw(8) << 0 << " at offset "
           << std::setw(8) << (currentOffset + offset) << std::endl;
    offset += 2;
    output << "File contains " << offset << " bytes";

    return output;
}

void Create_Photo(const std::string &photo, int number) {
    std::stringstream fileName {};
    fileName << "recovered-" << std::setw(4) << std::setfill('0') << number << ".jpg";
    std::ofstream file(fileName.str(), std::ios::binary);
    file << photo;
    std::cout << "Recovering file: " << fileName.str() << std::endl;
}

int Recover_Photos(std::string filename, bool recover) {
    int count {0};
    std::ifstream input(filename);

    input.seekg(0, input.end); // go to end of file
    std::streamoff fileSize {input.tellg()};
    input.seekg(0, input.beg); // move to beginning again to read

    std::string buf {};
    buf.resize(fileSize);
    input.read(&buf[0], buf.size());

    int block {512};
    long int currentOffset {0};
    while (currentOffset < int(buf.size())) {
        int start {big_endian_2_bytes_to_int(buf.substr(currentOffset, 2))};
        if (start == 0xFFD8) {
            std::string photo {Process_Photo(buf, currentOffset)};

            if (!photo.empty()) {
                std::stringstream photoOutput {Output_Photo(photo, currentOffset)};
                std::cout << photoOutput.str() << std::endl;

                if (recover)
                    Create_Photo(photo, count);

                count++;
            }
            int blocksOccupied {(int(photo.size()) / block) + 1};
            currentOffset += blocksOccupied * block;
        } else
            currentOffset += block;
    }

    return count;
}