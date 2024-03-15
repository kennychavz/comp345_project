#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Part2_Map.cpp"

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;
using std::cin;

// Abstract builder interface
class Builder {
public:
    virtual void setMatrix(vector<vector<int>>& matrix) = 0;
    virtual void setWidth(int width) = 0;
    virtual void setHeight(int height) = 0;
    virtual Map build() const = 0;
};

// Concrete builder for reading the map as saved
class MapBuilder : public Builder {
protected:
    vector<vector<int>> map;
    int width;
    int height;

public:

    MapBuilder(int width, int height) : width(width), height(height) {}

    void setMatrix(vector<vector<int>>& matrix) override {
        map = matrix;
    }

    void setWidth(int width) override {
        this->width = width;
    }

    void setHeight(int height) override {
        this->height = height;
    }

    Map build() const override {

        return map;
    }
    //     string result;
    //     for (const auto& row : map) {
    //         for (int cell : row) {
    //             result += std::to_string(cell) + " ";
    //         }
    //         result += "\n";
    //     }
    //     return result;
};

// Director class
class MapDirector {
private:
    MapBuilder* builder;

public:
    void setBuilder(MapBuilder* builder) {
        this->builder = builder;
    }

    vector<vector<int>> readMapFromFile(const string& filename) {
    ifstream file(filename);
    vector<vector<int>> map;
    string line;
    while (getline(file, line)) {
        vector<int> row;
        string number;
        for (char c : line) {
            int value;
            switch(c) {
                case '.':
                    value = 1;
                    break;
                case 'x':
                    value = 2;
                    break;
                case '|':
                    value = 3;
                    break;
                default:
                    break;
            }
            row.push_back(value);
        }
        map.push_back(row);
    }
    return map;

}

   void saveMap(Map map, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {

        for (int i = 0; i < map.getHeight(); i++) {
            for (int j = 0; j < map.getWidth(); j++) { 

                file << map.getElement(i, j);
            }
            file << endl;
        }
        file.close(); 

    } else {
        cout << "Unable to open file." << endl;
    }
}

    void constructMap(vector<vector<int>> matrix) {
        int width = matrix[0].size();
        int height = matrix.size();

        builder->setWidth(width);
        builder->setHeight(height);
        builder->setMatrix(matrix);
    }

    Map getMap() const {
        
        return builder->build();
    }

};

class LevelBuilder : public MapBuilder {
private:
    int level;

public:
    LevelBuilder(int width, int height, int level) : MapBuilder(width, height), level(level) {}

    // Override the build method to adapt map contents and items to the specific level
    Map build() {
        Map map = Builder::build(); // Build the base map using parent's build method

        // Adapt map contents based on the level
        adaptMapToLevel(map);

        return map;
    }

private:
    void adaptMapToLevel(Map& map) {
        switch (level) {
            // level 1, replace all 'x' with '.'
            case 1:
                for (int row = 0; row < height; ++row) {
                    for (int col = 0; col < width; ++col) {
                        if (map.getElement(col, row) == 2) {
                            map.setCell(col, row, 1);
                        }
                    }
                }
                break;
             // level 2, replace all '.' with 'x'
            case 2:
               for (int row = 0; row < height; ++row) {
                    for (int col = 0; col < width; ++col) {
                        if (map.getElement(col, row) == 1) {
                            map.setCell(col, row, 2);
                        }
                    }
                }
                break;
            default:
                break;
        }

    }
};

int main() { 

    MapBuilder mapBuilder(5, 5);
    LevelBuilder levelBuilder(3, 3, 1);
    MapDirector mapDirector;
    mapDirector.setBuilder(&mapBuilder);
    //mapDirector.setBuilder(&levelBuilder);

    // Read map from file
    std::vector<std::vector<int>> mapData = mapDirector.readMapFromFile("Asia.txt");

    // Construct map using director
    mapDirector.constructMap(mapData);

    // Get map from builder
    Map mapLoaded = mapDirector.getMap();
    cout << "Map read from file and constructed:" << endl;
    mapLoaded.printMap();

    // Save map to file
    mapDirector.saveMap(mapLoaded, "saved_map.txt");
    cout << "Map saved to file 'saved_map.txt'." << endl;

    return 0;
}


// class Builder {
//     private:
//         int width, height;
//         string filename;

//     public:

//         // Builder constructor 
//         Builder(int width, int height) : width(width), height(height) {}

//         Builder& setFilename(const string& filename) {
//             this->filename = filename;
//             return *this;
//         }
        
//         // maps CellType to correcponding char
//         char cellToChar(CellType type) {
//             switch (type) {
//                 case CellType::Occupied:
//                     return 'x';
//                 case CellType::Empty:
//                     return '.';
//                 case CellType::Wall:
//                     return '|';
//                 default:
//                     return ' ';
//             }
//         }

// //        Map build() {
// //     Map map(width, height);
// //     if (!filename.empty()) {
// //         ifstream infile(filename); // Read file

// //         if (!infile.is_open()) {
// //             cout << "Unable to open file: " << filename << endl;
// //             return map; // Return map with default (empty) contents
// //         }

// //         string line;
// //         int row = 0;
// //         while (getline(infile, line) && row < height) {
// //             for (int col = 0; col < width && col < line.length(); ++col) {
// //                 char cellChar = line[col];

// //                 // Skip over spaces
// //                 if (cellChar == ' ') {
// //                     continue;
// //                 }

// //                 // Put the character in the middle
// //                 if (col == width / 2 && row == height / 2) {
// //                     map.setCell(col, row, 'o');
// //                     cout << 'o';
// //                 } else {
// //                     CellType cellType;
// //                     switch (cellChar) {
// //                         case '.':
// //                             cellType = CellType::Empty;
// //                             cout << '.';
// //                             break;
// //                         case 'x':
// //                             cellType = CellType::Wall;
// //                             cout << 'x';
// //                             break;
// //                         case '|':
// //                             cellType = CellType::Occupied;
// //                             cout << '|';
// //                             break;
// //                         default:
// //                             cellType = CellType::Empty;
// //                             cout << '.';
// //                             break;
// //                     }
// //                     // Map to cell grid
// //                     map.setCell(col, row, cellToChar(cellType));
// //                 }
// //             }
// //             cout << endl; // Print newline after each row
// //             ++row;
// //         }

// //         infile.close();
// //     }

// //     return map;
// // }


//         Map build() {
//             Map map(width, height);
//             if (!filename.empty()) {
//                 ifstream infile(filename); //read file

//                 if (!infile.is_open()) {
//                     cout << "Unable to open file: " << filename << endl;
//                     return map; // Return map with default (empty) contents
//                 }

//                 string line;
//                 int row = 0;
//                 while (getline(infile, line) && row < height) { 
//                     for (int col = 0; col < width && col < line.length(); ++col) {
                        
//                         char cellChar = line[col];
//                         cout << "Reading character: " << cellChar << endl;
//                         CellType cellType;

//                         //puts the character in the middle
//                         if (col == width / 2 && row == height / 2) {
//                             map.setCell(col, row, 'o');
//                             cout << setw(3) << setfill(' ') << "o";
//                         }

//                         //check each char for the cell type
//                         else 
//                         {
//                             switch (cellChar) {
//                                 case '.':
//                                     cellType = CellType::Empty;
//                                     //std::cout << std::setw(3) << std::setfill(' ') << ".";
//                                     break;
//                                 case 'x':
//                                     cellType = CellType::Wall;
//                                     std::cout << std::setw(3) << std::setfill(' ') << "x";
//                                     break;
//                                 case '|':
//                                     cellType = CellType::Occupied;
//                                     std::cout << std::setw(3) << std::setfill(' ') << "|";
//                                     break;
//                                 default:
//                                     cellType = CellType::Empty;
//                                     cout << setw(3) << setfill(' ') << ".";
//                                     break;
//                             }
//                             //maps to cell grid 
//                             map.setCell(col, row, cellToChar(cellType));
//                         }

//                     }

//                     row++;
//                 }

//                 infile.close();
//             }
           
//             return map;
//         }

    
//     };

// class LevelBuilder : public Builder {
// private:
//     int level;

// public:
//     LevelBuilder(int width, int height, int level) : Builder(width, height), level(level) {}

//     // Override the build method to adapt map contents and items to the specific level
//     Map build() override {
//         Map map = Builder::build(); // Build the base map using parent's build method

//         // Adapt map contents based on the level
//         adaptMapToLevel(map);

//         return map;
//     }

// private:
//     void adaptMapToLevel(Map& map) {
//         switch (level) {
//             case 1:
//                 // Example: If level 1, replace all 'x' with '.'
//                 for (int row = 0; row < map.getHeight(); ++row) {
//                     for (int col = 0; col < map.getWidth(); ++col) {
//                         if (map.getCell(col, row) == 'x') {
//                             map.setCell(col, row, '.');
//                         }
//                     }
//                 }
//                 break;
//             case 2:
//                 // Example: If level 2, replace all '.' with 'x'
//                 for (int row = 0; row < map.getHeight(); ++row) {
//                     for (int col = 0; col < map.getWidth(); ++col) {
//                         if (map.getCell(col, row) == '.') {
//                             map.setCell(col, row, 'x');
//                         }
//                     }
//                 }
//                 break;
//             default:
//                 break;
//         }

//     }
// };

// // int main() {

// //     Builder builder(10, 10); // Create a builder with width 10 and height 10
// //     builder.setFilename("MapFile.txt"); // Set the filename if you have a file to load the map from

// //     LevelBuilder builder(10, 10, 1); // Create a level builder with width 10, height 10, and level 1
// //     builder.setFilename("MapFile.txt"); // Set the filename if you have a file to load the map from


// //     // Build the map
// //     Map map = builder.build();
    

// //     // Print the map
// //     map.printMap();
// //     //map.startGame();

// //     return 0;
// // }
