#ifndef AI_UTILS_H
#define AI_UTILS_H

#include "character.h"

//==================================================
// Resources
//==================================================

bool hasMagic(const Character& character);
bool hasHealing(const Character& character);
bool hasSpecial(const Character& character);

//==================================================
// Health
//==================================================

bool isHealthy(const Character& character);
bool isInjured(const Character& character);
bool isCritical(const Character& character);

double healthPercentage(const Character& character);

//==================================================
// Action availability
//==================================================

bool canUseMagic(const Character& character);
bool canUseCantrip(const Character& character);
bool canHealSelf(const Character& character);
bool canUseSpecial(const Character& character);

//==================================================
// Combat estimation
//==================================================

int estimatePhysicalDamage(
    const Character& character
);

int estimateMagicDamage(
    const Character& character
);

int estimateCantripDamage(
    const Character& character
);

int estimateHealing(
    const Character& character
);

//==================================================
// Enemy evaluation
//==================================================

bool enemyIsWeak(
    const Character& enemy
);

bool enemyIsNearDeath(
    const Character& enemy
);

//==================================================
// Spell information
//==================================================

bool spellUsesAttackRoll(
    const Character& character
);

bool spellUsesSavingThrow(
    const Character& character
);

bool cantripUsesAttackRoll(
    const Character& character
);

bool cantripUsesSavingThrow(
    const Character& character
);

#endif