#include <iostream>
#include <string>
#include <vector>
#include <list> // For the observer list

using namespace std;

class Character;

// observer interface
class ICharacterObserver {
public:
    virtual void onCharacterUpdate(Character *character) = 0;
};

class Item
{
public:
    string name;
    int bonus;
    Item(string name, int bonus) : name(name), bonus(bonus) {}
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

    void generateAbilityScores()
    {
        for (int i = 0; i < 6; i++)
        {
            abilityScores[i] = rand() % 16 + 3; // Roll 3d6. i.e. Rolling three six-sided dices and sum the result.
            abilityModifiers[i] = (abilityScores[i] - 10) / 2; // Score of 10 gives a +0 modifier,
            // and each even number above/below adjusts the modifier by 1 accordingly.
        }
    }

    void calculateHitPoints()
    {
        int baseHP = 10; // Base HP for fighter class
        hitPoints = baseHP + (abilityModifiers[2] * level); // CON modifier
    }

    void calculateArmorClass()
    {
        armorClass = 10 + abilityModifiers[1]; // DEX modifier
    }

    void calculateAttackBonus()
    {
        attackBonus = level + abilityModifiers[0]; // STR modifier
    }

    void calculateDamageBonus() {
        damageBonus = abilityModifiers[0]; // STR modifier
    }
    list<ICharacterObserver*> observers; // List to store observers

public:
    Character(int level) : level(level)
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

    void attachObserver(ICharacterObserver *observer) {
        observers.push_back(observer);
    }

    void detachObserver(ICharacterObserver *observer) {
        observers.remove(observer);
    }

    void notifyObservers() {
        for (auto observer : observers) {
            observer->onCharacterUpdate(this);
        }
    }

    void equipItem(Item *item, int slot) {
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

    void displayCharacter()
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

    std::vector<int> getAbilityScores() const {
        return std::vector<int>(abilityScores, abilityScores + 6);
    }

    int getHitPoints(){
        return hitPoints;
    }

    int getArmorClass(){
        return armorClass;
    }

    int getAttackBonus(){
        return attackBonus;
    }
};

// The observer reacts to changes in the subject
class CharacterObserver : public ICharacterObserver {
public:
    void onCharacterUpdate(Character *character) override {
        // Re-display character view
        cout << "\nCharacter View Updated:\n";
        character->displayCharacter();
    }
};

//Character Testing Method
void testCharacter() {
    Character testSubjectCharacter(20);
    auto scores = testSubjectCharacter.getAbilityScores();

    // Test 1: To check if the Ability Scores are within the expected range
    bool abilityScoreTestPassed = true;
    for (int score : scores) {
        if (score < 3 || score > 18) {
            abilityScoreTestPassed = false;
            break;
        }
    }
    cout << (abilityScoreTestPassed ? "Test 1: Ability score range test passed." : "Test 1: Ability score range test failed.") << endl;

    // Initial values to compare
    int initialHitPoints = testSubjectCharacter.getHitPoints();
    int initialArmorClass = testSubjectCharacter.getArmorClass();
    int initialAttackBonus = testSubjectCharacter.getAttackBonus();

    // Test 2: To check if item equipments properly change the stats
    Item sword("Sword", 5); // Sword should add 5 to the attack bonus
    testSubjectCharacter.equipItem(&sword, 2); // Equip sword in weapon slot

    Item armor("Armor", 10); // This armor should add 10 to hit points
    testSubjectCharacter.equipItem(&armor, 0); // Equip armor in armor slot

    Item shield("Shield", 3); // This shield should 3 to armor class
    testSubjectCharacter.equipItem(&shield, 1); // Equip shield in shield slot

    bool equipmentTestPassed = true;
    if (testSubjectCharacter.getHitPoints() != initialHitPoints + armor.bonus) {
        cout << "Hit points did not increase correctly after equipping armor." << endl;
        equipmentTestPassed = false;
    }
    if (testSubjectCharacter.getArmorClass() != initialArmorClass + shield.bonus) {
        cout << "Armor class did not increase correctly after equipping shield." << endl;
        equipmentTestPassed = false;
    }
    if (testSubjectCharacter.getAttackBonus() != initialAttackBonus + sword.bonus) {
        cout << "Attack bonus did not increase correctly after equipping sword." << endl;
        equipmentTestPassed = false;
    }

    cout << (equipmentTestPassed ? "Test 2: Equipment stat modification tests passed." : "Test 2: Equipment stat modification tests failed.") << endl;
}

// Observer Pattern Testing
void testObserverPattern() {
    Character myCharacter(5);
    CharacterObserver observer1;
    CharacterObserver observer2;

    // Test 1: Attaching Multiple Observers
    myCharacter.attachObserver(&observer1);
    myCharacter.attachObserver(&observer2);
    std::cout << "\nTwo observers attached. Equipping item (should update BOTH)...\n";
    myCharacter.equipItem(new Item("Iron Armor", 5), 0);
    // Replace visual inspection with checks for both observer1 and observer2

    // Test 2: Detaching One Observer
    myCharacter.detachObserver(&observer1);
    std::cout << "\nObserver 1 detached. Equipping item (should update ONLY observer2)...\n";
    myCharacter.equipItem(new Item("Helmet", 1), 5);
    // Replace visual inspection with checks for observer1 (no update) and observer 2

}

// // Driver class
// int main() {
//     cout << "\nRunning tests...\n\n";
//     testCharacter();
//     testObserverPattern();

//     cout << "\n>>>>>>>>>>>>>>>>>>> Character Creation <<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n";

//     Character fighter(20); // ex: Create a fighter with a given level
//     fighter.displayCharacter(); // Display the initial character

//     CharacterObserver observer;  // Create an observer
//     fighter.attachObserver(&observer);  // Attach observer to character

//     // Make changes that trigger updates
//     cout << "\n>>>>>>>>>>>>>>>>>>>>>>> Equip Items <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n";

//     // NOTE: equipments[0:Armor, 1:Shield, 2:Weapon, 3:Boots, 4:Ring, 5:Helmet]

//     Item sword("Sword", 2);
//     fighter.equipItem(&sword, 2);// ex: Equip sword in weapon slot
//     cout << "\nSword equipped with a Attack Bonus of 2.\n";

//     Item armor("Breastplate", 3);
//     fighter.equipItem(&armor, 0); // ex: Equip breastplate in armor slot
//     cout << "\nBreastplate equipped with a Hit Points Increase of 3.\n";

//     Item shield("Steele Shield", 1);
//     fighter.equipItem(&shield, 1); // ex: Equip steele shield in shield slot
//     cout << "\nSteele Shield equipped with a Armor Bonus of 1.\n";

//     return 0;
// }
