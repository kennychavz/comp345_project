#ifndef DICE_H
#define DICE_H

#include <string>

class Dice {
//roll based one the kind of dice
private:
    int rollOnce(int sides);
    
//roll with the proper expression
public:
    Dice();
    int rollDice(std::string& expression);
};


#endif //DICE_H