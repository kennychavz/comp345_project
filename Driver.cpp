
#include <iostream>
#include "Part2_Map.cpp"
//#include "Part4_Dice.cpp" // Include Map class file
#include "MapObserver.cpp"  // Include MapObserver class file
//#include "Part4_MapBuilder.cpp"
#include "A2_Part3_CampaignEditor.cpp"
//#include "Part1_Character.cpp"
#include "PartOneCharacter/Character.h"
#include "Part4_MapBuilder.cpp"
//#include "GameLog.cpp"
#include <cstdlib>
#include <filesystem>
#include <thread>
#include <chrono>
#include <deque>

namespace fs = std::filesystem;
using std::exit;

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

void setUp () {
        time_t currentTime = time(nullptr);
        char* timeString = ctime(&currentTime);
    // Print out the current date and time
        cout << "This game was played at: " << timeString << endl;
    }

void printLog() {
        Map map;
        MapObserver mapObserver(map);
        cout << "\n*********************************** GAME LOG *****************************************\n" << endl;
         //if (controllerLogging == true) {
            setUp();
            cout << "Maps saved: " << endl;

        //}
        //if (mapLogging == true) {
            cout << "Previous positions: " << endl;

        //}

        //if (charLogging == true) {
            cout << "Attack record: " << endl;
            //charObserver.onCharacterUpdate();
        //}
        // //if (diceLogging == true ) {
        //     cout << "Dice roll record: " << endl;
        //     diceObserver.update();
        // //}

        cout << "\n***************************************************************************************\n" << endl;

}

std::deque<std::string> actions;
void addAction(const std::string& action) {
        if (actions.size() >= 5) {
            actions.pop_front();
        }
        actions.push_back(action);
}

 void printLastActions() {
    if(!actions.empty()) {
      // Clear the console
        //std::cout << "\033[2J\033[H";
        std::cout << "\nLast 5 actions:" << std::endl;
        for (const auto& action : actions) {
            std::cout << action << std::endl;
        }
    }
}

void greetingScreen() {
  cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ WELCOME ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;
   cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ TO KUTA ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n" << endl;

}
void congratulationsScreen() {
  std::this_thread::sleep_for(std::chrono::seconds(1));
   cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ CONGRATULATIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n" << endl;
   cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~YOU WON~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n" << endl;
}
void defeatScreen() {
  std::this_thread::sleep_for(std::chrono::seconds(1));
   cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ SORRY ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n" << endl;
   cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ YOU  LOST ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n" << endl;
}
void nothingScreen() {
cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n" << endl;
}
void attackScreen(int attackDmg) {
   cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << attackDmg << "dmg ATTACK ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n" << endl;
}
void fatalScreen() {
   cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ FATAL BLOW ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n" << endl;
}
void deathScreen() {
   cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ YOU DIED ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n" << endl;
}
void defenseScreen(int attackTaken) {
   cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << attackTaken << "dmg DEFENSE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n" << endl;
}

// void characterSelection(CampaignEditor& campaign) {
//   char choice;

//   while (true) {
//     // Clear the input buffer
//     cout << "Enter 'c' to create a character, 's' to move down, 'a' to move left, 'd' to move right, or 'q' to quit: ";
//     cin.clear();
//     cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//     cin >> choice; // Read user input into 'choice'

//       switch (choice) {
//           case 'w':
//               map.moveCharacter(0, -1);
//               break;
//           case 's':
//               map.moveCharacter(0, 1);
//               break;
//           case 'a':
//               map.moveCharacter(-1, 0);
//               break;
//           case 'd':
//               map.moveCharacter(1, 0);
//               break;
//           case 'q':
//               return; // Quit the function
//           default:
//               std::cout << "Invalid choice. Try again." << std::endl;
//               break;
//       }
//     }
// }

// ~~~~~~~~~~~~~~~~~~~ Game ~~~~~~~~~~~~~~~~~~~~~~~
void printHpBar(int& totalHp, int& remainingHp, char selection) {
    // if
    if (selection == 'v') { cout << "\t\t\t\t\t\tVillain HP: [ ";}
    if (selection == 'h') { cout << "Hero HP: [ ";}

  // print hp bar
    double percentageHp = static_cast<double>(remainingHp) / totalHp;

    cout << "";
    for (double i = 0; i < 1; i = i + 0.1) {
      if (i < percentageHp) {
        cout << "||||";
      }
      else {
        cout << " - ";
      }
    }
    cout << "]" << endl;

}

void printInline(Character& hero, Character& villain, int heroY, int heroX, int villainY, int villainX, char select) {
    std::system("clear");
    if (select== 'h') {cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ HIGHFIVE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n" << endl;}
    else {
      cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ BATTLE SCENE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n" << endl;
    }
    // Define the dimensions of the battle scene
    const int width = 70;
    const int height = 5;

    // retrieve hp of characters
    int villainTotalHp = villain.hitPoints;
    int villainRemainingHp = villain.remainingHitPoints;
    int heroTotalHp = hero.hitPoints;
    int heroRemainingHp = hero.remainingHitPoints;

    // villain Hp
    printHpBar(villainTotalHp, villainRemainingHp, 'v');

    cout << endl;

    // Print the battle scene
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (x == heroX && y == heroY)  {
                // Print the little guy and the bad guy
                cout << ":)";
            }else if (x == villainX && y == villainY) {
              cout << ">:(";
            } else {
                // Print empty space
                std::cout << " ";
            }
        }
        std::cout << std::endl;  // Move to the next line
    }

    cout << endl;

    // Hero Hp
    printHpBar(heroTotalHp, heroRemainingHp, 'h');

    cout << endl;
  }

void printFriendly(Character &hero, Character & villain) {

  std::this_thread::sleep_for(std::chrono::milliseconds(750));
  for (int i = 1; i< 3; i++) {
    if (i== 3) {
      printInline(hero, villain, 4-i, 15+14*i, 5-i, 68-14*i, 'f');
    }
    else {
      printInline(hero, villain, 4-i, 15+14*i, 5-i, 68-14*i, 'h');
    }
    nothingScreen();
    std::this_thread::sleep_for(std::chrono::milliseconds(750));

  }
}
void printRangedAttack(Character &hero, Character & villain, int arrowX, int arrowY) {
  std::system("clear");

  cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ RANGED ATTACK ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n" << endl;
    // Define the dimensions of the battle scene
    const int width = 70;
    const int height = 5;

    // Define the positions of the little guy and the bad guy
    int heroX = 15;
    int heroY = height - 1;
    int villainX = width - 2;
    int villainY = 0;

    // retrieve hp of characters
    int villainTotalHp = villain.hitPoints;
    int villainRemainingHp = villain.remainingHitPoints;
    int heroTotalHp = hero.hitPoints;
    int heroRemainingHp = hero.remainingHitPoints;

    // villain Hp
    printHpBar(villainTotalHp, villainRemainingHp, 'v');

    cout << endl;

    // Print the battle scene
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (x == heroX && y == heroY)  {
                // Print the little guy and the bad guy
                cout << ":)";
            }else if (x == arrowX && y == arrowY) {
              cout << ">--->";
            }

            else if (x == villainX && y == villainY) {
              cout << ">:(";
            } else {
                // Print empty space
                std::cout << " ";
            }
        }
        std::cout << std::endl;  // Move to the next line
    }
    cout << endl;

    // Hero Hp
    printHpBar(heroTotalHp, heroRemainingHp, 'h');

    cout << endl;
}


void printBattleScene(Character& hero, Character& villain) {
  std::system("clear");
  cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ BATTLE SCENE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n" << endl;
    // Define the dimensions of the battle scene
    const int width = 70;
    const int height = 5;

    // Define the positions of the little guy and the bad guy
    int heroX = 15;
    int heroY = height - 1;
    int villainX = width - 2;
    int villainY = 0;

    // retrieve hp of characters
    int villainTotalHp = villain.hitPoints;
    int villainRemainingHp = villain.remainingHitPoints;
    int heroTotalHp = hero.hitPoints;
    int heroRemainingHp = hero.remainingHitPoints;

    // villain Hp
    printHpBar(villainTotalHp, villainRemainingHp, 'v');

    cout << endl;

    // Print the battle scene
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (x == heroX && y == heroY)  {
                // Print the little guy and the bad guy
                cout << ":)";
            }else if (x == villainX && y == villainY) {
              cout << ">:(";
            } else {
                // Print empty space
                std::cout << " ";
            }
        }
        std::cout << std::endl;  // Move to the next line
    }
    cout << endl;

    // Hero Hp
    printHpBar(heroTotalHp, heroRemainingHp, 'h');

    cout << endl;
}

vector <string> itemsFound;

void printItemsFound() {
  for (string item : itemsFound) {
        std::cout << item << endl;
    }
    std::cout << std::endl;

}

vector <string> attackRecord;

void battle(Character& hero, Character& villain) {
    printBattleScene(hero, villain);
  while (true) {

    char choice;
    cout << "\tPress [r] for Ranged Attack \t\t\tPress [d] to Defend\n\tPress [m] for Melee Attack\t\t\tPress [f] to be Friendly\n";
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin >> choice; // Read user input into 'choice'

    cout << "choice is: " << choice << endl;

    // vars
    string vstring, hstring;
    int i, j;
    bool res;
    int heroDmg = hero.getAttackBonus() * 0.4;
    int villainDmg = villain.getAttackBonus() * 0.4;


    switch (choice) {

      case 'm':
        // attack
        printFriendly(hero, villain);
        res = villain.takeAttack(heroDmg);
        printBattleScene(hero, villain);
        hstring = "Hero Melee Damage = " + std::to_string(heroDmg);
        attackRecord.push_back(hstring);
        addAction(hstring);

        if (res) {

            attackRecord.push_back("Villain Defeated");
            addAction("Villain Defeated");
            fatalScreen();
             congratulationsScreen();

             // retrieve item from dead body
             // prompt user to open the chess
              cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Villain Dropped~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
              Item random_item = Item::generateRandomItem(hero);
              char choice;
              // cout << "Villain dropped";
              // random_item.printItem();
              // cout << "\n Press [l] to loot" << endl;
              // cin.clear();
              // cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
              // cin >> choice; // Read user input into 'choice'
              // if (choice == 'l') {
              //   // spawn item

              //   // equip it
              //   hero.equipItem(&random_item, 2);
              // }

             // call the logs
              return;
          } else {

            attackScreen(heroDmg);
            i += heroDmg;
            //cout << "\tVillain:" << endl;
            //villain.displayHitPoints();
            break;
          }

          break;

      case 'r':
        res = villain.takeAttack(villainDmg * 0.5);

        for (int i = 4; i>0; i--) {
          int x = (-i*5) + 35;
          int y = i;
          std::this_thread::sleep_for(std::chrono::milliseconds(600));
          printRangedAttack(hero, villain, (-i*15) + 80, i);
          hstring = "Hero Ranged Damage = " + std::to_string(heroDmg);
          attackRecord.push_back(hstring);
          addAction(hstring);
        }
        // ranged scene
        if (res) {

            attackRecord.push_back("Villain Defeated");
            addAction("Villain Defeated");
            fatalScreen();
             congratulationsScreen();

             // retrieve item from dead body
             // prompt user to open the chess
              cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Villain Dropped~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
              Item random_item = Item::generateRandomItem(hero);
              char choice;
              // random_item.printItem();
              // cout << "\n Press [l] to loot" << endl;
              // cin.clear();
              // cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
              // cin >> choice; // Read user input into 'choice'
              // if (choice == 'l') {
              //   // spawn item

              //   // equip it
              //   hero.equipItem(&random_item, 2);
              // }

             // call the logs
              return;
          } else {

            attackScreen(heroDmg);
            i += heroDmg;
            //cout << "\tVillain:" << endl;
            //villain.displayHitPoints();
            break;
          }

          break;

      case 'd':
        // defend
        res = hero.takeAttack(villainDmg);
        printBattleScene(hero, villain);
        defenseScreen(villainDmg);
        vstring = "Hero Damage = " + std::to_string(villainDmg);
        attackRecord.push_back(vstring);
        addAction(vstring);

        if (res) {
              attackRecord.push_back("YOU DIED");
              addAction("YOU DIED");
              fatalScreen();
             defeatScreen();

             // call the logs
              return;
          } else {
            j += villainDmg;
            //cout << "\tVillain:" << endl;
            //villain.displayHitPoints();
            break;
          }

          break;
        break;

      case 'f':
        // friendly
        printFriendly(hero, villain);

        // if (res) {
        //      defeatScreen();
        //       return;
        //   } else {
        //     //cout << "\tVillain:" << endl;
        //     //villain.displayHitPoints();
        //     break;
        //   }
        //   break;
        break;
      }
  }
}

void printAttackRecord() {
        for (string attack : attackRecord) {
        std::cout << attack << endl;
    }
    std::cout << std::endl;
    }

void chooseStrategy(Character& hero, Character& villain) {
  // print battle scene
  char choice;
  cout << "Press [x] to battle ";
  cin.clear();
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  cin >> choice; // Read user input into 'choice'

    switch (choice) {
      case 'x':
        battle(hero, villain);
      default:
      std::cout << "Invalid choice. Try again." << std::endl;
      break;
    }
}

int rollDice() {
    int sumResult = 0;
    int diceValues[4];
    for (int i = 0; i < 4; i++) {
        diceValues[i] = rand() % 6 + 1;
    }
    int lowest = 6;
    int lowestIndex;
    for (int i = 0; i < 4; i++) {
        if (diceValues[i] < lowest) {
            lowest = diceValues[i];
            lowestIndex = i;
        }
    }
    for (int i = 0; i < 4; i++) {
        if (i == lowestIndex) continue;
        else
            sumResult += diceValues[i];
    }

    return sumResult;
}

void startGame(Map& map) {
  char choice;
  int result;
  map.hero.printUI();
  map.printMap();

  while (true) {
  // Clear the input buffer
    cout << "\nHit 1 to roll the dice: ";
    cin >> choice;
    if (choice == '1') {
      result = rollDice();
    }

    cin.clear();

    while (result > 0) {
      map.hero.printUI();
      map.printMap();
      cout << "You have " << result << " moves left." << endl;
      printLastActions();
      

      //
      cout << map.checkForEnnemies() << endl;
      if (map.checkForEnnemies()) {
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~VILLAIN FOUND~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;
        chooseStrategy(map.hero, map.villain);
      }

      cout << map.checkForEnnemies() << endl;
      if (map.checkForItems()) {
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CHEST FOUND~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;

        // prompt user to open the chess
        char choice;
        cout << "Press [x] to open the chess" << endl;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin >> choice; // Read user input into 'choice'
        if (choice == 'x') {
          // spawn item
          Item random_item = Item::generateRandomItem(map.hero);

          // equip it
          map.hero.equipItem(&random_item, 2);
          itemsFound.push_back(random_item.getName()+ ", Bonus: " + to_string(random_item.getBonus()));
          addAction(random_item.getName()+ " equipped with a bonus of " + to_string(random_item.getBonus()));
          continue;
        }

      else
        continue;
      }

      // check if theres is an enemy nearby
      cout << "Enter 'w' to move up, 's' to move down, 'a' to move left, 'd' to move right, or 'q' to quit: ";
      cin.clear();
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      cin >> choice; // Read user input into 'choice'
        switch (choice) {
            // case 't':
            //     map.tryMove('');
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
            //addAction(printPastPos);
        }
      result--;
    }
    if (result == 0) {
      cout << "YOU ARE OUT OF MOVES." << endl;
      startGame(map);
    }

  }
}

int startCampaign(CampaignEditor& campaign) {

      MapDirector mapDirector;

      // give inputs to user
      char choice;
      char recordChoice;
      char input;
      string filename;
      int width, height;

      while (true) {

          //cout << "Enter 'w' to move up, 's' to move down, 'a' to move left, 'd' to move right, or 'q' to quit: ";
          cout <<"Enter a hotkey [q]uit, [c]reate new map, [s]ave, l[o]ad, [m]odify: ";

          // Clear the input buffer
          cin >> choice; // Read user input into 'choice'
          cin.clear();
          cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

          switch (choice) {

            case 'q':
              // Quit the program
              //cout << "1";
              char recordChoice;
              cout << "Do you want to record the game? (y/n): ";
              cin >> recordChoice;

              if (recordChoice == 'y') {
                  cout << "\n*********************************** GAME LOG *****************************************\n" << endl;
                  setUp();

                  cout << "Previous positions: " << endl;
                  campaign.printPastPos();

                  cout << "Attack record: "<< endl;
                  printAttackRecord();

                  cout << "Maps saved: " << endl;
                  printMapLoaded();

                  cout << "Items equipped: " << endl;
                  printItemsFound();
              }

              std::cout << "Thank you for playing!" << std::endl;
              std::exit(EXIT_SUCCESS);

              return 0;
            // new game
            case 'c':
              // cout << "Enter width: ";
              // cin >> width;
              // cout << " Enter height: ";
              // cin >> height;

              // cout <<width<<endl;
              // cout <<height<<endl;
              // //cout << width << " " << height << endl;

              //campaign.appendMap(Map(width,height));

              cout << "Do you want to record the game? (y/n): ";
              cin >> recordChoice;

              campaign.appendMap(Map(20,20));
              // // Create a MapObserver instance and pass the Map reference to it
              // MapObserver observer(campaign.campaign);
              // // Add the observer to the map
              // campaign.campaign.addObserver(&observer);

              cout << "going to spawn my items" << endl;

              // // spawn a bad person
              // cout << 1 << endl;
              // campaign.campaign.spawnVillain();
              // cout << 2 << endl;
              // campaign.campaign.spawnHero();
              // cout << 3 << endl;
              // campaign.campaign.spawnItems();
              // cout << 4 << endl;


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

              // spawn a bad person
              map.spawnVillain();
              map.spawnHero();
              map.spawnItems();


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

  // m
  // Character fighter(10); // ex: Create a fighter with a given level
  // Character hero = fighter;
  // Character fighter2(10); // ex: Create a fighter with a given level
  // Character villain = fighter2;
  // battle(hero, villain);


  // std::exit(EXIT_SUCCESS);


  std::system("clear");
  greetingScreen();
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
