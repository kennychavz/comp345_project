#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "Part4_Dice.h"
#include "Observable.cpp"
using namespace std;

class Dice : Observable {


private:
    //generates number based on sides between [1, sides]
    int rollOnce(int sides) {
                return (rand() % sides) + 1;
    }
    vector<int> results;
    vector<Observer*> observers;

public:
      
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

    //constructor
    Dice() {
        srand(static_cast<unsigned int>(time(nullptr)));
    }

    //generate result based on expression xdy[+z]
    int rollDice(string& expression) {

        int num, sides, modifier = 0;
        char d;

        //find d
        size_t posD = expression.find('d');
        if (posD == string::npos) { //if 'd' not found in the expression, gives an error

            cerr << "Invalid dice expression\n";
            return 0;
        }

        //find + for modifier
        int posModifier = expression.find('+');

        //create substring for num and modifiier
        try {

            num = stoi(expression.substr(0, posD)); //parse sring into int
            sides = stoi(expression.substr(posD + 1, posModifier));

        } catch (const exception& e) { //throws an exception if the expression is not formatted correctly
            cerr << "Invalid dice expression\n";
            return 0;

        }

        //validate dice -> num is at least 1, d4 d6 d8 d10 d12 d20 d100
        if (!(num > 0) || !(sides == 4 || sides == 6 || sides == 8 || sides == 10 || sides == 12 || sides == 20 || sides == 100)) {

            cerr << "Invalid dice expression\n";
            return 0;

        }

        //add modifier
        if (posModifier != string::npos) {

            try {
                modifier = stoi(expression.substr(posModifier + 1, expression.length() - 1)); //create substring for modifier and parse into integer

            } catch (const exception& e) {
                cerr << "Invalid modifier\n";
                return 0;
            }
        }

        int total = 0;
        for (int i = 0; i < num; ++i) { // for number of times rolled, generates dice roll and adds it to total

            total += rollOnce(sides);
        }
        int result = total + modifier;
        results.push_back(result);
        notifyObservers();
        return result;
    }

    vector<int>& getPastResults() {
        return results;
    }

};

class DiceObserver : Observer {
public:
    DiceObserver(Dice& dice) : dice(dice) {};

    void update () { 

        vector<int>& pastResults = dice.getPastResults();
        //cout << "Past dice roll results: " << endl;
        for (int result : pastResults) {
            cout << result << endl;
        }
        cout << endl;
    }

    // void printDiceLog () {

    //     vector<int>& pastResults = dice.getPastResults();
    //     cout << "Past dice roll results: " << endl;
    //     for (int result : pastResults) {
    //         cout << result << endl;
    //     }
    //     cout << endl;
    // }

private:
    Dice& dice;

};

// //test
// int main() {

//     string str;
//     Dice dice;
//     DiceObserver observer(dice);

//     while (true) {
//             string str;
//             cout << "Enter a dice expression in the form xdy[+z] (enter 'q' to quit): ";
//             getline(cin, str);

//             if (str == "q") {
//                 cout << "Exiting..." << endl;
//                 observer.update(); //prints past result 
//                 break; // Exit the loop
//             }

//             int result = dice.rollDice(str);
//             cout << "Your result is " << result << endl;
//     }

//     return 0;

// }
