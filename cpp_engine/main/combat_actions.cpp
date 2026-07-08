#include "combat_actions.h"


//==================================================
// Physical Attack
//==================================================

bool canUsePhysicalAttack(
    const Character&
);

const PhysicalAction&
getPhysicalAttack(
    const Character&
);

//==================================================
// Spellcasting
//==================================================

bool canCastSpell(
    const Character&
);

bool hasSpellSlot(
    const Character&,
    SpellLevel
);

const MagicalAction&
getSpell(
    const Character&,
    int
);

const MagicalAction&
getCantrip(
    const Character&,
    int
);

bool canCastHealingSpell(
    const Character&
);

const HealingAction&
getHealingSpell(
    const Character&,
    int
);

//==================================================
// Special Abilities
//==================================================

bool hasSpecialAvailable(
    const Character&,
    SpecialType
);

SpecialAction*
findSpecial(
    Character&,
    SpecialType
);

const SpecialAction*
findSpecial(
    const Character&,
    SpecialType
);

SpecialAction* findSpecial(
    Character& character,
    SpecialType type
)
{
    for(auto& special : character.specials)
    {
        if(special.type == type)
            return &special;
    }

    return nullptr;
}

const SpecialAction* findSpecial(
    const Character& character,
    SpecialType type
)
{
    for(const auto& special : character.specials)
    {
        if(special.type == type)
            return &special;
    }

    return nullptr;
}
