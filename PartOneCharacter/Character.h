#ifndef CHARA_BUILD
#define CHARA_BUILD


#include <iostream>
#include <string>
#include <vector>
#include <list> // For the observer list

using namespace std;

class Character;

// observer interface
class ICharacterObserver {
public:
    virtual void onCharacterUpdate(Character *character) = 0; //Abstract/Pure_Virtual Function
};

class Item
{
public:
    string name;
    int bonus;
    Item(string name, int bonus);
};

class Character {
private:
    int level;
    int abilityScores[6]; // STR, DEX, CON, INT, WIS, CHA
    int abilityModifiers[6];
    int hitPoints;
    int armorClass;
    int attackBonus;
    int damageBonus;
    Item *equipment[6]; // Armor, Shield, Weapon, Boots, Ring, Helmet

    void generateAbilityScores();

    void calculateHitPoints();

    void calculateArmorClass();

    void calculateAttackBonus();

    void calculateDamageBonus();

    list<ICharacterObserver*> observers; // List to store observers

public:
    Character(int level);

    void attachObserver(ICharacterObserver *observer);

    void detachObserver(ICharacterObserver *observer);

    void notifyObservers();

    void equipItem(Item *item, int slot);

    void displayCharacter();

    std::vector<int> getAbilityScores() const;

    int getHitPoints();

    int getArmorClass();

    int getAttackBonus();

};

// The observer reacts to changes in the subject
class CharacterObserver : public ICharacterObserver {
public:
    void onCharacterUpdate(Character *character);
};


#endif // CHARA_BUILD