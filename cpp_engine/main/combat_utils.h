#ifndef COMBAT_UTILS_H
#define COMBAT_UTILS_H

#include "character.h"
#include "combat_rules.h"

//==================================================
// Damage Profile
//==================================================

bool hasResistance(
    const Character& character,
    DamageType type
);

bool hasImmunity(
    const Character& character,
    DamageType type
);

bool hasVulnerability(
    const Character& character,
    DamageType type
);

//==================================================
// HP
//==================================================

void applyDamage(
    Character& character,
    int damage
);

void healCharacter(
    Character& character,
    int healing
);

//==================================================
// Spell Slots
//==================================================

void consumeSpellSlot(
    Character& character,
    SpellLevel level
);

//==================================================
// Special Abilities
//==================================================

bool useSpecial(
    Character& character,
    SpecialType type
);

//==================================================
// Equipment
//==================================================

void equipShield(
    Character& character
);

void unequipShield(
    Character& character
);

bool isShieldEquipped(
    const Character& character
);

void toggleShield(
    Character& fighter
);

/////////////////////////////////////////////////////
// Damage
/////////////////////////////////////////////////////

void dealDamage(
    Character& attacker,
    Character& target,
    int damage,
    DamageType damageType
);

/////////////////////////////////////////////////////
// Healing
/////////////////////////////////////////////////////

void dealHealing(
    Character& healer,
    Character& target,
    int healing
);

/////////////////////////////////////////////////////
// Temporary HP
/////////////////////////////////////////////////////

void giveTemporaryHP(
    Character& target,
    int amount
);

#endif