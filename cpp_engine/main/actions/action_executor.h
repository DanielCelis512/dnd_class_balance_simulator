#ifndef ACTION_EXECUTOR_H
#define ACTION_EXECUTOR_H

#include "character.h"
#include "combat_rules.h"

//==================================================
// Physical
//==================================================

AttackResolution executePhysicalAttack(
    Character& attacker,
    Character& defender
);

//==================================================
// Magic
//==================================================

AttackResolution executeSpell(
    Character& caster,
    Character& target,
    int spellIndex
);

AttackResolution executeCantrip(
    Character& caster,
    Character& target,
    int cantripIndex
);

//==================================================
// Specials
//==================================================

void executeSpecial(
    Character& user,
    Character& target,
    int specialIndex
);

#endif