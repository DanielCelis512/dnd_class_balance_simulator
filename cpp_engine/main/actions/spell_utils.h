#ifndef SPELL_UTILS_H
#define SPELL_UTILS_H

#include "../character.h"

/////////////////////////////////////////////////////
// Spell Slots
/////////////////////////////////////////////////////

bool hasSpellSlot(
    const Character& caster,
    SpellLevel level
);

void restoreSpellSlots(
    Character& caster
);

/////////////////////////////////////////////////////
// Search
/////////////////////////////////////////////////////

MagicalAction* findSpell(
    Character& caster,
    const std::string& name
);

const MagicalAction* findSpell(
    const Character& caster,
    const std::string& name
);

MagicalAction* findCantrip(
    Character& caster,
    const std::string& name
);

const MagicalAction* findCantrip(
    const Character& caster,
    const std::string& name
);

/////////////////////////////////////////////////////
// Casting
/////////////////////////////////////////////////////

bool canCastSpell(
    const Character& caster,
    const MagicalAction& spell
);

bool castSpell(
    Character& caster,
    const MagicalAction& spell
);

/////////////////////////////////////////////////////
// Spell Math
/////////////////////////////////////////////////////

int getSpellSaveDC(
    const Character& caster
);

int getSpellAttackBonus(
    const Character& caster
);

/////////////////////////////////////////////////////
// Concentration
/////////////////////////////////////////////////////

bool canConcentrate(
    const Character& caster
);

void beginConcentration(
    Character& caster,
    int rounds
);

void endConcentration(
    Character& caster
);

void updateConcentration(
    Character& caster
);

#endif