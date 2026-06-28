#ifndef ACTIONS_H
#define ACTIONS_H

#include "character.h"

// Physical attacks
bool attack(
    Character& attacker,
    Character& defender
);

// Spell attacks vs AC
bool magicAttack(
    Character& caster,
    Character& target
);

// Saving throw spells
bool savingThrowAttack(
    Character& caster,
    Character& target,
    int saveModifier
);

// Cantrip attacks vs AC
bool cantripAttack(
    Character& caster,
    Character& target
);

// Fuction to get the modifier for Saving Throws
int getSaveModifier(
    Character& target,
    SaveType type
);

// Function to update the Status Effects
void updateStatusEffects(
    Character& character
);

// Cantrip attacks vs saving throw
bool cantripSavingThrow(
    Character& caster,
    Character& target,
    int saveModifier
);

// Healing
bool heal(
    Character& healer,
    Character& target
);

// Special abilities
bool useSpecial(
    Character& user,
    Character& target
);

// Utility functions
void applyDamage(
    Character& target,
    int damage
);

// Function Restore Health
void restoreHealth(
    Character& target,
    int amount
);

// Dice helpers
int rollD20(
    Character& character
);

enum class SaveResult
{
    CriticalFailure,
    Failure,
    Success,
    CriticalSuccess
};

SaveResult savingThrow(
    int modifier,
    int dc
);

#endif