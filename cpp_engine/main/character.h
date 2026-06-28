#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

// =====================================================
// Character Classes
// =====================================================

enum class ClassType
{
    Barbarian,
    Bard,
    Cleric,
    Druid,
    Fighter,
    Monk,
    Paladin,
    Ranger,
    Rogue,
    Sorcerer,
    Warlock,
    Wizard
};

// =====================================================
// Available Actions
// =====================================================

enum class ActionType
{
    Attack,
    Magic,
    Cantrip,
    Heal,
    Special,
    EquipShield,
    UnequipShield
};

// =====================================================
// Saving Throw Types
// =====================================================

enum class SaveType
{
    Strength,
    Dexterity,
    Constitution,
    Intelligence,
    Wisdom,
    Charisma
};

// =====================================================
// Magic Resolution Types
// =====================================================

enum class MagicType
{
    AttackRoll,
    SavingThrow,
    Automatic
};

// =====================================================
// Druid Forms
// =====================================================

enum class WildShapeForm
{
    None,
    Wolf,
    Snake
};

struct Character
{
    // =====================================================
    // Identity
    // =====================================================

    std::string name;

    ClassType classType;

    // =====================================================
    // AI / Decision Making
    // =====================================================

    ActionType preferredAction;
    ActionType currentAction;

    // =====================================================
    // Ability Modifiers
    // =====================================================

    int str;
    int dex;
    int con;
    int intel;
    int wis;
    int cha;

    // =====================================================
    // Saving Throws
    // =====================================================

    int strSave;
    int dexSave;
    int conSave;
    int intSave;
    int wisSave;
    int chaSave;

    // =====================================================
    // Health
    // =====================================================

    int hp;
    int maxHp;

    int tempHp;

    // =====================================================
    // Defense
    // =====================================================

    int ac;

    int bonusAc;

    int damageReduction;

    // =====================================================
    // Weapon Attack
    // =====================================================

    int attackBonus;

    int damageDiceNumber;
    int damageDiceSides;
    int damageModifier;

    // =====================================================
    // Extra Damage
    // =====================================================

    int extraDamageDiceNumber;
    int extraDamageDiceSides;
    int bonusDamage;

    // =====================================================
    // Spellcasting
    // =====================================================

    int spellDc;

    MagicType magicType;
    SaveType spellSaveType;

    int magicUses;
    int maxMagicUses;

    int magicDiceNumber;
    int magicDiceSides;
    int magicModifier;

    // =====================================================
    // Cantrips
    // =====================================================

    MagicType cantripType;
    SaveType cantripSaveType;

    int cantripDiceNumber;
    int cantripDiceSides;
    int cantripModifier;

    // =====================================================
    // Healing
    // =====================================================

    int healingUses;
    int maxHealingUses;

    int healingDiceNumber;
    int healingDiceSides;
    int healingModifier;

    // =====================================================
    // Special Abilities
    // =====================================================

    int specialUses;
    int maxSpecialUses;

    int extraAttacks;

    // =====================================================
    // General States
    // =====================================================

    bool alive;

    bool shieldEquipped;

    bool hasAdvantage;
    bool hasDisadvantage;

    // =====================================================
    // Barbarian
    // =====================================================

    bool raging;

    // =====================================================
    // Bard
    // =====================================================

    bool cuttingWordsActive;

    // =====================================================
    // Fighter
    // =====================================================

    bool actionSurgeActive;

    // =====================================================
    // Ranger
    // =====================================================

    bool favoredEnemy;

    // =====================================================
    // Monk
    // =====================================================

    bool flurryReady;

    // =====================================================
    // Rogue
    // =====================================================

    bool sneakAttackReady;

    // =====================================================
    // Warlock
    // =====================================================

    bool cursed;

    int curseDamageDiceNumber;
    int curseDamageDiceSides;

    // =====================================================
    // Druid
    // =====================================================

    bool wildShapeActive;

    WildShapeForm wildShapeForm;

    int originalAc;
    int originalAttackBonus;
    int originalDamageDiceNumber;
    int originalDamageDiceSides;
    int originalDamageModifier;
    bool originalHasAdvantage;

    // =====================================================
    // Spellcaster Flags
    // =====================================================

    bool isCaster;
    bool canHeal;
    bool canUseCantrips;

    // =====================================================
    // Temporary Effects
    // =====================================================

    int bonusAcRounds;
    int favoredEnemyRounds;
    int curseRounds;
    int wildShapeRounds;
    int rageRounds;
    int cuttingWordsRounds;
    int sneakAttackRounds;
    int empoweredSpellRounds;
};

#endif