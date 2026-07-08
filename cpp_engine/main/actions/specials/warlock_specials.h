#ifndef WARLOCK_SPECIAL_H
#define WARLOCK_SPECIAL_H

#include "character.h"

/////////////////////////////////////////////////////
// Imp
/////////////////////////////////////////////////////

bool canSummonImp(
    const Character& warlock
);

void summonImp(
    Character& warlock
);

void updateImp(
    Character& warlock
);

void removeImp(
    Character& warlock
);

bool isImpActive(
    const Character& warlock
);

/////////////////////////////////////////////////////
// Magical Cunning
/////////////////////////////////////////////////////

bool canUseMagicalCunning(
    const Character& warlock
);

void useMagicalCunning(
    Character& warlock
);

/////////////////////////////////////////////////////
// Hex
/////////////////////////////////////////////////////

bool canCastHex(
    const Character& warlock
);

void castHex(
    Character& warlock,
    Character& target
);

void updateHex(
    Character& warlock
);

void removeHex(
    Character& warlock
);

/////////////////////////////////////////////////////
// Eldritch Blast
/////////////////////////////////////////////////////

bool canCastEldritchBlast(
    const Character& warlock
);

void castEldritchBlast(
    Character& warlock,
    Character& target
);

/////////////////////////////////////////////////////
// Witch Bolt
/////////////////////////////////////////////////////

bool canCastWitchBolt(
    const Character& warlock
);

void castWitchBolt(
    Character& warlock,
    Character& target
);

#endif