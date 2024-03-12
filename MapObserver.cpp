//#include "Observable.cpp"
//#include "Part2_Map.cpp"

class MapObserver : public Observer {
public:
    MapObserver(Map& map) : map(map) {}

    void update() {
        // Print the map here
        map.printMap();
    }

private:
    Map& map;  // Reference to the Map instance
};
