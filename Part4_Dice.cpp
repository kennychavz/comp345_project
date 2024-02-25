#include <iostream>
#include <cstdlib>
#include <string>
#include "dice.h"
using namespace std;

//constructor
Dice::Dice() {

   //generate srand unsigned int 
    srand(static_cast<unsigned int>(time(nullptr)));
}

//generates number based on sides between [1, sides]
int Dice::rollOnce(int sides) {

    return (rand() % sides) + 1;
}

//generate result based on expression xdy[+z]
int Dice::rollDice(string& expression) {

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

    return total + modifier; // adds the total with the modifier for the final result 

}

//test
int main() {

    string str;
    Dice dice;

    str = "3d100[+9]"; //valid 
    //str = "6d5[+10]"; //invalid

    // cout << "Enter a dice expression in the form xdy[+z] : ";
    // getline(cin, str); //makes sure that the entire string is consumed
    int result = dice.rollDice(str);
    cout << "Your result is " << result << endl;

    return 0;

}


// int DiceRoll::d4() {
//     return (std::rand() % 4) + 1;
// };

// int DiceRoll::d6() {
//     return (std::rand() % 6) + 1;
// };

// int DiceRoll::d8() {
//     return (std::rand() % 8) + 1;
// };

// int DiceRoll::d10() {
//     return (std::rand() % 10) + 1;
// };

// int DiceRoll::d12() {
//     return (std::rand() % 12) + 1;
// };

// int DiceRoll::d20() {
//     return (std::rand() % 20) + 1;
// };

// int DiceRoll::d100() {
//     return (std::rand() % 100) + 1;
// };
