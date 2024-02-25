#include <iostream>
#include <vector>
#include <string>

struct Enchantment
{
    std::string type;
    int bonus;

    Enchantment(std::string t = "", int b = 0) : type(t), bonus(b) {}
};

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

    virtual ~Item() {}

    Enchantment getEnchantment() const
    {
        return enchantment;
    }

    std::string getName() const
    {
        return name;
    }

    void setEnchantment(const Enchantment &enchantment)
    {
        this->enchantment = enchantment;
    }

    void setName(const std::string &name)
    {
        this->name = name;
    }

    virtual std::string getType() const = 0;
};

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

class Helmet : public Item
{
public:
    Helmet(std::string name, Enchantment enchantment) : Item(name, enchantment) {}

    std::string getType() const override
    {
        return "Helmet";
    }
};

class Ring : public Item
{
public:
    Ring(std::string name, Enchantment enchantment) : Item(name, enchantment) {}

    std::string getType() const override
    {
        return "Ring";
    }
};

class Weapon : public Item
{
public:
    Weapon(std::string name, Enchantment enchantment) : Item(name, enchantment) {}

    std::string getType() const override
    {
        return "Weapon";
    }
};

class Shield : public Item
{
public:
    Shield(std::string name, Enchantment enchantment) : Item(name, enchantment) {}

    std::string getType() const override
    {
        return "Shield";
    }
};

class Armor : public Item
{
public:
    Armor(std::string name, Enchantment enchantment) : Item(name, enchantment) {}

    std::string getType() const override
    {
        return "Armor";
    }
};

class Boots : public Item
{
public:
    Boots(std::string name, Enchantment enchantment) : Item(name, enchantment) {}

    std::string getType() const override
    {
        return "Boots";
    }
};

int main(int argc, char *argv[])
{
    ItemContainer backpack;

    Helmet *helmet = new Helmet("Mystic Helmet", Enchantment("Intelligence", 3));
    backpack.addItem(helmet);

    Item *retrievedItem = backpack.getItem("Mystic Helmet");
    if (retrievedItem)
    {
        std::cout << "Retrieved: " << retrievedItem->getName() << " with enchantment " << retrievedItem->getEnchantment().type << std::endl;
    }
}
