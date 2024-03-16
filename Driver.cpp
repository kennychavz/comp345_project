
#include <iostream>
#include "Part2_Map.cpp"  // Include Map class file
#include "MapObserver.cpp"  // Include MapObserver class file
//#include "Part4_MapBuilder.cpp"
#include "A2_Part3_CampaignEditor.cpp"
#include "Part1_Character.cpp"
#include "Part4_MapBuilder.cpp"
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

vector<string> getFilenames() {
    // Path to the folder
    fs::path folder_path = "data/maps/";

    // Vector to store filenames
    std::vector<std::string> filenames;

    // Iterate over the files in the folder
    for (const auto& entry : fs::directory_iterator(folder_path)) {
        // Check if the entry is a regular file
        if (fs::is_regular_file(entry)) {
            // Get the filename and add it to the vector
            filenames.push_back(entry.path().filename().string());
        }
    }

    return filenames;
}

// ~~~~~~~~~~~~~~~~~~~ Game ~~~~~~~~~~~~~~~~~~~~~~~
void startGame(Map& map) {
  char choice;

  while (true) {
  // Clear the input buffer
  map.printMap();
  cout << "Enter 'w' to move up, 's' to move down, 'a' to move left, 'd' to move right, or 'q' to quit: ";
  cin.clear();
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  cin >> choice; // Read user input into 'choice'

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
            return; // Quit the function
        default:
            std::cout << "Invalid choice. Try again." << std::endl;
            break;
    }
  }
}

int startCampaign(CampaignEditor& campaign) {

      MapDirector mapDirector;

      // give inputs to user
      char choice;
      char choice1;
      char choice2;
      char input;
      string filename;
      int width, height;

      while (true) {

          //cout << "Enter 'w' to move up, 's' to move down, 'a' to move left, 'd' to move right, or 'q' to quit: ";
          cout <<"Enter a hotkey [q]uit, [c]reate new map,[s]ave, l[o]ad, [m]odify";

          // Clear the input buffer
          cin >> choice; // Read user input into 'choice'
          cin.clear();
          cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

          switch (choice) {

            case 'q':
              // Quit the program
              cout << "1";
               std::exit(EXIT_SUCCESS);
              return 0;

            case 'c':
              cout << "Enter width: ";
              cin >> width;
              cout << " Enter height: ";
              cin >> height;

              cout <<width<<endl;
              cout <<height<<endl;
              //cout << width << " " << height << endl;

              campaign.appendMap(Map(width,height));
              // // Create a MapObserver instance and pass the Map reference to it
              // MapObserver observer(campaign.campaign);
              // // Add the observer to the map
              // campaign.campaign.addObserver(&observer);

              cout << "appending the map";
              //once part is finished
              startGame(campaign.campaign);

              break;

            case 's':
              // Save the campaign
              cout << "Enter a filename: ";
              cin >> filename;
              campaign.saveCampaign(filename);
              cout << "Campaign saved." << endl;
              break;

            case 'o':
              // Load a campaign

              cout << "Choose your campaign"<< endl;

              vector<string> maps = getFilenames();
              for (int i = 0; i<maps.size(); i++) {
                cout << i+1<< ": Campaign " << maps[i] << endl;
              }

              cout << "Enter a filename: ";
              cin >> filename;
              Map map = campaign.loadCampaign("data/maps/" + filename);
              cout << "Campaign loaded." << endl;

              startGame(map);
              break;

          // case 'm':
          //     // Modify the cell at the cursor
          //     cout << "Enter a new type for the cell (1, 2, 3): " << endl;
          //     int newType;
          //     cin >> newType;
          //     //campaign.changeCellType(campaign.cursorX, campaign.cursorY, newType);
          //     break;

          }
      }



  };

int main() {

  //
    string mapName1 = "data/maps/Asia.txt";
    string mapName2 = "data/maps/Europe.txt";
    string mapName3 = "data/maps/America.txt";

    // make 3 maps
    Map map = Map(20, 20);
    Map map2 = Map(20, 20);
    Map map3 = Map(20, 20);

    //map.printMap();

    MapDirector mapDirector = MapDirector();
    mapDirector.saveMap(map, mapName1);
    mapDirector.saveMap(map3, mapName2);
    mapDirector.saveMap(map2, mapName3);




    //Map mapLoaded = mapDirector.readMapFromFile(mapName1);

    // load 3 levels from thien an
    vector<vector<int> > mapData = mapDirector.readMapFromFile(mapName1);

    Map mapLoaded = Map(mapData, mapName1);


    //mapLoaded.printMap();


    // add them to the campaign
    CampaignEditor campaign;
    // campaign.addMap(map1);
    // campaign.addMap(map2);
    // campaign.addMap(map3);


    startCampaign(campaign);
    // start the game
    // startGame(campaign);

//     // Accumulate starting positions for each map to render them next to each other
//     int startingPosAcc = 0;

//     // Add the maps to the canvas
//     for (int i = 0; i < campaign.maps.size(); i++)
//     {
//         Map map = campaign.maps[i];
//         int mapSizeX = map.getMap().size();
//         int mapSizeY = map.getMap()[0].size();

//         int startX = startingPosAcc;

//         // Copy the map onto the canvas
//         for (int x = 0; x < mapSizeX; x++)
//         {
//             for (int y = 0; y < mapSizeY; y++)
//             {
//                 campaign.canvas[startX + x][y] = map.getMap()[x][y];
//             }
//         }
//         startingPosAcc += mapSizeX;
//     }

//     // Print the canvas initially
//     campaign.printCanvas();

//     // // Create a level builder with width 10, height 10, and level 1
//     // LevelBuilder builder(10, 10, 1);

//     // // load map from map builder
//     // Map map = builder.build();

//     // make a campaign

//     Map map = Map(15,15);

//     Campaign campaign;
//     campaign.addMap(map);
// //     campaign.addMap(map2);
// //     campaign.addMap(map3);

//     // Create a MapObserver instance and pass the Map reference to it
//     MapObserver observer(map);

//     // Add the observer to the map
//     map.addObserver(&observer);

//     // Start the game (which will trigger updates)
//     startGame(map);


    return 0;
}
