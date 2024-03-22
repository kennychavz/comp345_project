#include <iostream>
//#include "Part1_Character.cpp"


// Step 1: Define the CharacterActionsStrategy interface or abstract class
class CharacterActionsStrategy {
public:
    virtual void attack(Character& hero, Character& villain) = 0;
    virtual void defend(Character& hero, Character& villain) = 0;
    virtual void friendly(Character& hero, Character& villain) = 0;
    virtual ~CharacterActionsStrategy() {}
};

// Step 2: Implement three concrete strategies
class HumanPlayerStrategy : public CharacterActionsStrategy {
public:
    void attack(Character& hero, Character& villain) override {
        bool res;
        int heroDmg = hero.getAttackBonus() * 0.4;
        int villainDmg = villain.getAttackBonus() * 0.4;
        // attack the villain
        res = villain.takeAttack(heroDmg);
    }
    void defend(Character& hero, Character& villain) override {

      bool res;
        int heroDmg = hero.getAttackBonus() * 0.4;
        int villainDmg = villain.getAttackBonus() * 0.4;
        // defend from villain
        res = hero.takeAttack(villainDmg);
    }
};

class AggressorStrategy : public CharacterActionsStrategy {
public:

    void attack(Character& hero, Character& villain) override {
        bool res;
        int heroDmg = hero.getAttackBonus() * 0.4;
        int villainDmg = villain.getAttackBonus() * 0.4;
        // attack the villain
        res = villain.takeAttack(heroDmg);
    }
    void defend(Character& hero, Character& villain) override {
      attack(hero, villain);
    }

    void freeActions(Character& hero, Character& villain) override {
        attack(hero, villain);
    }
};

class FriendlyStrategy : public CharacterActionsStrategy {
public:

    void attack(Character& hero, Character& villain) override {
        defend(hero, villain);
    }

    void defend(Character& hero, Character& villain) override {

        bool res;
        int heroDmg = hero.getAttackBonus() * 0.4;
        int villainDmg = villain.getAttackBonus() * 0.4;
        // defend from villain
        res = hero.takeAttack(villainDmg);
    }
};

// Step 3: Implement the Character class
class Character {
private:
    CharacterActionsStrategy* actionsStrategy;

public:
    Character(CharacterActionsStrategy* strategy) : actionsStrategy(strategy) {}

    void performActions() {
        actionsStrategy->move();
        actionsStrategy->attack();
        actionsStrategy->freeActions();
    }
};

// Usage
int main() {
    HumanPlayerStrategy humanStrategy;
    AggressorStrategy aggressorStrategy;
    FriendlyStrategy friendlyStrategy;

    Character humanCharacter(&humanStrategy);
    humanCharacter.performActions();

    Character aggressorCharacter(&aggressorStrategy);
    aggressorCharacter.performActions();

    Character friendlyCharacter(&friendlyStrategy);
    friendlyCharacter.performActions();

    return 0;
}
