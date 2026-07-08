#ifndef WIZARD_SPECIALS_H
#define WIZARD_SPECIALS_H

#include "../../character.h"

/////////////////////////////////////////////////////
// Arcane Recovery
/////////////////////////////////////////////////////

bool canUseArcaneRecovery(
    const Character& wizard
);

void useArcaneRecovery(
    Character& wizard
);

/////////////////////////////////////////////////////
// Portent
/////////////////////////////////////////////////////

bool canUsePortent18(
    const Character& wizard
);

bool canUsePortent5(
    const Character& wizard
);

void usePortent18(
    Character& wizard
);

void usePortent5(
    Character& wizard
);

/////////////////////////////////////////////////////
// Poison Spray
/////////////////////////////////////////////////////

bool canCastPoisonSpray(
    const Character& wizard
);

void castPoisonSpray(
    Character& wizard,
    Character& target
);

/////////////////////////////////////////////////////
// Magic Missile
/////////////////////////////////////////////////////

bool canCastMagicMissile(
    const Character& wizard
);

void castMagicMissile(
    Character& wizard,
    Character& target
);

/////////////////////////////////////////////////////
// Arcane Vigor
/////////////////////////////////////////////////////

bool canCastArcaneVigor(
    const Character& wizard
);

void castArcaneVigor(
    Character& wizard
);

/////////////////////////////////////////////////////
// Tasha's Hideous Laughter
/////////////////////////////////////////////////////

bool canCastTashas(
    const Character& wizard
);

void castTashas(
    Character& wizard,
    Character& target
);

/////////////////////////////////////////////////////
// Chromatic Orb
/////////////////////////////////////////////////////

bool canCastChromaticOrb(
    const Character& wizard
);

void castChromaticOrb(
    Character& wizard,
    Character& target
);

/////////////////////////////////////////////////////
// False Life
/////////////////////////////////////////////////////

bool canCastFalseLife(
    const Character& wizard
);

void castFalseLife(
    Character& wizard
);

#endif