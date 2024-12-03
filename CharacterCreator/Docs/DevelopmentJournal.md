
# Character Creator

**Advanced Programming**

**Dmitrii Kolchin**  
**2220982**

## Initial Research

For this project, I aimed to:
1. Implement the required functionality to explore the **Decorator** design pattern [(Decorator, n.d.)](https://refactoring.guru/design-patterns/decorator).
2. Gain additional hands-on experience with the **Factory Method** pattern [(Factory Method, n.d.)](https://refactoring.guru/design-patterns/factory-method).

These objectives allowed me to deepen my understanding of object-oriented design principles and apply them effectively to a practical use case.

---

## Implementation

### Encapsulating Character Stats

To manage character attributes effectively, I encapsulated them in a dedicated `CharacterStats` structure. This approach simplifies attribute manipulation and reduces duplication. The `+` operator was overridden to facilitate easy addition of stats, which is particularly useful for stacking modifiers introduced by decorators.

```cpp
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
```
*Figure 1. `CharacterStats` structure implementation*

### Character Base Class

The `Character` class serves as the foundation for all characters. It encapsulates key properties, such as `name`, `characterClass`, and `characterStats`, while also providing a virtual `PrintCharacterInfo()` method for polymorphic behaviour. 

```cpp
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
```
*Figure 2. `Character` class implementation*

### Factory Pattern

To streamline character creation and manage default stats for various classes, I implemented the **Factory Method** pattern. 
The `CreateCharacter()` method centralises the logic, leveraging a map for default stats, 
which makes the implementation extendable and maintainable. This design was inspired by "Code Complete" (McConnell, 2004:414) .

```cpp
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
```
*Figure 3. `CreateCharacter()` function implementation*

### Decorator Pattern

To dynamically modify character attributes, I implemented the **Decorator** pattern. Each decorator layer wraps a `Character` object and applies stat modifications to the `characterStats` field. Since stats are updated directly, the base `PrintCharacterInfo()` function remains unchanged.

```cpp
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
```
*Figure 4. `CharacterDecorator` class implementation*

### Example Usage

Equipping items using decorators becomes straightforward with this design:

```cpp
    // Task for student: Create a character using the factory and apply decorators
    Character* warrior = CharacterFactory::CreateCharacter("Warrior", CharacterClass::Warrior);
    warrior->PrintCharacterInfo();
    
    CharacterDecorator* SwordedWarrior = new CharacterDecorator(warrior, CharacterStats{ 5, 0, 0, 0, 0, 0, 0 });
    SwordedWarrior->PrintCharacterInfo();
    
    CharacterDecorator* ArmoredSwordedWarrior = new CharacterDecorator(SwordedWarrior, CharacterStats{ 0, 0, 5, 0, 0, 0, 0 });
    ArmoredSwordedWarrior->PrintCharacterInfo();
```


Source code could be accessed [here](https://github.com/DmitryKolchin/AdvancedProgramming2024/tree/main/CharacterCreator/CharacterCreator)

---

## Critical Reflection

### What Went Well
- Successfully implemented and gained practical experience with the **Decorator** and **Factory Method** patterns.
- Simplified character stat manipulation using encapsulation and operator overloading.

### Areas for Improvement
- Considered implementing the **Strategy** pattern [(Strategy, n.d.)](https://refactoring.guru/design-patterns/strategy), which might better fit the context by decoupling character behaviour from classes. 

## Bibliography
- Decorator (s.d.) At: https://refactoring.guru/design-patterns/decorator (Accessed  03/12/2024).
- Factory Method (s.d.) At: https://refactoring.guru/design-patterns/factory-method (Accessed  03/12/2024).
- Mcconell, S. (2004) Code Complete: A Practical Handbook of Software Construction. (2nd edition) (s.l.): Microsoft Press US.
- Strategy (s.d.) At: https://refactoring.guru/design-patterns/strategy (Accessed  03/12/2024).

## Declared Assets

Assets made with AI:

- DevelopmentJournal.md

