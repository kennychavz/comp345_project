#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "Observable.cpp"
#include "Part2_Map.cpp"
#include "Part1_Character.cpp"
#include "MapObserver.cpp"
#include "Part4_Dice.cpp"


using std::string;
using std::cout;
using std::cin;
using std:: endl;
using std::vector;


class GameController : public Observer {
public:
    void update() {
        
    }

    void setUp () {
        time_t currentTime = time(nullptr);
        char* timeString = ctime(&currentTime);

    // Print out the current date and time
        cout << "This game was played at: " << timeString << endl;
    }
};


class GameLog : Observable {

private:
    vector <Observer*> observers;
    GameController gameController;
    MapObserver mapObserver;
    CharacterObserver charObserver;
    DiceObserver diceObserver;

    bool loggingEnabled;
    // bool controllerLogging;
    // bool mapLogging;
    // bool charLogging;
    // bool diceLogging;

    vector<string> logs;

public: 

    GameLog(GameController& gameController, MapObserver& mapObserver, CharacterObserver& charObserver, DiceObserver& diceObserver)
        : gameController(gameController), mapObserver(mapObserver), charObserver(charObserver), diceObserver(diceObserver) {}

    void setLogging(bool enabled) {
        loggingEnabled = enabled;
    }

    // void setControllerLogging(bool enabled) {
    //     controllerLogging = enabled;
    // }

    // void setMapLogging(bool enabled) {
    //     mapLogging = enabled;
    // }

    // void setCharLogging(bool enabled) {
    //     charLogging = enabled;
    // }

    // void setDiceLogging(bool enabled) {
    //     diceLogging = enabled;
    // }
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
        if (loggingEnabled) {
            for (Observer* observer : observers) {
            observer->update();
                }
            }
        }
    
    void printLog() {

        cout << "/n******************** GAME LOG **************************/n" << endl;

         //if (controllerLogging == true) {
            gameController.setUp();
            cout << "Maps saved: " << endl; 
            //return campaign names
        //}

        //if (mapLogging == true) { 
            cout << "Previous positions: " << endl;
            mapObserver.printPastPos(); 
        //}

        //if (charLogging == true) {
            cout << "Attack record: " << endl;
            //charObserver.onCharacterUpdate();
        //}

        //if (diceLogging == true ) {
            cout << "Dice roll record: " << endl;
            diceObserver.update();
        //}

        cout << "/n*******************************************************/n" << endl;
    }
};

// int main() {
    
//     char input;
//     int choice;
//     Map map;
//     Dice dice;

//     GameController gameController;
//     MapObserver mapObserver(map);
//     CharacterObserver charObserver;
//     DiceObserver diceObserver(dice);

//     GameLog gameLog = GameLog(gameController, mapObserver, charObserver, diceObserver);
//     gameLog.addObserver(&gameController);
//     gameLog.addObserver(&mapObserver);
//     //gameLog.addObserver(&charObserver);
//     //gameLog.addObserver(&diceObserver);


//     bool validInput = false;

//     while (!validInput) {
//         cout << "Do you want to record this game? (y/n): ";
//         cin >> input;

//         switch (input) {

//             case 'y':
//                 gameLog.setLogging(true);
//                 validInput = true;
//                 //gameLog.printLog();
//                 cout << "What would you like to log?" << endl << "(1) Maps" << endl << "(2) Character moves" << endl << "(3) Character attacks"
//                     << endl << "(4) Dice rolls" << endl << "(5) All of the above" << endl;
//                 cin >> choice;
//                 // switch (choice) {
//                 // case 1:
//                 //     gameLog.setControllerLogging(true);
//                 //     break;
//                 // case 2:
//                 //     gameLog.setMapLogging(true);
//                 //     break;
//                 // case 3:
//                 //     gameLog.setCharLogging(true);
//                 //     break;
//                 // case 4:
//                 //     gameLog.setDiceLogging(true);
//                 //     break;
//                 // case 5: 
//                 //     gameLog.setCharLogging(true);
//                 //     gameLog.setCharLogging(true);
//                 //     gameLog.setMapLogging(true);
//                 //     gameLog.setDiceLogging(true);
//                 // default:
//                 //     break;
//                 // }
                
//                 gameLog.printLog();
//                 break;

//             case 'n':
//                 gameLog.setLogging(false);
//                 validInput = true;
//                 break;
//             default: 
//                 cout << "Invalid input. Please try again." << endl;
//         }
//     }



// };
