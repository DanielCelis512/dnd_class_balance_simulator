#ifndef CLERIC_SPECIALS_H
#define CLERIC_SPECIALS_H

#include "../../character.h"

//==================================================
// Shield
//==================================================

void equipShield(
    Character& cleric
);

void unequipShield(
    Character& cleric
);

bool isUsingShield(
    const Character& cleric
);

//==================================================
// Guiding Bolt
//==================================================

bool canCastGuidingBolt(
    const Character& cleric
);

void castGuidingBolt(
    Character& cleric,
    Character& target
);

void applyGuidingBoltAdvantage(
    Character& target
);

void clearGuidingBoltAdvantage(
    Character& target
);

//==================================================
// Toll the Dead
//==================================================

bool canCastTollTheDead(
    const Character& cleric
);

void castTollTheDead(
    Character& cleric,
    Character& target
);

//==================================================
// Cure Wounds
//==================================================

bool canCastCureWounds(
    const Character& cleric
);

void castCureWounds(
    Character& cleric
);

//==================================================
// Shield of Faith
//==================================================

bool canCastShieldOfFaith(
    const Character& cleric
);

void castShieldOfFaith(
    Character& cleric
);

void updateShieldOfFaith(
    Character& cleric
);

void removeShieldOfFaith(
    Character& cleric
);

//==================================================
// Channel Divinity
//==================================================

bool canUseChannelDivinity(
    const Character& cleric
);

void useChannelDivinityHeal(
    Character& cleric
);

void useChannelDivinityRadiance(
    Character& cleric,
    Character& target
);

#endif