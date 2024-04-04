#include "Character.h"
#include "CharacterBuilder.h"
#include <iostream>


using namespace std;


//Item::Item(string name, int bonus) : name(name), bonus(bonus) {}

class ItemContainer
{
    std::vector<Item *> items;

public:
    ~ItemContainer()
    {
        for (Item *item : items)
        {
            delete item;
        }
    }

    void addItem(Item *item)
    {
        items.push_back(item);
    }

    Item *getItem(const std::string &name)
    {
        for (Item *item : items)
        {
            if (item->getName() == name)
            {
                return item;
            }
        }
        return NULL;
    }
};

Character::Character(int level) : level(level)
{
    type = "Fighter";
    skill_description = "Base Fighter";
    srand((unsigned)time(0)); // To seed the random number generator used by rand().
    // To ensure the random number generator is seeded with a unique value based on current time.
    // Assuming the character creation has at least 1 minute interval.
    generateAbilityScores();
    calculateHitPoints();
    remainingHitPoints = hitPoints;
    calculateArmorClass();
    calculateAttackBonus();
    calculateDamageBonus();
    ItemContainer backpack;
    for (int i = 0; i < 6; i++)
    {
        equipment[i] = nullptr; // Initialize empty equipment slots.
    }
}

void Character::setBuilder(CharacterBuilder* builder) {
    builder->build(this);
}

void Character::generateAbilityScores()
{
    for (int i = 0; i < 6; i++)
    {
        abilityScores[i] = rollDice(); // Roll 4d6 and sum the MAX 3/4 dice values.
        abilityModifiers[i] = (abilityScores[i] - 10) / 2; // Score of 10 gives a +0 modifier,
        // and each even number above/below adjusts the modifier by 1 accordingly.
    }
}

void Character::calculateHitPoints()
{
    int baseHP = 10; // Base HP for fighter class
    hitPoints = baseHP + (abilityModifiers[1] * level); // CON modifier
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

int Character::rollDice() {
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


//------------- Character Modification/Display -----------------

void Character::equipItem(Equipment *item, int slot) {
    if (slot >= 0 && slot < 6)
    {
        equipment[slot] = item;

        // Adjust stats based on the slot the item is equipped in
        // NOTE: The adjustments are based on assumptions.
        switch (slot) {
            case 0: // Armor slot
                // Armor increases hit points
                hitPoints += item->getEnchantmentBonus();
                break;
            case 1: // Shield slot
                // Shields increase armor class
                armorClass += item->getEnchantmentBonus();
                break;
            case 2: // Weapon slot
                // Weapons increase attack bonus
                attackBonus += item->getEnchantmentBonus();
                break;
            case 3: // Boots slot
                // Boots increase DEX
                abilityScores[2] += item->getEnchantmentBonus();
                break;
            case 4: // Ring slot
                // Rings can increase CONST
                abilityScores[1] += item->getEnchantmentBonus();
                break;
            case 5: // Helmet slot
                // Helmets increase armor class
                armorClass += item->getEnchantmentBonus();
                break;
            default:
                // If somehow an invalid slot is passed, do nothing
                break;
        }
        notifyObservers();
    }
}

void Character::use(UsableItem *item) {
    if (item->getName() == "Healing Potion") {
        int healAmount = item->getEnchantmentBonus();
        remainingHitPoints = std::min(remainingHitPoints + healAmount, hitPoints);
        std::cout << "Used Healing Potion! Healed for " << healAmount << " HP." << std::endl;
    } else if(item->getName() == "Potion of Strength") {
        damageBonus += item->getEnchantmentBonus();
        std::cout << "Used Potion of Strength! Damage bonus increased by " << item->getEnchantmentBonus() << std::endl;
    } else {
        std::cout << "Unknown usable item!" << std::endl;
    }
    notifyObservers();
}

void Character::displayCharacter()
{
    cout << "\nType: " << type << endl;
    cout << "Skill: " << skill_description << endl;
    cout << "Level: " << level << endl;
    cout << "\nAbility Scores and Modifiers: " << endl;
    string abilities[6] = {"STR (Strength)", "CON (Constitution)", "DEX (Dexterity)",
                           "INT (Intelligence)", "WIS (Wisdom)", "CHA (Charisma)"};
    for (int i = 0; i < 6; i++)
    {
        cout << abilities[i] << ": " << abilityScores[i] << " (" << abilityModifiers[i] << ")" << endl;
    }
    cout << "Hit Points: " << hitPoints << endl;
    cout << "Armor Class: " << armorClass << endl;
    cout << "Attack Bonus: " << attackBonus << endl;
    cout << "Attack Per Rounds: " << attacksPerRound << endl;
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

void Character::updateAttackBonus() {
    attackBonus++; // +1 attack bonus every level
}

void Character::updateDamageBonus(int bonus){
    damageBonus += bonus;
}

void Character::updateAttacksPerRound() {
    attacksPerRound = 1 + level / 5; // 1 attack at initial levels, +1 every 5 levels
}

bool Character::takeAttack(int heroDmg){
    if (remainingHitPoints > heroDmg) {
        remainingHitPoints -= heroDmg;
        return true;
    }
    else {
        remainingHitPoints = 0;
        return false;
        cout << "\nDEBUG: Character Died!" << endl;
    }
}

void Character::levelUp() {
    level++;
    calculateHitPoints();
    updateAttackBonus();
    updateAttacksPerRound();

    notifyObservers();
}


void CharacterObserver::onCharacterUpdate(Character *character) {
    // Re-display character view
    cout << "\nCharacter View Updated:\n";
    character->displayCharacter();
}

