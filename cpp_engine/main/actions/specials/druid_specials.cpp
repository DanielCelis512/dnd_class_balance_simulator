#include "druid_specials.h"

#include "../../combat_actions.h"
#include "../../combat_utils.h"
#include "../../combat/combat_statistics.h"
#include "../../dice.h"

#include "../spell_utils.h"
#include "../saving_throw.h"

/////////////////////////////////////////////////////
// Wild Shape
/////////////////////////////////////////////////////

bool canUseWildShape(
    const Character& druid
)
{
    if(!druid.health.alive)
        return false;

    if(isWildShaped(druid))
        return false;

    const SpecialAction* wildShape =
        findSpecial(
            druid,
            SpecialType::WildShape
        );

    if(wildShape == nullptr)
        return false;

    return wildShape->currentUses > 0;
}

void activateWolfForm(
    Character& druid
)
{
    if(!canUseWildShape(druid))
        return;

    SpecialAction* wildShape =
        findSpecial(
            druid,
            SpecialType::WildShape
        );

    if(wildShape == nullptr)
        return;

    wildShape->currentUses--;

    //------------------------------------------
    // Save original values
    //------------------------------------------

    druid.wildShape.originalAc =
        druid.ac;

    druid.wildShape.originalAttack =
        druid.physical;

    //------------------------------------------
    // Form
    //------------------------------------------

    druid.status.wildShapeActive = true;

    druid.status.wildShapeForm =
        WildShapeForm::Wolf;

    druid.health.tempHp = 11;

    druid.ac = 12 + druid.bonusAc;

    //------------------------------------------
    // Wolf Bite
    //------------------------------------------

    druid.physical.name = "Bite";

    druid.physical.attackBonus = 4;

    druid.physical.damageDiceNumber = 1;

    druid.physical.damageDiceSides = 6;

    druid.physical.damageModifier = 2;

    druid.physical.damageType =
        DamageType::Piercing;

    registerWildShape(
        druid.statistics
    );
}

void activateSnakeForm(
    Character& druid
)
{
    if(!canUseWildShape(druid))
        return;

    SpecialAction* wildShape =
        findSpecial(
            druid,
            SpecialType::WildShape
        );

    if(wildShape == nullptr)
        return;

    wildShape->currentUses--;

    //------------------------------------------
    // Save original values
    //------------------------------------------

    druid.wildShape.originalAc =
        druid.ac;

    druid.wildShape.originalAttack =
        druid.physical;

    //------------------------------------------
    // Form
    //------------------------------------------

    druid.status.wildShapeActive = true;

    druid.status.wildShapeForm =
        WildShapeForm::ConstrictorSnake;

    druid.health.tempHp = 13;

    druid.ac = 13 + druid.bonusAc;

    //------------------------------------------
    // Snake Bite
    //------------------------------------------

    druid.physical.name = "Bite";

    druid.physical.attackBonus = 4;

    druid.physical.damageDiceNumber = 1;

    druid.physical.damageDiceSides = 8;

    druid.physical.damageModifier = 2;

    druid.physical.damageType =
        DamageType::Piercing;

    registerWildShape(
        druid.statistics
    );
}

void deactivateWildShape(
    Character& druid
)
{
    if(!isWildShaped(druid))
        return;

    druid.status.wildShapeActive = false;

    druid.status.wildShapeForm =
        WildShapeForm::None;

    druid.health.tempHp = 0;

    //------------------------------------------
    // Restore
    //------------------------------------------

    druid.ac =
        druid.wildShape.originalAc;

    druid.physical =
        druid.wildShape.originalAttack;
}

void updateWildShape(
    Character& druid
)
{
    if(!isWildShaped(druid))
        return;

    if(druid.health.tempHp <= 0)
    {
        deactivateWildShape(
            druid
        );
    }
}

bool isWildShaped(
    const Character& druid
)
{
    return
        druid.status.wildShapeActive &&
        druid.status.wildShapeForm != WildShapeForm::None;
}

WildShapeForm getCurrentWildShape(
    const Character& druid
)
{
    return
        druid.status.wildShapeForm;
}

/////////////////////////////////////////////////////
// Healing Word
/////////////////////////////////////////////////////

bool canCastHealingWord(
    const Character& druid
)
{
    if(!druid.health.alive)
        return false;

    if(isWildShaped(druid))
        return false;

    return hasSpellSlot(
        druid,
        SpellLevel::Level1
    );
}

void castHealingWord(
    Character& druid
)
{
    if(!canCastHealingWord(druid))
        return;

    const MagicalAction* spell =
        findSpell(
            druid,
            "Healing Word"
        );
    
    if(
        spell == nullptr ||
        !castSpell(druid,*spell)
    )
    {
        return;
    }

    int healing =
        rollDice(2,4)
        +
        druid.abilities.wis;

    healCharacter(
        druid,
        healing
    );

    registerHealing(
        druid.statistics,
        druid.statistics,
        healing
    );
}

/////////////////////////////////////////////////////
// Cure Wounds
/////////////////////////////////////////////////////

bool canCastCureWounds(
    const Character& druid
)
{
    if(!druid.health.alive)
        return false;

    if(isWildShaped(druid))
        return false;

    if(druid.status.shieldEquipped)
        return false;

    return hasSpellSlot(
        druid,
        SpellLevel::Level1
    );
}

void castCureWounds(
    Character& druid
)
{
    if(!canCastCureWounds(druid))
        return;

    const MagicalAction* spell =
        findSpell(
            druid,
            "Cure Wounds"
        );

    if(
        spell == nullptr ||
        !castSpell(druid,*spell)
    )
    {
        return;
    }

    int healing =
        rollDice(2,8)
        +
        druid.abilities.wis;

    healCharacter(
        druid,
        healing
    );

    registerHealing(
        druid.statistics,
        druid.statistics,
        healing
    );
}

/////////////////////////////////////////////////////
// Thunderwave
/////////////////////////////////////////////////////

bool canCastThunderwave(
    const Character& druid
)
{
    if(!druid.health.alive)
        return false;

    if(isWildShaped(druid))
        return false;

    if(druid.status.shieldEquipped)
        return false;

    return hasSpellSlot(
        druid,
        SpellLevel::Level1
    );
}

void castThunderwave(
    Character& druid,
    Character& target
)
{
    if(!canCastThunderwave(druid))
        return;

    const MagicalAction* spell =
        findSpell(
            druid,
            "Thunderwave"
        );

    if(
        spell == nullptr ||
        !castSpell(druid,*spell)
    )
    {
        return;
    }

    bool saved =
        performSavingThrow(
            druid,
            target,
            SaveType::Constitution
        );

    if(saved)
    {
        dealDamage(
            druid,
            target,
            rollDice(2,8) / 2,
            DamageType::Thunder
        );
    }
    else
    {
        dealDamage(
            druid,
            target,
            rollDice(2,8),
            DamageType::Thunder
        );
    }
}

/////////////////////////////////////////////////////
// Entangle
/////////////////////////////////////////////////////

bool canCastEntangle(
    const Character& druid
)
{
    if(!druid.health.alive)
        return false;

    if(isWildShaped(druid))
        return false;

    if(druid.status.concentrating)
        return false;

    return hasSpellSlot(
        druid,
        SpellLevel::Level1
    );
}

void castEntangle(
    Character& druid,
    Character& target
)
{
    if(!canCastEntangle(druid))
        return;

    const MagicalAction* spell =
        findSpell(
            druid,
            "Entangle"
        );

    if(
        spell == nullptr ||
        !castSpell(druid,*spell)
    )
    {
        return;
    }

    druid.status.concentrating = true;
    druid.timers.concentrationRounds = 3;

    bool saved =
        performSavingThrow(
            druid,
            target,
            SaveType::Strength
        );

    if(!saved)
    {
        target.status.restrained = true;
    }
}

/////////////////////////////////////////////////////
// Shillelagh
/////////////////////////////////////////////////////

bool canCastShillelagh(
    const Character& druid
)
{
    if(!druid.health.alive)
        return false;

    if(isWildShaped(druid))
        return false;

    if(druid.status.shieldEquipped)
        return false;

    return !druid.status.shillelaghActive;
}

void castShillelagh(
    Character& druid
)
{
    if(!canCastShillelagh(druid))
        return;

    druid.status.shillelaghActive = true;

    druid.timers.shillelaghRounds = 10;

    druid.physical.attackBonus =
        druid.abilities.wis +
        druid.proficiencyBonus;

    druid.physical.damageModifier =
        druid.abilities.wis;

    druid.physical.damageDiceSides = 8;

    druid.physical.damageType =
        DamageType::Force;
}

void removeShillelagh(
    Character& druid
)
{
    if(!druid.status.shillelaghActive)
        return;

    druid.status.shillelaghActive = false;

    druid.timers.shillelaghRounds = 0;

    druid.physical.attackBonus =
        druid.abilities.str +
        druid.proficiencyBonus;

    druid.physical.damageModifier =
        druid.abilities.str;

    if(druid.status.shieldEquipped)
    {
        druid.physical.damageDiceSides =
            druid.physical.oneHandedDiceSides;
    }
    else
    {
        druid.physical.damageDiceSides =
            druid.physical.twoHandedDiceSides;
    }

    druid.physical.damageType =
        DamageType::Bludgeoning;
}

void updateShillelagh(
    Character& druid
)
{
    if(!druid.status.shillelaghActive)
        return;

    druid.timers.shillelaghRounds--;

    if(
        druid.timers.shillelaghRounds <= 0
    )
    {
        removeShillelagh(
            druid
        );
    }
}