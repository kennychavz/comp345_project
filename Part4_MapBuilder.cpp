#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Part2_Map.cpp"


using namespace std;

class Builder {
    private:
        int width, height;
        string filename;

    public:

        // Builder constructor 
        Builder(int width, int height) : width(width), height(height) {}

        Builder& setFilename(const string& filename) {
            this->filename = filename;
            return *this;
        }
        
        // maps CellType to correcponding char
        char cellToChar(CellType type) {
            switch (type) {
                case CellType::Occupied:
                    return 'x';
                case CellType::Empty:
                    return '.';
                case CellType::Wall:
                    return '|';
                default:
                    return ' ';
            }
        }

//        Map build() {
//     Map map(width, height);
//     if (!filename.empty()) {
//         ifstream infile(filename); // Read file

//         if (!infile.is_open()) {
//             cout << "Unable to open file: " << filename << endl;
//             return map; // Return map with default (empty) contents
//         }

//         string line;
//         int row = 0;
//         while (getline(infile, line) && row < height) {
//             for (int col = 0; col < width && col < line.length(); ++col) {
//                 char cellChar = line[col];

//                 // Skip over spaces
//                 if (cellChar == ' ') {
//                     continue;
//                 }

//                 // Put the character in the middle
//                 if (col == width / 2 && row == height / 2) {
//                     map.setCell(col, row, 'o');
//                     cout << 'o';
//                 } else {
//                     CellType cellType;
//                     switch (cellChar) {
//                         case '.':
//                             cellType = CellType::Empty;
//                             cout << '.';
//                             break;
//                         case 'x':
//                             cellType = CellType::Wall;
//                             cout << 'x';
//                             break;
//                         case '|':
//                             cellType = CellType::Occupied;
//                             cout << '|';
//                             break;
//                         default:
//                             cellType = CellType::Empty;
//                             cout << '.';
//                             break;
//                     }
//                     // Map to cell grid
//                     map.setCell(col, row, cellToChar(cellType));
//                 }
//             }
//             cout << endl; // Print newline after each row
//             ++row;
//         }

//         infile.close();
//     }

//     return map;
// }


        Map build() {
            Map map(width, height);
            if (!filename.empty()) {
                ifstream infile(filename); //read file

                if (!infile.is_open()) {
                    cout << "Unable to open file: " << filename << endl;
                    return map; // Return map with default (empty) contents
                }

                string line;
                int row = 0;
                while (getline(infile, line) && row < height) { 
                    for (int col = 0; col < width && col < line.length(); ++col) {
                        
                        char cellChar = line[col];
                        cout << "Reading character: " << cellChar << endl;
                        CellType cellType;

                        //puts the character in the middle
                        if (col == width / 2 && row == height / 2) {
                            map.setCell(col, row, 'o');
                            cout << setw(3) << setfill(' ') << "o";
                        }

                        //check each char for the cell type
                        else 
                        {
                            switch (cellChar) {
                                case '.':
                                    cellType = CellType::Empty;
                                    //std::cout << std::setw(3) << std::setfill(' ') << ".";
                                    break;
                                case 'x':
                                    cellType = CellType::Wall;
                                    std::cout << std::setw(3) << std::setfill(' ') << "x";
                                    break;
                                case '|':
                                    cellType = CellType::Occupied;
                                    std::cout << std::setw(3) << std::setfill(' ') << "|";
                                    break;
                                default:
                                    cellType = CellType::Empty;
                                    cout << setw(3) << setfill(' ') << ".";
                                    break;
                            }
                            //maps to cell grid 
                            map.setCell(col, row, cellToChar(cellType));
                        }

                    }

                    row++;
                }

                infile.close();
            }
           
            return map;
        }

    
    };


 
int main() {

    Builder builder(10, 10); // Create a builder with width 10 and height 10
    builder.setFilename("MapFile.txt"); // Set the filename if you have a file to load the map from

    // Build the map
    Map map = builder.build();
    

    // Print the map
    map.printMap();
    //map.startGame();

    return 0;
}
