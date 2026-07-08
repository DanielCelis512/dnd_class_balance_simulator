#ifndef COMBAT_ACTIONS_H
#define COMBAT_ACTIONS_H

#include "character.h"

#include <vector>

//==================================================
// Action Category
//==================================================

enum class CombatActionType
{
    Physical,
    Spell,
    Cantrip,
    Healing,
    Special,
    None
};

//==================================================
// Combat Action
//==================================================

struct CombatAction
{
    CombatActionType type =
        CombatActionType::None;

    int index = -1;
};

//==================================================
// Queries
//==================================================

std::vector<CombatAction> getAvailableActions(
    const Character& character
);

bool canUsePhysicalAttack(
    const Character& character
);

bool canCastSpell(
    const Character& character
);

bool canCastCantrip(
    const Character& character
);

bool canCastHealingSpell(
    const Character& character
);

bool canUseSpecial(
    const Character& character
);

//==================================================
// Accessors
//==================================================

const PhysicalAction& getPhysicalAttack(
    const Character& character
);

const MagicalAction& getSpell(
    const Character& character,
    int index
);

const MagicalAction& getCantrip(
    const Character& character,
    int index
);

const HealingAction& getHealingSpell(
    const Character& character,
    int index
);

const SpecialAction& getSpecial(
    const Character& character,
    int index
);

bool hasSpellSlot(
    const Character& character,
    SpellLevel level
);

SpecialAction* findSpecial(
    Character& character,
    SpecialType type
);

const SpecialAction* findSpecial(
    const Character& character,
    SpecialType type
);

bool executeSpellAttack(
    Character& caster,
    Character& target,
    const MagicalAction& spell
);

bool executeSavingThrowSpell(
    Character& caster,
    Character& target,
    const MagicalAction& spell
);

bool executeHealingSpell(
    Character& caster,
    Character& target,
    const HealingAction& spell
);

bool executeBuffSpell(
    Character& caster,
    const MagicalAction& spell
);

bool executeConstrict(
    Character& attacker,
    Character& target
);

#endif