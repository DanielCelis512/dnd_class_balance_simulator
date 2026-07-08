#ifndef SORCERER_SPECIALS_H
#define SORCERER_SPECIALS_H

#include "../../character.h"

/////////////////////////////////////////////////////
// Metamagic
/////////////////////////////////////////////////////

bool canUseMetamagic(
    const Character& sorcerer
);

bool canUseEmpoweredSpell(
    const Character& sorcerer
);

int applyEmpoweredSpell(
    Character& sorcerer,
    int damage,
    int diceNumber,
    int diceSides,
    bool criticalHit
);

/////////////////////////////////////////////////////
// Innate Sorcery
/////////////////////////////////////////////////////

bool canUseInnateSorcery(
    const Character& sorcerer
);

void activateInnateSorcery(
    Character& sorcerer
);

void deactivateInnateSorcery(
    Character& sorcerer
);

void updateInnateSorcery(
    Character& sorcerer
);

bool isInnateSorceryActive(
    const Character& sorcerer
);

/////////////////////////////////////////////////////
// Sorcerous Burst
/////////////////////////////////////////////////////

bool canCastSorcerousBurst(
    const Character& sorcerer
);

void castSorcerousBurst(
    Character& sorcerer,
    Character& target
);

/////////////////////////////////////////////////////
// Fire Bolt
/////////////////////////////////////////////////////

bool canCastFireBolt(
    const Character& sorcerer
);

void castFireBolt(
    Character& sorcerer,
    Character& target
);

/////////////////////////////////////////////////////
// Chaos Bolt
/////////////////////////////////////////////////////

bool canCastChaosBolt(
    const Character& sorcerer
);

void castChaosBolt(
    Character& sorcerer,
    Character& target
);

/////////////////////////////////////////////////////
// Chromatic Orb
/////////////////////////////////////////////////////

bool canCastChromaticOrb(
    const Character& sorcerer
);

void castChromaticOrb(
    Character& sorcerer,
    Character& target
);

/////////////////////////////////////////////////////
// False Life
/////////////////////////////////////////////////////

bool canCastFalseLife(
    const Character& sorcerer
);

void castFalseLife(
    Character& sorcerer
);

#endif