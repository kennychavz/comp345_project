#include <iostream>
#include <fstream>
#include <vector>
#include <string>
// #include "Part2_Map.cpp"

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
    virtual void setMatrix(vector<vector<int> >& matrix) = 0;
    virtual void setWidth(int width) = 0;
    virtual void setHeight(int height) = 0;
    virtual Map build() const = 0;
};

// Concrete builder for reading the map as saved
class MapBuilder : public Builder {
protected:
    vector<vector<int> > map;
    int width;
    int height;

public:

    MapBuilder(int width, int height) : width(width), height(height) {}

    void setMatrix(vector<vector<int> >& matrix) override {
        map = matrix;
    }

    void setWidth(int width) override {
        this->width = width;
    }

    void setHeight(int height) override {
        this->height = height;
    }

    Map build() const override {
        Map map(height, width);
        return map;
    }
};

// Director class
class MapDirector {
private:
    MapBuilder* builder;

public:
    void setBuilder(MapBuilder* builder) {
        this->builder = builder;
    }

    // Reads a map
    static vector<vector<int> > readMapFromFile(const string& filename) {
    ifstream file(filename);
    vector<vector<int> > map;
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
        vector<int> row;
        for (char c : line) {
            //cout << c << endl;
            int value = c - '0';
            //cout << value << endl;
            // cout << c << endl;
            // switch(c) {
            //     case '':
            //         value = 1;
            //         break;
            //     case 'x':
            //         value = 2;
            //         break;
            //     case '|':
            //         value = 3;
            //         break;
            //     default:
            //         break;
            // }
            row.push_back(value);

        }
        // string choice;
        //cout<< map[0][0] << endl;
        // cin>> choice;
        map.push_back(row);

        }
        //map.push_back(row);
    }
    file.close();

    return map;

}
    // Save a map to file
   static void saveMap(Map map, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {

        for (int j = 0; j < map.getHeight(); ++j) {
            for (int i = 0; i < map.getWidth(); ++i) {

                file << map.getElement(j, i);
            }
            file << endl;
        }
        file.close();

    } else {
        cout << "Unable to open file." << endl;
    }
}


    // Map getMap() const {
    //     return builder->build();
    // }

};

class LevelBuilder : public MapBuilder {
private:
    int level;

public:
    LevelBuilder(int width, int height, int level) : MapBuilder(width, height), level(level) {}

    // Override the build method to adapt map contents and items to the specific level
    // Map build() {
    //     Map map = Builder::build(); // Build the base map using parent's build method

    //     // Adapt map contents based on the level
    //     adaptMapToLevel(map);

    //     return map;
    // }
    // void adaptMapToLevel(Map& map) {
    //     switch (level) {
    //         // level 1, replace all 'x' with '.'
    //         case 1:
    //             for (int j = 0; j < map.getHeight(); ++j) {
    //                 for (int i = 0; i < map.getWidth(); ++i) {
    //                     if (map.getElement(j, i == 1)) {
    //                         map.setCell(j, i, 2);
    //                     }
    //                 }
    //             }
    //             break;
    //          // level 2, replace all '.' with 'x'
    //         case 2:
    //            for (int j = 0; j < map.getHeight(); j += 2) {
    //                 for (int i = 0; i < map.getWidth(); ++i) {
    //                     if (map.getElement(j, i == 1)) {
    //                         map.setCell(j, i, 2);
    //                     }
    //                 }
    //             }
    //             break;
    //         //
    //         case 3:
    //            for (int j = 0; j < map.getHeight(); j += 4) {
    //                 for (int i = 0; i < map.getWidth(); ++i) {
    //                     if (map.getElement(j, i == 1)) {
    //                         map.setCell(j, i, 2);
    //                     }
    //                 }
    //             }
    //             break;

    //         default:
    //             break;
    //     }

    //}
};

// int main() {

//     Map map = Map(20, 20);
//     MapDirector mapDirector = MapDirector();
//     mapDirector.saveMap(map, "America.txt");
//     map.printMap();

//     MapBuilder mapBuilder(20, 20);
//     LevelBuilder levelBuilder(20, 20, 1);
//     mapDirector.setBuilder(&mapBuilder);
//     //mapDirector.setBuilder(&levelBuilder);

//     // Read map from file
//     vector<vector<int> > mapData = mapDirector.readMapFromFile("America.txt");

//     //cout << 4 << endl;

//     // Construct map using director
//     Map mapLoaded = mapDirector.constructMap(mapData);
      //Map mapLoaded = Map(mapData, "America.txt");
//     mapLoaded.printMap();
//     levelBuilder.adaptMapToLevel(mapLoaded);
//     mapLoaded.printMap();
//     //cout << 5 << endl;

//     // // Get map from builder
//     // Map mapBuilder = mapBuilder.build();
//     // cout << 6 << endl;
//     // cout << "Map read from file and constructed:" << endl;
//     // mapBuilder.printMap();

//     // // Save map to file
//     // mapDirector.saveMap(mapBuilder, "saved_map.txt");
//     // cout << "Map saved to file 'saved_map.txt'." << endl;

//     return 0;
// }
