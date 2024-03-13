
#include <iostream>
#include "Part2_Map.cpp"  // Include Map class file
#include "MapObserver.cpp"  // Include MapObserver class file
#include "Part4_MapBuilder.cpp"
#include "A2_Part3_CampaignEditor.cpp"
#include "Part1_Character.cpp"

int main() {

    // Create a level builder with width 10, height 10, and level 1
    LevelBuilder builder(10, 10, 1);

    // load map from map builder
    Map map = builder.build();

    // Create a MapObserver instance and pass the Map reference to it
    MapObserver observer(map);

    // Add the observer to the map
    myMap.addObserver(&observer);

    // Start the game (which will trigger updates)
    myMap.startGame();


    return 0;
}
