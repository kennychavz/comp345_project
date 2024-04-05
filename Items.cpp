#include <vector>
#include <string>

struct Enchantment
{
    std::string type;
    int bonus;

    Enchantment(std::string t = "", int b = 0) : type(t), bonus(b) {}
};

// Base class for all items
class Item
{
protected:
    std::string name;
    Enchantment enchantment;

public:
    Item(std::string name = "", Enchantment enchantment = Enchantment())
    {
        setName(name);
        setEnchantment(enchantment);
    }

    virtual ~Item() = default;

    Enchantment getEnchantment() const
    {
        return enchantment;
    }

    std::string getName() const
    {
        return name;
    }

    int getEnchantmentBonus() const
    {
        return enchantment.bonus;
    }

    void setEnchantment(const Enchantment &enchantment)
    {
        this->enchantment = enchantment;
    }

    void setName(const std::string &name)
    {
        this->name = name;
    }
};

class WornItem : public Character {

    public:
    Item* currentItem;
    WornItem(Character* character) : character(character) {}
    ~WornItem() { delete character; }

    void remove() {
        if (currentItem) {
        delete currentItem;
        currentItem = nullptr;
        }
    }
   
protected:

    Character* character;
};

// Concrete item classes
class Helmet : public WornItem {
public:
    Helmet(Character* character) : WornItem(character) {}

    int getHitPoints() {
        return character->getHitPoints()+currentItem.bonus;
    }
    
};

class Weapon : public WornItem {
public:
    Weapon(Character* character) : WornItem(character) {}

    int getAttackBonus() {

        return character->getAttackBonus()+currentItem.bonus;
    }

};

class Shield : public WornItem {
    Shield(Character* character) : WornItem(character) {}

    int getArmorClass() {
        return character->getArmorClass()+currentItem.bonus;
    }

}

class Boots : public WornItem {

    Boots(Character* character) : WornItem(character) {}

    int getAbilityScores(){
        return abilityScores[2]+currentItem.bonus;
    }
}



//class ItemContainer
//{
//    std::vector<Item *> items;
//
//public:
//    ~ItemContainer()
//    {
//        for (Item *item : items)
//        {
//            delete item;
//        }
//    }
//
//    void addItem(Item *item)
//    {
//        items.push_back(item);
//    }
//
//    Item *getItem(const std::string &name)
//    {
//        for (Item *item : items)
//        {
//            if (item->getName() == name)
//            {
//                return item;
//            }
//        }
//        return NULL;
//    }
//};

// Derived class for equipment
class Equipment : public Item
{
public:
    Equipment(std::string name, Enchantment enchantment) : Item(name, enchantment) {}

};

// Derived class for usable items
class UsableItem : public Item
{
public:
    UsableItem(std::string name, Enchantment enchantment) : Item(name, enchantment) {}

//    void use() {
//        if (name == "Healing Potion") {
//            int healAmount = enchantment.bonus;
//            character->remainingHitPoints = std::min(character->remainingHitPoints + healAmount, character->hitPoints);
//            std::cout << "Used Healing Potion! Healed for " << healAmount << " HP." << std::endl;
//        } else if(name == "Potion of Strength") {
//            character->damageBonus += enchantment.bonus;
//            std::cout << "Used Potion of Strength! Damage bonus increased by " << enchantment.bonus << std::endl;
//        } else {
//            std::cout << "Unknown usable item!" << std::endl;
//        }
//    }
};

//class Helmet : public Item
//{
//public:
//    Helmet(std::string name, Enchantment enchantment) : Item(name, enchantment) {}
//
//    std::string getType() const override
//    {
//        return "Helmet";
//    }
//};
//
//class Ring : public Item
//{
//public:
//    Ring(std::string name, Enchantment enchantment) : Item(name, enchantment) {}
//
//    std::string getType() const override
//    {
//        return "Ring";
//    }
//};
//
//class Weapon : public Item
//{
//public:
//    Weapon(std::string name, Enchantment enchantment) : Item(name, enchantment) {}
//
//    std::string getType() const override
//    {
//        return "Weapon";
//    }
//};
//
//class Shield : public Item
//{
//public:
//    Shield(std::string name, Enchantment enchantment) : Item(name, enchantment) {}
//
//    std::string getType() const override
//    {
//        return "Shield";
//    }
//};
//
//class Armor : public Item
//{
//public:
//    Armor(std::string name, Enchantment enchantment) : Item(name, enchantment) {}
//
//    std::string getType() const override
//    {
//        return "Armor";
//    }
//};
//
//class Boots : public Item
//{
//public:
//    Boots(std::string name, Enchantment enchantment) : Item(name, enchantment) {}
//
//    std::string getType() const override
//    {
//        return "Boots";
//    }
//};

//int main(int argc, char *argv[])
//{
//    ItemContainer backpack;
//
//    Helmet *helmet = new Helmet("Mystic Helmet", Enchantment("Intelligence", 3));
//    backpack.addItem(helmet);
//
//    Item *retrievedItem = backpack.getItem("Mystic Helmet");
//    if (retrievedItem)
//    {
//        std::cout << "Retrieved: " << retrievedItem->getName() << " with enchantment " << retrievedItem->getEnchantment().type << std::endl;
//    }
//}