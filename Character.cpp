#include "Character.h"
#include <iostream>
#include <string>
#include <vector>
#include <list> // For the observer list

using namespace std;


Item::Item(string name, int bonus) : name(name), bonus(bonus) {}

Character::Character(int level) : level(level)
{
    srand((unsigned)time(0)); // To seed the random number generator used by rand().
    // To ensure the random number generator is seeded with a unique value based on current time.
    // Assuming the character creation has at least 1 minute interval.
    generateAbilityScores();
    calculateHitPoints();
    calculateArmorClass();
    calculateAttackBonus();
    calculateDamageBonus();
    for (int i = 0; i < 6; i++)
    {
        equipment[i] = nullptr; // Initialize empty equipment slots.
    }
}

void Character::generateAbilityScores()
{
    for (int i = 0; i < 6; i++)
    {
        abilityScores[i] = rand() % 16 + 3; // Roll 3d6. i.e. Rolling three six-sided dices and sum the result.
        abilityModifiers[i] = (abilityScores[i] - 10) / 2; // Score of 10 gives a +0 modifier,
        // and each even number above/below adjusts the modifier by 1 accordingly.
    }
}

void Character::calculateHitPoints()
{
    int baseHP = 10; // Base HP for fighter class
    hitPoints = baseHP + (abilityModifiers[2] * level); // CON modifier
}

void Character::calculateArmorClass()
{
    armorClass = 10 + abilityModifiers[1]; // DEX modifier
}

void Character::calculateAttackBonus()
{
    attackBonus = level + abilityModifiers[0]; // STR modifier
}

void Character::calculateDamageBonus() {
    damageBonus = abilityModifiers[0]; // STR modifier
}

//------------- Observer Management -----------------

void Character::attachObserver(ICharacterObserver *observer) {
    observers.push_back(observer);
}

void Character::detachObserver(ICharacterObserver *observer) {
    observers.remove(observer);
}

void Character::notifyObservers() {
    for (auto observer : observers) {
        observer->onCharacterUpdate(this);
    }
}

void Character::equipItem(Item *item, int slot) {
    if (slot >= 0 && slot < 6)
    {
        equipment[slot] = item;

        // Adjust stats based on the slot the item is equipped in
        // NOTE: The adjustments are based on assumptions.
        switch (slot) {
            case 0: // Armor slot
                // Armor increases hit points
                hitPoints += item->bonus;
                break;
            case 1: // Shield slot
                // Shields increase armor class
                armorClass += item->bonus;
                break;
            case 2: // Weapon slot
                // Weapons increase attack bonus
                attackBonus += item->bonus;
                break;
            case 3: // Boots slot
                // Boots increase DEX
                abilityScores[1] += item->bonus;
                break;
            case 4: // Ring slot
                // Rings can increase CONST
                abilityScores[2] += item->bonus;
                break;
            case 5: // Helmet slot
                // Helmets increase armor class
                armorClass += item->bonus;
                break;
            default:
                // If somehow an invalid slot is passed, do nothing
                break;
        }
        notifyObservers();
    }
}

void Character::displayCharacter()
{
    cout << "\nLevel: " << level << endl;
    cout << "Ability Scores and Modifiers: " << endl;
    string abilities[6] = {"STR (Strength)", "DEX (Dexterity)", "CON (Constitution)",
                            "INT (Intelligence)", "WIS (Wisdom)", "CHA (Charisma)"};
    for (int i = 0; i < 6; i++)
    {
        cout << abilities[i] << ": " << abilityScores[i] << " (" << abilityModifiers[i] << ")" << endl;
    }
    cout << "Hit Points: " << hitPoints << endl;
    cout << "Armor Class: " << armorClass << endl;
    cout << "Attack Bonus: " << attackBonus << endl;
    cout << "Damage Bonus: " << damageBonus << endl;
}

std::vector<int> Character::getAbilityScores() const {
    return std::vector<int>(abilityScores, abilityScores + 6);
}

int Character::getHitPoints(){
    return hitPoints;
}

int Character::getArmorClass(){
    return armorClass;
}

int Character::getAttackBonus(){
    return attackBonus;
}

void CharacterObserver::onCharacterUpdate(Character *character) {
    // Re-display character view
    cout << "\nCharacter View Updated:\n";
    character->displayCharacter();
}
