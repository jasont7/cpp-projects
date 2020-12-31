// CSC 116 - Fall 2020
// Jason Thomo (V00949336)

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include <sstream>
#include <limits>

// The first year covered by the dataset
const int kFirstYear = 1920;

// The number of years in the dataset
const int kTotalYears = 100;

struct BabyName_t {
	//Baby name
    std::string name;
		
	//The number of occurrences of the name in each year.
	//After this structure is initialized, element i of yearsCount
	//will contain the number of babies with this name in year i.
	//Note that the year at index i corresponds to the year kFirstYear + i
	//(for example, yearsCount.at(6) will give the count for 1920 + 6 = 1926)
	//For this BabyName_t structure to be valid, the number of elements in yearsCount
	//must equal kTotalYears after the structure is initialized.
    std::vector<unsigned int> yearsCount;
	
	//The total number of occurrences of this name over all years.
    unsigned int total;
};


// Verify that the total matches the counts, and exit if it does not.
// (No need to modify this function)
void Check_Baby(const BabyName_t& baby) {
    unsigned int sum {0};

    if (baby.yearsCount.size() != kTotalYears) {
        std::cout << "There was an error reading baby [" << baby.name << "]. Only " <<  baby.yearsCount.size() << " years were read."  << std::endl;
        exit(1);
    }

    for (unsigned int r: baby.yearsCount) {
        sum+=r;
    }
    if (sum != baby.total) {
        std::cout << "There was an error reading baby [" << baby.name << "]: the sum of yearsCount is inconsistent has [" << baby.total << "] expected [" << sum << "]" << std::endl;
        exit(1);
    }
}

/* Print_Baby( baby )
   Given a reference to a valid BabyName_t structure, print the statistics for the
   corresponding baby name in the format specified in the assignment description.
   (Remember to exactly duplicate all spacing and capitalization)
*/
void Print_Baby(const BabyName_t &baby) {
    unsigned int total {baby.total};
    std::cout << " Total: " << total << std::endl;

    std::vector yearsCount {baby.yearsCount};

    unsigned int years {0};
    for (auto yCount : yearsCount) {
        if (yCount > 0)
            years++;
    }
    std::cout << " Years: " << years << std::endl;

    unsigned int babies2019 {yearsCount.back()};
    std::cout << " 2019: " << babies2019 << std::endl;

    unsigned int firstYear {0};
    unsigned int firstYearCount {0};
    for (size_t i=0; i < yearsCount.size(); i++) {
        if (yearsCount.at(i) > 0) {
            firstYear = kFirstYear + i;
            firstYearCount = yearsCount.at(i);
            break;
        }
    }
    std::cout << " First: " << firstYear << " " << firstYearCount << std::endl;

    unsigned int lastYear {0};
    unsigned int lastYearCount {0};
    for (size_t i=yearsCount.size()-1; i >= 0; i--) {
        if (yearsCount.at(i) > 0) {
            lastYear = kFirstYear + i;
            lastYearCount = yearsCount.at(i);
            break;
        }
    }
    std::cout << " Last: " << lastYear << " " << lastYearCount << std::endl;

    unsigned int minBabies {std::numeric_limits<int>::max()};
    unsigned int minBabiesYear {0};
    for (size_t i=0; i < yearsCount.size(); i++) {
        if (yearsCount.at(i) < minBabies && yearsCount.at(i) >= 1) {
            minBabies = yearsCount.at(i);
            minBabiesYear = kFirstYear + i;
        }
    }
    std::cout << " Min: " << minBabiesYear << " " << minBabies << std::endl;

    unsigned int maxBabies {0};
    unsigned int maxBabiesYear {0};
    for (size_t i=0; i < yearsCount.size(); i++) {
        if (yearsCount.at(i) >= maxBabies) {
            maxBabies = yearsCount.at(i);
            maxBabiesYear = kFirstYear + i;
        }
    }
    std::cout << " Max: " << maxBabiesYear << " " << maxBabies << std::endl;

    double totalCount {0};
    double average {0};
    for (auto yCount : yearsCount) {
        totalCount += yCount;
    }
    average = totalCount/100;
    std::cout << " Avg: " << average << std::endl;
}

/* Find_Baby( name_list, name, output_baby)
   Given a vector name_list containing a sequence of BabyName_t structures and a name to search
   for, determine whether the provided name is in the list.
   If the name is found in name_list, assign the corresponding entry of name_list to the 
   provided structure baby and return true.
   If the name is not found in name_list, return false.
*/
bool Find_Baby(const std::vector<BabyName_t>& name_list, const std::string& name, BabyName_t& output_baby) {
    BabyName_t baby {};
    for (auto bName : name_list) {
        if (bName.name == name) { // names are equal
            output_baby = bName;
            return true;
        }
    }
    return false;
}


/* Read_Babies(inputFileName)
   Each line in inputFileName will be converted into a BabyName_t struct. 
   All lines will be read and return in a vector
*/
std::vector<BabyName_t> Read_Babies(const std::string& inputFileName) {
    std::vector<BabyName_t> babies;
    std::ifstream inputFile {};
    inputFile.open(inputFileName);

    if (inputFile.is_open()) {
        std::string nameLine {};
        while (std::getline(inputFile, nameLine)) {
            std::string name {};
            std::vector<unsigned int> yearsCount {};
            unsigned int total {};

            std::vector<std::string> lineComponents {};
            std::stringstream ss(nameLine);
            while (ss.good()) {
                std::string lineComp {};
                std::getline(ss, lineComp, ',');
                lineComponents.push_back(lineComp);
            }

            name = lineComponents.at(0);
            for (size_t i=1; i < lineComponents.size()-1; i++) {
                yearsCount.push_back(std::stoi(lineComponents.at(i)));
            }
            total = std::stoi(lineComponents.back());

            BabyName_t baby = {name, yearsCount, total};
            babies.push_back(baby);
        }
    } else {
        std::cout << "Unable to open input file." << std::endl;
        exit(1);
    }

    return babies;
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Usage " << argv[0] << " <filename>" << std::endl;
        exit(1);
    }
    std::string inputFileName = argv[1];

    // read the babies
    std::vector<BabyName_t> babies = Read_Babies(inputFileName);
    // verify them
    for (auto &baby: babies) {
        Check_Baby(baby);
    }

    std::cout << "Read " << babies.size() << " babies."<< std::endl;

    std::string name {};
    while (getline(std::cin, name)) {

        std::cout << name << std::endl;

        // search and print the baby, if exists
        BabyName_t baby {};
        if (Find_Baby(babies, name, baby)) {
            Print_Baby(baby);
        } else {
            std::cout << "Baby name [" << name << "] was not found" << std::endl;
        
        }
    }

    return 0;
}
