#ifndef SPELL_EFFECTS_H
#define SPELL_EFFECTS_H

#include "../character.h"
#include "../combat_rules.h"

/////////////////////////////////////////////////////
// Spell Effects
/////////////////////////////////////////////////////

void applySpellEffect(
    Character& caster,
    Character& target,
    const MagicalAction& spell,
    AttackResolution& result
);

#endif