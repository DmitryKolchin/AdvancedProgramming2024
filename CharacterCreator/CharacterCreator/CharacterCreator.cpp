#include <iostream>
#include <map>
#include <string>

// Define the character classes
enum class CharacterClass
{
    Warrior,
    Rogue,
    Mage,
    Wizard,
    Ranger,
    Monk,
    Bard,
    Paladin,
    Cleric
};

struct CharacterStats
{
    int strength, agility, endurance, intelligence, willpower, speed, luck;

    CharacterStats() :
        strength( 5 ), agility( 5 ), endurance( 5 ), intelligence( 5 ), willpower( 5 ), speed( 5 ), luck( 5 )
    {
    }

    CharacterStats(int str,
                   int agi,
                   int end,
                   int intel,
                   int will,
                   int spd,
                   int lck) :
        strength( str ), agility( agi ), endurance( end ), intelligence( intel ), willpower( will ), speed( spd ), luck( lck )
    {
    }

    CharacterStats operator+(const CharacterStats& other)
    {
        return CharacterStats{
            strength + other.strength,
            agility + other.agility,
            endurance + other.endurance,
            intelligence + other.intelligence,
            willpower + other.willpower,
            speed + other.speed,
            luck + other.luck
        };
    }
};

// Character base class
class Character
{
public:
    std::string name;
    CharacterClass characterClass;
    CharacterStats characterStats;

    Character(std::string n, CharacterClass c, const CharacterStats& stats = CharacterStats())
        : name(n), characterClass(c), characterStats( stats ) {}

    virtual void PrintCharacterInfo()
    {
        std::cout << "Name: " << name << ", Class: " << static_cast<int>(characterClass) << '\n';
        std::cout << "Strength: " << characterStats.strength << ", Agility: " << characterStats.agility
            << ", Endurance: " << characterStats.endurance << ", Intelligence: " << characterStats.intelligence
            << ", Willpower: " << characterStats.willpower << ", Speed: " << characterStats.speed
            << ", Luck: " << characterStats.luck << '\n';
    }

    virtual ~Character() = default;
};

// Factory for character creation
class CharacterFactory
{

public:
    static Character* CreateCharacter(const std::string& name, CharacterClass charClass)
    {
        std::map<CharacterClass, CharacterStats> defaultStats = {
            {CharacterClass::Warrior, CharacterStats{10, 5, 8, 3, 5, 5, 3}},
            {CharacterClass::Rogue, CharacterStats{5, 10, 5, 3, 5, 8, 5}},
            {CharacterClass::Mage, CharacterStats{3, 5, 5, 10, 8, 5, 3}},
            {CharacterClass::Wizard, CharacterStats{3, 5, 5, 10, 8, 5, 3}},
            {CharacterClass::Ranger, CharacterStats{5, 8, 5, 5, 5, 8, 5}},
            {CharacterClass::Monk, CharacterStats{5, 8, 5, 5, 5, 8, 5}},
            {CharacterClass::Bard, CharacterStats{5, 5, 5, 5, 5, 5, 5}},
            {CharacterClass::Paladin, CharacterStats{8, 5, 8, 5, 5, 5, 5}},
            {CharacterClass::Cleric, CharacterStats{5, 5, 5, 8, 5, 5, 5}}
        };

        Character* character = new Character( name, charClass, defaultStats[charClass] );

        return character;
    }
};

// Decorator for adding abilities or modifiers to characters
class CharacterDecorator : public Character
{
protected:
    Character* character;

    CharacterStats statsModifications;

public:
    CharacterDecorator(Character* c, const CharacterStats& newStatsModifications) : Character(c->name, c->characterClass), character(c), statsModifications( newStatsModifications )
    {
        characterStats = character->characterStats + statsModifications;
    }
};



// Task for student: Implement a concrete decorator (e.g., EnchantedArmor, SpecialWeapon) to modify character stats

int main()
{
    // Task for student: Create a character using the factory and apply decorators
    Character* warrior = CharacterFactory::CreateCharacter("Warrior", CharacterClass::Warrior);
    warrior->PrintCharacterInfo();
    CharacterDecorator* SwordedWarrior = new CharacterDecorator(warrior, CharacterStats{ 5, 0, 0, 0, 0, 0, 0 });
    SwordedWarrior->PrintCharacterInfo();
    CharacterDecorator* ArmoredSwordedWarrior = new CharacterDecorator(SwordedWarrior, CharacterStats{ 0, 0, 5, 0, 0, 0, 0 });
    ArmoredSwordedWarrior->PrintCharacterInfo();
    return 0;
}