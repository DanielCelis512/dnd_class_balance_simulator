#ifndef BARBARIAN_SPECIALS_H
#define BARBARIAN_SPECIALS_H

#include "../../character.h"

//==================================================
// Rage
//==================================================

bool canActivateRage(
    const Character& barbarian
);

void activateRage(
    Character& barbarian
);

void deactivateRage(
    Character& barbarian
);

void updateRage(
    Character& barbarian
);

bool isRaging(
    const Character& barbarian
);

//==================================================
// Reckless Attack
//==================================================

bool canUseRecklessAttack(
    const Character& barbarian
);

void activateRecklessAttack(
    Character& barbarian
);

void clearRecklessAttack(
    Character& barbarian
);

bool isUsingRecklessAttack(
    const Character& barbarian
);

#endif