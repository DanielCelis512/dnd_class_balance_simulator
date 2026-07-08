#include "cleric_ai.h"

#include "specials/cleric_specials.h"

#include "../action_executor.h"

#include "../../dice.h"

namespace
{

//==================================================
// Shield Decision
//==================================================

bool shouldEquipShield(
    const Character& cleric
)
{
    //------------------------------------------
    // Opening decision
    //------------------------------------------

    if(
        cleric.statistics.actionsTaken == 0
    )
    {
        return rollDice(1,100) <= 50;
    }

    //------------------------------------------
    // Rarely switches afterwards
    //------------------------------------------

    return rollDice(1,100) <= 10;
}

//==================================================
// Healing
//==================================================

bool shouldCastCureWounds(
    const Character& cleric
)
{
    if(!canCastCureWounds(cleric))
        return false;

    return
        cleric.health.hp <=
        cleric.health.maxHp * 35 / 100;
}

bool shouldUseChannelHeal(
    const Character& cleric
)
{
    if(!canUseChannelDivinity(cleric))
        return false;

    return
        cleric.health.hp <=
        cleric.health.maxHp * 20 / 100;
}

//==================================================
// Shield of Faith
//==================================================

bool shouldCastShieldOfFaith(
    const Character& cleric
)
{
    if(!canCastShieldOfFaith(cleric))
        return false;

    if(cleric.status.shieldOfFaith)
        return false;

    return
        rollDice(1,100) <= 70;
}

//==================================================
// Guiding Bolt
//==================================================

bool shouldCastGuidingBolt(
    const Character& cleric,
    const Character& target
)
{
    (void)target;

    if(!canCastGuidingBolt(cleric))
        return false;

    return
        rollDice(1,100) <= 60;
}

//==================================================
// Toll the Dead
//==================================================

bool shouldCastTollTheDead(
    const Character& cleric
)
{
    return
        canCastTollTheDead(cleric);
}

//==================================================
// Channel Divinity Radiance
//==================================================

bool shouldUseRadiance(
    const Character& cleric,
    const Character& target
)
{
    if(!canUseChannelDivinity(cleric))
        return false;

    if(
        target.health.hp >
        target.health.maxHp / 2
    )
    {
        return false;
    }

    return
        rollDice(1,100) <= 40;
}

//==================================================
// Bonus Action
//==================================================

void chooseBonusAction(
    Character& cleric
)
{
    //------------------------------------------
    // Shield of Faith
    //------------------------------------------

    if(
        shouldCastShieldOfFaith(cleric)
    )
    {
        castShieldOfFaith(cleric);
        return;
    }

    //------------------------------------------
    // Shield
    //------------------------------------------

    if(
        shouldEquipShield(cleric)
    )
    {
        equipShield(cleric);
    }
    else
    {
        unequipShield(cleric);
    }
}

//==================================================
// Main Action
//==================================================

void performMainAction(
    Character& cleric,
    Character& target
)
{
    //------------------------------------------
    // Emergency Heal
    //------------------------------------------

    if(
        shouldCastCureWounds(cleric)
    )
    {
        castCureWounds(cleric);
        return;
    }

    //------------------------------------------
    // Channel Heal
    //------------------------------------------

    if(
        shouldUseChannelHeal(cleric)
    )
    {
        useChannelDivinityHeal(cleric);
        return;
    }

    //------------------------------------------
    // Guiding Bolt
    //------------------------------------------

    if(
        shouldCastGuidingBolt(
            cleric,
            target
        )
    )
    {
        castGuidingBolt(
            cleric,
            target
        );
        return;
    }

    //------------------------------------------
    // Toll the Dead
    //------------------------------------------

    if(
        shouldCastTollTheDead(
            cleric
        )
    )
    {
        castTollTheDead(
            cleric,
            target
        );
        return;
    }

    //------------------------------------------
    // Channel Radiance
    //------------------------------------------

    if(
        shouldUseRadiance(
            cleric,
            target
        )
    )
    {
        useChannelDivinityRadiance(
            cleric,
            target
        );
        return;
    }

    //------------------------------------------
    // Physical Attack
    //------------------------------------------

    executePhysicalAttack(
        cleric,
        target
    );
}

void finishTurn(
    Character& cleric
)
{
    cleric.statistics.recentCriticalHits = 0;
}

} // namespace

//==================================================
// Cleric AI
//==================================================

void clericTurnAI(
    Character& cleric,
    Character& target
)
{
    //------------------------------------------
    // Start Turn
    //------------------------------------------

    updateShieldOfFaith(
        cleric
    );

    //------------------------------------------
    // Bonus Action
    //------------------------------------------

    chooseBonusAction(
        cleric
    );

    //------------------------------------------
    // Main Action
    //------------------------------------------

    performMainAction(
        cleric,
        target
    );

    //------------------------------------------
    // End Turn
    //------------------------------------------

    finishTurn(
        cleric
    );
}