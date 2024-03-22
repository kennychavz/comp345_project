//#include "Observable.cpp"
//#include "Part2_Map.cpp"

class MapObserver : public Observer {
public:
    MapObserver(Map& map) : map(map) {}

    void update() {
        // Print the map here
        map.printMap();
    }

void printPastPos() {
        vector<string>& pastPos = map.getPastPositions();
        for (string pos : pastPos) {
            cout << pos << " " << pos << endl;
        }
        cout << endl;
    }

private:
    Map& map;  // Reference to the Map instance
};
