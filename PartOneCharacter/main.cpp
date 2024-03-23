#include "Character.h"
#include "CharacterBuilder.h"
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

    Item sword1("Sword", 2);
    fighter.equipItem(&sword1, 2);// ex: Equip sword in weapon slot
    cout << "\nSword equipped with a Attack Bonus of 2.\n";

    Item armor("Breastplate", 3);
    fighter.equipItem(&armor, 0); // ex: Equip breastplate in armor slot
    cout << "\nBreastplate equipped with a Hit Points Increase of 3.\n";

    Item shield1("Steele Shield", 1);
    fighter.equipItem(&shield1, 1); // ex: Equip steele shield in shield slot
    cout << "\nSteele Shield equipped with a Armor Bonus of 1.\n";

    fighter.detachObserver(&observer);

    cout << "\n\n>>>>>>>>>>>>>> Testing after the CharacterBuilder update! <<<<<<<<<<<<<<\n\n";

    BullyBuilder bullyBuilder;
    Character* myBully = new Character(1);
    myBully->setBuilder(&bullyBuilder);

    myBully->attachObserver(&observer);

    myBully->displayCharacter();

    Item sword2("Sword", 2);
    myBully->equipItem(&sword2, 2);

    myBully->levelUp();

    myBully->detachObserver(&observer);

    // <><><><><><><><> NIMBLE BUILDER <><><><><><><><>

    NimbleBuilder nimbleBuilder;
    Character* myNimble = new Character(17);
    myNimble->setBuilder(&nimbleBuilder);

    myNimble->attachObserver(&observer);

    Item sword3("Sword", 5);
    myNimble->equipItem(&sword3, 2);

    Item shield2("Steele Shield", 1);
    myNimble->equipItem(&shield2, 2);

    for (int i = 0; i < 10; i++){
        myNimble->levelUp();
    }

    myNimble->detachObserver(&observer);

    return 0;
}