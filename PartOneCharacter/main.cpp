#include "Character.h"
#include "Tests.h"
#include <iostream>

using namespace std;

// Driver class
int main() {
    cout << "\nRunning tests...\n\n";
    testCharacter();
    testObserverPattern();

    cout << "\n>>>>>>>>>>>>>>>>>>> Character Creation <<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n";

    Character fighter(20); // ex: Create a fighter with a given level
    fighter.displayCharacter(); // Display the initial character

    CharacterObserver observer;  // Create an observer
    fighter.attachObserver(&observer);  // Attach observer to character

    // Make changes that trigger updates
    cout << "\n>>>>>>>>>>>>>>>>>>>>>>> Equip Items <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n";

    // NOTE: equipments[0:Armor, 1:Shield, 2:Weapon, 3:Boots, 4:Ring, 5:Helmet]

    Item sword("Sword", 2);
    fighter.equipItem(&sword, 2);// ex: Equip sword in weapon slot
    cout << "\nSword equipped with a Attack Bonus of 2.\n";

    Item armor("Breastplate", 3);
    fighter.equipItem(&armor, 0); // ex: Equip breastplate in armor slot
    cout << "\nBreastplate equipped with a Hit Points Increase of 3.\n";

    Item shield("Steele Shield", 1);
    fighter.equipItem(&shield, 1); // ex: Equip steele shield in shield slot
    cout << "\nSteele Shield equipped with a Armor Bonus of 1.\n";

    return 0;
}