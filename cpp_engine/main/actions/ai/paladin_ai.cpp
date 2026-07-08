#include "paladin_ai.h"

#include "specials/paladin_specials.h"

#include "../../combat_actions.h"
#include "../../combat_utils.h"

#include "../action_executor.h"

#include "../../dice.h"

namespace
{

//==================================================
// Shield Decision
//==================================================

bool shouldEquipShield(
    const Character& paladin
)
{
    //------------------------------------------
    // First turn
    //------------------------------------------

    if(
        paladin.statistics.actionsTaken == 0
    )
    {
        return rollDice(1,100) <= 50;
    }

    //------------------------------------------
    // Afterwards rarely changes
    //------------------------------------------

    return rollDice(1,100) <= 10;
}

//==================================================
// Lay on Hands
//==================================================

bool shouldUseLayOnHands(
    const Character& paladin
)
{
    if(!canUseLayOnHands(paladin))
        return false;

    return
        paladin.health.hp <=
        (paladin.health.maxHp * 35) / 100;
}

//==================================================
// Shield of Faith
//==================================================

bool shouldCastShieldOfFaith(
    const Character& paladin
)
{
    if(!canCastShieldOfFaith(paladin))
        return false;

    //------------------------------------------
    // Early combat preference
    //------------------------------------------

    if(
        paladin.statistics.actionsTaken <= 2
    )
    {
        return true;
    }

    return rollDice(1,100) <= 30;
}

//==================================================
// Divine Smite
//==================================================

bool shouldPrepareDivineSmite(
    const Character& paladin,
    const Character& target
)
{
    if(!canPrepareDivineSmite(paladin))
        return false;

    //------------------------------------------
    // Finish enemy
    //------------------------------------------

    if(
        target.health.hp <=
        target.health.maxHp / 3
    )
    {
        return true;
    }

    //------------------------------------------
    // Otherwise moderate chance
    //------------------------------------------

    return rollDice(1,100) <= 40;
}

//==================================================
// Bonus Action
//==================================================

void chooseBonusAction(
    Character& paladin,
    Character& target
)
{
    //------------------------------------------
    // Lay on Hands
    //------------------------------------------

    if(
        shouldUseLayOnHands(
            paladin
        )
    )
    {
        useLayOnHands(
            paladin
        );

        return;
    }

    //------------------------------------------
    // Shield of Faith
    //------------------------------------------

    if(
        shouldCastShieldOfFaith(
            paladin
        )
    )
    {
        castShieldOfFaith(
            paladin
        );

        return;
    }

    //------------------------------------------
    // Divine Smite
    //------------------------------------------

    if(
        shouldPrepareDivineSmite(
            paladin,
            target
        )
    )
    {
        prepareDivineSmite(
            paladin
        );

        return;
    }

    //------------------------------------------
    // Shield
    //------------------------------------------

    if(
        shouldEquipShield(
            paladin
        )
    )
    {
        equipShield(
            paladin
        );
    }
    else
    {
        unequipShield(
            paladin
        );
    }
}

//==================================================
// End Turn
//==================================================

void finishTurn(
    Character& paladin
)
{
    //------------------------------------------
    // If Divine Smite wasn't consumed
    //------------------------------------------

    clearDivineSmite(
        paladin
    );

    //------------------------------------------

    paladin.status.bonusActionUsed = false;

    paladin.statistics.recentCriticalHits = 0;
}

}

//==================================================
// Paladin AI
//==================================================

void paladinTurnAI(
    Character& paladin,
    Character& target
)
{
    //------------------------------------------
    // Start Turn
    //------------------------------------------

    updateShieldOfFaith(
        paladin
    );

    //------------------------------------------
    // Bonus Action
    //------------------------------------------

    chooseBonusAction(
        paladin,
        target
    );

    //------------------------------------------
    // Main Action
    //------------------------------------------

    executePhysicalAttack(
        paladin,
        target
    );

    //------------------------------------------
    // End Turn
    //------------------------------------------

    finishTurn(
        paladin
    );
}