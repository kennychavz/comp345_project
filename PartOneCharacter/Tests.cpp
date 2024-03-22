#include "Tests.h"
#include <iostream>

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