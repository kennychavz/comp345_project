
#include <iostream>
#include "Part2_Map.cpp"  // Include Map class file
#include "MapObserver.cpp"  // Include MapObserver class file
//#include "Part4_MapBuilder.cpp"
#include "A2_Part3_CampaignEditor.cpp"
#include "Part1_Character.cpp"

// ~~~~~~~~~~~~~~~~~~~ Game ~~~~~~~~~~~~~~~~~~~~~~~
int startGame(Map& map) {

      // give inputs to user
      char choice;
      while (true) {
          // notify observer of change to map
          map.updateMap();

          //cout << "Enter 'w' to move up, 's' to move down, 'a' to move left, 'd' to move right, or 'q' to quit: ";
          cout << "Enter a hotkey a-w-s-d to move cursor, [q]uit, [s]ave, l[o]ad, [m]odify + (1,2,3) to change type: ";
          cin >> choice;

          // Clear the input buffer
          cin.clear();
          cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

          switch (choice) {
              case 'w':
                  map.moveCharacter(0, -1);
                  break;
              case 's':
                  map.moveCharacter(0, 1);
                  break;
              case 'a':
                  map.moveCharacter(-1, 0);
                  break;
              case 'd':
                  map.moveCharacter(1, 0);
                  break;
              case 'q':
                  return 0; // Quit the function
              default:
                  std::cout << "Invalid choice. Try again." << std::endl;
                  break;
          }
      }
  }

int main() {

    Map map1(10, 10);
    Map map2(10, 10);
    Map map3(10, 10);

    Campaign campaign;
    campaign.addMap(map1);
    campaign.addMap(map2);
    campaign.addMap(map3);

    // Accumulate starting positions for each map to render them next to each other
    int startingPosAcc = 0;

    // Add the maps to the canvas
    for (int i = 0; i < campaign.maps.size(); i++)
    {
        Map map = campaign.maps[i];
        int mapSizeX = map.getMap().size();
        int mapSizeY = map.getMap()[0].size();

        int startX = startingPosAcc;

        // Copy the map onto the canvas
        for (int x = 0; x < mapSizeX; x++)
        {
            for (int y = 0; y < mapSizeY; y++)
            {
                campaign.canvas[startX + x][y] = map.getMap()[x][y];
            }
        }
        startingPosAcc += mapSizeX;
    }

    // Print the canvas initially
    campaign.printCanvas();

    // // Create a level builder with width 10, height 10, and level 1
    // LevelBuilder builder(10, 10, 1);

    // // load map from map builder
    // Map map = builder.build();

    // make a campaign

    Map map = Map(15,15);

    Campaign campaign;
    campaign.addMap(map);
//     campaign.addMap(map2);
//     campaign.addMap(map3);

    // Create a MapObserver instance and pass the Map reference to it
    MapObserver observer(map);

    // Add the observer to the map
    map.addObserver(&observer);

    // Start the game (which will trigger updates)
    startGame(map);


    return 0;
}
