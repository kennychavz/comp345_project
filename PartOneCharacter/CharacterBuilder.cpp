#include "CharacterBuilder.h"

void BullyBuilder::build(Character* character)  {
    character->type = "Bully";
    character->skill_description = "Uses brute strength to destroy his enemies";
    assignAbilityScores(character);
}

void BullyBuilder::assignAbilityScores(Character* character) {
    // Sort the ability scores in descending order
    std::sort(character->abilityScores, character->abilityScores + 6, std::greater<int>());

    // Prioritize STR, CON, DEX for the Bully
    // Since the default Character follows this pattern, no change needed after the sort.

    // Recalculate modifiers based on assigned scores
    for (int i = 0; i < 6; i++) {
        character->abilityModifiers[i] = (character->abilityScores[i] - 10) / 2;
    }
}

void NimbleBuilder::build(Character* character){
    character->type = "Nimble";
    character->skill_description = "Favors dexterity and better armor class to evade blows";
    assignAbilityScores(character);
}

void NimbleBuilder::assignAbilityScores(Character* character) {
    // Sort the ability scores in descending order
    std::sort(character->abilityScores, character->abilityScores + 6, std::greater<int>());

    // Prioritize DEX, CON, STR for the Nimble character
    int tempDex = character->abilityScores[2];
    character->abilityScores[2] = character->abilityScores[0];
    character->abilityScores[0] = tempDex; //Just replaced STR and DEX.

    // Recalculate modifiers
    for (int i = 0; i < 6; i++) {
        character->abilityModifiers[i] = (character->abilityScores[i] - 10) / 2;
    }
}

void TankBuilder::build(Character* character) {
    character->type = "Tank";
    character->skill_description = "Favors survival by more hit points through a high constitution score";
    assignAbilityScores(character);
}

void TankBuilder::assignAbilityScores(Character* character) {
    // Sort the ability scores in descending order
    std::sort(character->abilityScores, character->abilityScores + 6, std::greater<int>());

    // Prioritize CON, STR, DEX for the Tank
    int tempCon = character->abilityScores[2];
    character->abilityScores[1] = character->abilityScores[0];
    character->abilityScores[0] = tempCon; //Just replaced STR and CON.

    // Recalculate modifiers
    for (int i = 0; i < 6; i++) {
        character->abilityModifiers[i] = (character->abilityScores[i] - 10) / 2;
    }
}
