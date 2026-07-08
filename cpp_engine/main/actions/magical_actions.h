#ifndef MAGICAL_ACTIONS_H
#define MAGICAL_ACTIONS_H

#include "../character.h"
#include "../combat_rules.h"

//==================================================
// Spell
//==================================================

AttackResolution resolveSpell(
    Character& caster,
    Character& target,
    int spellIndex
);

//==================================================
// Cantrip
//==================================================

AttackResolution resolveCantrip(
    Character& caster,
    Character& target,
    int cantripIndex
);

#endif