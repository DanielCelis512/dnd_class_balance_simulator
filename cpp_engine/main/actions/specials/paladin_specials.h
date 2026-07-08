#ifndef PALADIN_SPECIALS_H
#define PALADIN_SPECIALS_H

#include "../../character.h"

/////////////////////////////////////////////////////
// Divine Smite
/////////////////////////////////////////////////////

bool canPrepareDivineSmite(
    const Character& paladin
);

void prepareDivineSmite(
    Character& paladin
);

bool shouldTriggerDivineSmite(
    const Character& paladin
);

void consumeDivineSmite(
    Character& paladin
);

void clearDivineSmite(
    Character& paladin
);

/////////////////////////////////////////////////////
// Lay on Hands
/////////////////////////////////////////////////////

bool canUseLayOnHands(
    const Character& paladin
);

void useLayOnHands(
    Character& paladin
);

/////////////////////////////////////////////////////
// Shield of Faith
/////////////////////////////////////////////////////

bool canCastShieldOfFaith(
    const Character& paladin
);

void castShieldOfFaith(
    Character& paladin
);

void updateShieldOfFaith(
    Character& paladin
);

void removeShieldOfFaith(
    Character& paladin
);

#endif