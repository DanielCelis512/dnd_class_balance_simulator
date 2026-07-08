#ifndef CLASS_FACTORY_UTILS_H
#define CLASS_FACTORY_UTILS_H

#include "character.h"

#include <string>

//==================================================
// Character Initialization
//==================================================

void initializeIdentity(
    Character& character,
    const std::string& name,
    ClassType classType,
    int level = 5
);

void initializeAbilities(
    Character& character,
    int str,
    int dex,
    int con,
    int intel,
    int wis,
    int cha
);

void initializeSavingThrows(
    Character& character,
    int str,
    int dex,
    int con,
    int intel,
    int wis,
    int cha
);

void initializeHealth(
    Character& character,
    int maxHp
);

void initializeArmorClass(
    Character& character,
    int armorClass
);

void initializeInitiative(
    Character& character
);

//==================================================
// Spellcasting
//==================================================

void initializeSpellcaster(
    Character& character,
    bool canHeal,
    bool canUseCantrips
);

void initializeSpellSlots(
    Character& character,
    int level1,
    int level2,
    int level3,
    int level4,
    int level5
);

//==================================================
// Builders
//==================================================

PhysicalAction createPhysicalAction(
    const std::string& name,
    int attackBonus,
    int diceNumber,
    int diceSides,
    int modifier,
    DamageType damageType,
    RangeType range = RangeType::Melee
);

MagicalAction createSpell(
    const std::string& name,
    SpellLevel level,
    MagicType magicType,
    DamageType damageType,
    int diceNumber,
    int diceSides,
    int modifier,
    SaveType saveType,
    bool concentration = false,
    int concentrationRounds = 0,
    int incapacitatedRounds = 0,
    SpellEffectType effect = SpellEffectType::None
);

HealingAction createHealingSpell(
    const std::string& name,
    SpellLevel level,
    int diceNumber,
    int diceSides,
    int modifier
);

SpecialAction createSpecial(
    const std::string& name,
    SpecialType type,
    int uses
);

//==================================================
// Character Loaders
//==================================================

void setPhysicalAttack(
    Character& character,
    const PhysicalAction& attack
);

void addSpell(
    Character& character,
    const MagicalAction& spell
);

void addCantrip(
    Character& character,
    const MagicalAction& cantrip
);

void addHealingSpell(
    Character& character,
    const HealingAction& spell
);

void addSpecial(
    Character& character,
    const SpecialAction& special
);

SpecialAction* getSpecial(
    Character& character,
    SpecialType type
);

const SpecialAction* getSpecial(
    const Character& character,
    SpecialType type
);

//==================================================
// Damage Profile
//==================================================

void addResistance(
    Character& character,
    DamageType damageType
);

void addImmunity(
    Character& character,
    DamageType damageType
);

void addVulnerability(
    Character& character,
    DamageType damageType
);

//==================================================
// Misc
//==================================================

void enableShield(
    Character& character
);

void initializeStatistics(
    Character& character
);

#endif