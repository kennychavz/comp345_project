#include <vector>
#include <iostream>
#include <random>
#include <iomanip>
#include <vector>

#include "Observable.cpp"


using std::cout;
using std::endl;
using std::vector;

enum class CellType {
     Empty,
     Wall,
     Occupied // This can be further detailed for characters, opponents, chests, etc.
 };


class Map : public Observable {

  private:

    // map dimensions
    int width, height;
    vector<vector<int> > map;
    int currentPosX;
    int currentPosY;

    // observable
    std::vector<Observer*> observers;



  public:
    Map(int width, int height) : width(width), height(height), map(vector<vector<int> >(height, vector<int>(width))) {
        makeMap(width, height);
    }
    // Constructor that takes a 2D matrix as argument
    Map(const vector<vector<int>>& matrix) {
        map = matrix;
        width = matrix[0].size();
        height = matrix.size();

        // Find the initial position of the character
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                if (map[y][x] == 1) {
                    currentPosX = x;
                    currentPosY = y;
                    return;
                }
            }
        }
    }

    // getter methods
    int getHeight() {
      return map.size();
    }
    // getter methods
    int getWidth() {
      return map[0].size();
    }
    int getElement(int x, int y) {
      return map[x][y];
    }

    // ~~~~~~~~~~~~~~~~~~~ Observable ~~~~~~~~~~~~~~~~~~~~~
    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer) {
        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it != observers.end()) {
            observers.erase(it);
        }
    }
    void notifyObservers() {
        for (Observer* observer : observers) {
            observer->update();
        }
    }
    void updateMap() {
      cout << "inside of update"<<endl;
      cout << "new posX" << currentPosX<<endl;
      cout << "new posY" << currentPosY<<endl;
        // Update map logic goes here...

        // After updating, notify all observers
        notifyObservers();
    }
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



    // ~~~~~~~~~~~~~~~~~~~ MAP CREATION ~~~~~~~~~~~~~~~~~~~~~
    void makeMap(int x, int y) {
      // fill with 0
      // Create a 2D vector filled with walls
      std::vector<std::vector<int> > arr(y, std::vector<int>(x, 2));

      //printMap(arr);

      // Set begin variables and set initial position to 1
      int beginX = x/2;
      int beginY = y/2;
      int dynamicX = beginX;
      int dynamicY = beginY;
      arr[beginX][beginY] = 1;

      // set player position to beggining
      currentPosX = beginX;
      currentPosY = beginY;

      //printMap(arr);

      // MAKE A PATH TO OUTSIDE THE MAP
      while (getRandomStep(arr, dynamicX, dynamicY)) {
      }
      dynamicX = x/2;
      dynamicY = y/2;
      while (getRandomStep(arr, dynamicX, dynamicY)) {
      }
      // dynamicX = x/2;
      // dynamicY = y/2;
      // while (getRandomStep(arr, dynamicX, dynamicY)) {
      // }

      // load some chests, doors etc
      loadOccupiedCell(arr);

      //printMap(arr);

      // // check if path exists
      // if (isValidPathExists(arr, beginX, beginY)) {
      //     std::cout << "There is a path to the outside." << std::endl;
      //   } else {
      //     std::cout << "No path to the outside." << std::endl;
      //   }
      map = arr;
      }

    // add chests, doors, etc
    void loadOccupiedCell(vector<vector<int> > &arr) {
      int numNeighbours = 0;
      for (int i = 1; i<arr.size() - 1; i++) {
        for (int j = 1; j<arr[i].size() - 1; j++) {
          // check for exactly 3 neighbours
          if (arr[i+1][j] == 2)
            numNeighbours++;
          if (arr[i-1][j] == 2)
            numNeighbours++;
          if (arr[i][j+1] == 2)
            numNeighbours++;
          if (arr[i][j-1] == 2)
            numNeighbours++;

          if (numNeighbours == 3) {

            // replace last 0 with a 3 instead
            if (arr[i+1][j] == 2)
              arr[i+1][j] = 3;

            if (arr[i-1][j] == 2)
              arr[i-1][j] = 3;

            if (arr[i][j+1] == 2)
              arr[i][j+1] = 3;

            if (arr[i][j-1] == 2)
              arr[i][j-1] = 3;

          }
          numNeighbours = 0;
        }
      }
    }

    bool isValid(int x, int y, int width, int height) {
    return x >= 0 && y >= 0 && x < width && y < height;
    }

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // ~~~~~~~~~~~~~~~~Map Changes~~~~~~~~~~~~~~~~~~

    // Function to move the character on the map
    void moveCharacter(int dx, int dy) {

        // Example: Move the character position
        int newX = currentPosX + dx;
        int newY = currentPosY + dy;

        // printPos();
        // cout << "new x " << newX << endl;;
        // cout << "new y " << newY << endl;;

        // Check if the new position is valid before updating
        if (isValid(newX, newY, width, height) && isOpenPosition(newX, newY)) {
          cout << "its valid" << endl;
            currentPosX = newX;
            currentPosY = newY;
        }
        else {
          cout << "YOU CAN'T MOVE THERE"<<endl;
        }
    }

    /*
    ~~~~~~~~~~~~~~~~ UTIL METHODS ~~~~~~~~~~~~~~~~~~
    */
    bool isValidPathExists(std::vector<std::vector<int> >& map, int x, int y) {
      int width = map[0].size();
      int height = map.size();

      // Check if out of bounds (means we reached the edge)
      if (!isValid(x, y, width, height)) return true;

      // If not "2", not part of the path
      if (map[y][x] != 1) return false;

      // Mark as visited to avoid infinite loops
      map[y][x] = -1; // Temporary mark as visited

      // Explore all 4 directions
      bool up = isValidPathExists(map, x, y - 1);
      bool down = isValidPathExists(map, x, y + 1);
      bool left = isValidPathExists(map, x - 1, y);
      bool right = isValidPathExists(map, x + 1, y);

      // Reset to "2" after exploring (if you need to keep the map intact)
      map[y][x] = 1;
      return up || down || left || right;
    }

    bool indexExists(vector<vector<int> >& vec, int x, int y) {
      // Check if the x index is within bounds
      if (x >= 0 && x < vec.size()) {
          // Check if the y index is within bounds for the specific x
          if (y >= 0 && y < vec[x].size()) {
              return true; // The index exists
          }
      }
      return false; // The index does not exist
    }
    bool getRandomStep(vector<vector<int> >& vec, int &x, int &y) {
      // Random number generator
      std::random_device rd;  // Obtain a random number from hardware
      std::mt19937 gen(rd()); // Seed the generator
      std::uniform_int_distribution<> distr(0, 3); // Define the range
      switch (distr(gen)) {
        case 0:
            //cout << "You chose option 0." << endl;
            x -= 1;
            break;
        case 1:
            //cout << "You chose option 1." << endl;
            x += 1;
            break;
        case 2:
            //cout << "You chose option 2." << endl;
            y -= 1;
            break;
        case 3:
            //cout << "You chose option 3." << endl;
            y += 1;
            break;
        }
        // check if step exists
        if (indexExists(vec, x, y)) {
          vec[x][y] = 1;
          return true;
        }
        else {
          return false;
        }
    }

    const vector<vector<int> > getMap() const {
      return map;
    }

    bool isOpenPosition(int newX, int newY) {
      return (map[newX][newY] == 1 || map[newX][newY] == 3);
    }
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



    // ~~~~~~~~~~~~~~~~~~~ OUTPUT ~~~~~~~~~~~~~~~~~~~~
    void printPos() {
      cout << "current x " << currentPosX << endl;;
      cout << "current y " << currentPosY << endl;;
    }
    void printMap() {
      printPos();
      for (size_t j = 0; j < map.size(); ++j) {
          for (size_t i = 0; i < map[j].size(); ++i) {
              if (i == currentPosX && j == currentPosY) {
                  std::cout << std::setw(3) << std::setfill(' ') << "o";
              } else if (map[i][j] == 1) {
                std::cout << std::setw(3) << std::setfill(' ') << ".";
              } else if (map[i][j] == 2) {
                std::cout << std::setw(3) << std::setfill(' ') << "x";
              } else if (map[i][j] == 3) {
                std::cout << std::setw(3) << std::setfill(' ') << "|";
              }
          }
        std::cout << std::endl;
      }
    }
};

// int main() {

//     // make a 10x10 map
//     cout << "\nmaking a 5x5 map" <<endl;
//     Map myMap(10, 10); // Creating a map, and checking validity
//     myMap.printMap(); // printing map

//     // // make a 15x15 map
//     // cout << "\nmaking a 15x15 map" <<endl;
//     // Map myMap2(15, 15); // Creating a map, and checking validity
//     // myMap2.printMap(); // printing map

//     // // make a 15x10 map
//     // cout << "\nmaking a 15x15 map" <<endl;
//     // Map myMap3(20, 20); // Creating a map, and checking validity
//     // myMap3.printMap(); // printing map

//     // // make a 15x10 map
//     // cout << "\nmaking a 15x15 map" <<endl;
//     // Map myMap4(30, 30); // Creating a map, and checking validity
//     // myMap4.printMap(); // printing map

//     myMap.startGame();

//     return 0;
// }
