#ifndef COMBAT_MODIFIERS_H
#define COMBAT_MODIFIERS_H

#include "character.h"

/////////////////////////////////////////////////////
// Attack Rolls
/////////////////////////////////////////////////////

int modifyAttackRoll(
    Character& attacker,
    Character& defender,
    int attackTotal
);

int modifySpellAttackRoll(
    Character& caster,
    Character& target,
    int attackTotal
);

/////////////////////////////////////////////////////
// Damage
/////////////////////////////////////////////////////

int modifyDamageRoll(
    Character& attacker,
    Character& defender,
    int damage
);

int modifySpellDamage(
    Character& caster,
    Character& target,
    int damage
);

/////////////////////////////////////////////////////
// Saving Throws
/////////////////////////////////////////////////////

bool modifySavingThrowResult(
    Character& caster,
    Character& target,
    int saveRoll,
    int spellDC
);

#endif