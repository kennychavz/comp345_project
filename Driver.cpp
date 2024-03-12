
#include <iostream>
#include "Part2_Map.cpp"  // Include Map class header file
#include "MapObserver.cpp"  // Include MapObserver class header file

int main() {
    // Create a Map instance
    Map myMap(10, 10);

    // Create a MapObserver instance and pass the Map reference to it
    MapObserver observer(myMap);

    // Add the observer to the map
    myMap.addObserver(&observer);

    // Start the game (which will trigger updates)
    myMap.startGame();

    return 0;
}
