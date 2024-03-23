#ifndef CHARACTERBUILDER_H
#define CHARACTERBUILDER_H

#include "Character.h"

class CharacterBuilder {
public:
    virtual ~CharacterBuilder() {} // Virtual destructor

    virtual void build(Character* character) = 0;
    virtual void assignAbilityScores(Character* character) = 0;
};

class BullyBuilder : public CharacterBuilder {
public:
    void build(Character* character) override;
    void assignAbilityScores(Character* character) override;
};

class NimbleBuilder : public CharacterBuilder {
public:
    void build(Character* character) override;
    void assignAbilityScores(Character* character) override;
};

class TankBuilder : public CharacterBuilder {
public:
    void build(Character* character) override;
    void assignAbilityScores(Character* character) override;
};


#endif // CHARACTERBUILDER_H
