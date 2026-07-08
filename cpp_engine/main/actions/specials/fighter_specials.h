#ifndef FIGHTER_SPECIALS_H
#define FIGHTER_SPECIALS_H

#include "../../character.h"


//==================================================
// Second Wind
//==================================================

bool canUseSecondWind(
    const Character& fighter
);

void useSecondWind(
    Character& fighter
);

//==================================================
// Action Surge
//==================================================

bool canUseActionSurge(
    const Character& fighter
);

void activateActionSurge(
    Character& fighter
);

void clearActionSurge(
    Character& fighter
);

bool hasActionSurge(
    const Character& fighter
);

#endif