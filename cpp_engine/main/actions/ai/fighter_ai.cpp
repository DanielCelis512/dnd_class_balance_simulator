#include "fighter_ai.h"

#include "specials/fighter_specials.h"
#include "../combat_utils.h"

#include "../action_executor.h"

#include "../../dice.h"

namespace
{

//==================================================
// Shield
//==================================================

bool shouldToggleShield(
    const Character& fighter
)
{
    //------------------------------------------
    // Opening decision
    //------------------------------------------

    if(fighter.statistics.actionsTaken == 0)
    {
        return rollDice(1,100) <= 5;
    }

    //------------------------------------------
    // Afterwards rarely changes
    //------------------------------------------

    return rollDice(1,100) <= 10;
}

//==================================================
// Second Wind
//==================================================

bool shouldUseSecondWind(
    const Character& fighter
)
{
    if(!canUseSecondWind(fighter))
        return false;

    //------------------------------------------

    return
        fighter.health.hp <=
        fighter.health.maxHp / 3;
}

//==================================================
// Action Surge
//==================================================

bool shouldUseActionSurge(
    const Character& fighter,
    const Character& target
)
{
    (void)target;

    if(!canUseActionSurge(fighter))
        return false;

    //------------------------------------------
    // Aggressive finish
    //------------------------------------------

    if(target.health.hp <=
       target.health.maxHp / 3)
    {
        return true;
    }

    //------------------------------------------
    // Low HP desperation
    //------------------------------------------

    if(fighter.health.hp <=
       fighter.health.maxHp / 4)
    {
        return true;
    }

    return false;
}

//==================================================
// Bonus Action
//==================================================

void chooseBonusAction(
    Character& fighter
)
{
    //------------------------------------------
    // Already spent
    //------------------------------------------

    if(fighter.status.bonusActionUsed)
        return;

    //------------------------------------------
    // Second Wind
    //------------------------------------------

    if(shouldUseSecondWind(fighter))
    {
        useSecondWind(fighter);
        return;
    }

    //------------------------------------------
    // Shield
    //------------------------------------------

    if(shouldToggleShield(fighter))
    {
        toggleShield(fighter);

        fighter.status.bonusActionUsed = true;
    }
}

//==================================================
// Main Action
//==================================================

void performMainAction(
    Character& fighter,
    Character& target
)
{
    executePhysicalAttack(
        fighter,
        target
    );
}

} // namespace

//==================================================
// Fighter AI
//==================================================

void fighterTurnAI(
    Character& fighter,
    Character& target
)
{
    //------------------------------------------
    // Bonus Action
    //------------------------------------------

    chooseBonusAction(
        fighter
    );

    //------------------------------------------
    // Normal Action
    //------------------------------------------

    performMainAction(
        fighter,
        target
    );

    //------------------------------------------
    // Action Surge
    //------------------------------------------

    if(
        target.health.alive &&
        shouldUseActionSurge(
            fighter,
            target
        )
    )
{
    activateActionSurge(
        fighter
    );
}

    if(hasActionSurge(fighter))
    {
        performMainAction(
            fighter,
            target
        );

        clearActionSurge(
            fighter
        );
    }

    //------------------------------------------
    // Statistics
    //------------------------------------------

    fighter.statistics.recentCriticalHits = 0;

    fighter.status.bonusActionUsed = false;

    fighter.statistics.actionsTaken++;

    fighter.statistics.recentCriticalHits = 0;
}