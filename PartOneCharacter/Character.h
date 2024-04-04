#ifndef CHARA_BUILD
#define CHARA_BUILD

#include <string>
#include <vector>
#include <list> // For the observer list

using namespace std;

class CharacterBuilder; //Forward Declaration
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
    int armorClass;
    int attackBonus;
    int damageBonus;
    int attacksPerRound;

    Item *equipment[6]; // Armor, Shield, Weapon, Boots, Ring, Helmet

    void generateAbilityScores();

    void calculateHitPoints();

    void calculateArmorClass();

    void calculateAttackBonus();

    void calculateDamageBonus();

    int rollDice();

    list<ICharacterObserver*> observers; // List to store observers

public:
    int abilityScores[6]; // STR, CON, DEX, INT, CHA, WIS
    int abilityModifiers[6];
    string type;
    string skill_description;
    int hitPoints;
    int remainingHitPoints;

    Character();

    Character(int level);

    void setBuilder(CharacterBuilder* builder);

    void attachObserver(ICharacterObserver *observer);

    void detachObserver(ICharacterObserver *observer);

    void notifyObservers();

    void equipItem(Item *item, int slot);

    void displayCharacter();

    std::vector<int> getAbilityScores() const;

    int getHitPoints();

    int getArmorClass();

    int getAttackBonus();

    void updateAttackBonus();

    void updateAttacksPerRound();

    bool takeAttack(int heroDmg);

    void levelUp();

};

// The observer reacts to changes in the subject
class CharacterObserver : public ICharacterObserver {
public:
    void onCharacterUpdate(Character *character);
};


#endif // CHARA_BUILD
