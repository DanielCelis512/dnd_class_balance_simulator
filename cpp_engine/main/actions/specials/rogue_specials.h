#ifndef ROGUE_SPECIALS_H
#define ROGUE_SPECIALS_H

#include "../../character.h"

//==================================================
// Aim
//==================================================

bool canUseAim(
    const Character& rogue
);

void useAim(
    Character& rogue
);

void clearAim(
    Character& rogue
);

//==================================================
// Dodge
//==================================================

bool canUseDodge(
    const Character& rogue
);

void useDodge(
    Character& rogue
);

void clearDodge(
    Character& rogue
);

//==================================================
// Off-Hand Attack
//==================================================

bool canUseOffHandAttack(
    const Character& rogue
);

void prepareOffHandAttack(
    Character& rogue
);

void clearOffHandAttack(
    Character& rogue
);

//==================================================
// Sneak Attack
//==================================================

bool canPrepareSneakAttack(
    const Character& rogue
);

void prepareSneakAttack(
    Character& rogue
);

bool shouldTriggerSneakAttack(
    const Character& rogue
);

void consumeSneakAttack(
    Character& rogue
);

void clearSneakAttack(
    Character& rogue
);

#endif