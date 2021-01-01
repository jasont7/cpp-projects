#include <iostream>
#include <vector>

using matrix_type = std::vector<std::vector<int>>;

// draws the spiral pattern inside the provided square matrix
void draw_spiral(matrix_type& matrix) {
    int D {int(matrix.size())};

    int dir {1}; // direction starts at right
    std::vector<int> pos {0,0}; // initial position in matrix

    for (int val=D; val >= 0; val--) {
        std::vector<int> tmpPos = pos;
        if (dir == 1) { // right
            for (int i=0; i < val; i++) { // fill row with val
                matrix.at(tmpPos.at(0)).at(tmpPos.at(1)) = val;
                tmpPos.at(1)++;
            }
            tmpPos.at(1)--;
            tmpPos.at(0)++; // move next position down
            pos = tmpPos;
            dir=2;
        } else if (dir == 2) { // down
            for (int i=0; i < val; i++) { // fill column with val
                matrix.at(tmpPos.at(0)).at(tmpPos.at(1)) = val;
                tmpPos.at(0)++;
            }
            tmpPos.at(0)--;
            tmpPos.at(1)--; // move next position left
            pos = tmpPos;
            dir=3;
        } else if (dir == 3) { // left
            for (int i=0; i < val; i++) { // fill row with val
                matrix.at(tmpPos.at(0)).at(tmpPos.at(1)) = val;
                tmpPos.at(1)--;
            }
            tmpPos.at(1)++;
            tmpPos.at(0)--; // move next position up
            pos = tmpPos;
            dir=4;
        } else { // (4) up
            for (int i=0; i < val; i++) { // fill column with val
                matrix.at(tmpPos.at(0)).at(tmpPos.at(1)) = val;
                tmpPos.at(0)--;
            }
            tmpPos.at(0)++;
            tmpPos.at(1)++; // move next position right
            pos = tmpPos;
            dir=1;
        }
    }
}

// helper function which prints the provided matrix
void print(const matrix_type& matrix) {
    for (auto& row : matrix) {
        for (auto value : row) {
            std::cout << value << ' ';
        }
        std::cout << std::endl;
    }
}

int main(int argc, char** argv) {
    // check that the user provided a command line argument
    if (argc != 2) {
        std::cout << "One integer command line argument must be provided\n";
        return EXIT_FAILURE;
    }

    size_t dimension {0};

    // attempt to convert the command line argument into an integer
    try {
        int test {std::stoi(argv[1])};

        if (test < 0) {
            throw std::invalid_argument("Command line argument was negative");
        }
        dimension = static_cast<int>(test);
    } catch (std::invalid_argument& e) {
        std::cout << "The command line argument must be a positive integer\n";
        return EXIT_FAILURE;
    }

    // create an "empty" square matrix from the dimension
    matrix_type matrix {dimension, std::vector<int>(dimension, 0)};

    // student implements this function
    draw_spiral(matrix);

    print(matrix);

    return EXIT_SUCCESS;
}