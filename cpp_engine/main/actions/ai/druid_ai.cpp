#include "druid_ai.h"

#include "specials/druid_specials.h"

#include "../action_executor.h"
#include "../combat_actions.h"

#include "../../dice.h"

namespace
{

//==================================================
// Wild Shape
//==================================================

bool shouldUseWildShape(
    const Character& druid
)
{
    if(!canUseWildShape(druid))
        return false;

    //------------------------------------------
    // Emergency survival
    //------------------------------------------

    if(
        druid.health.hp <=
        (druid.health.maxHp * 40) / 100
    )
    {
        return true;
    }

    //------------------------------------------
    // Small chance early fight
    //------------------------------------------

    if(
        druid.statistics.actionsTaken == 0
    )
    {
        return rollDice(1,100) <= 25;
    }

    return false;
}

//==================================================
// Healing Word
//==================================================

bool shouldCastHealingWord(
    const Character& druid
)
{
    if(!canCastHealingWord(druid))
        return false;

    return
        druid.health.hp <=
        (druid.health.maxHp * 35) / 100;
}

//==================================================
// Shillelagh
//==================================================

bool shouldCastShillelagh(
    const Character& druid
)
{
    if(!canCastShillelagh(druid))
        return false;

    if(druid.status.shillelaghActive)
        return false;

    return true;
}

//==================================================
// Cure Wounds
//==================================================

bool shouldCastCureWounds(
    const Character& druid
)
{
    if(!canCastCureWounds(druid))
        return false;

    return
        druid.health.hp <=
        (druid.health.maxHp * 30) / 100;
}

//==================================================
// Thunderwave
//==================================================

bool shouldCastThunderwave(
    const Character& druid,
    const Character& target
)
{
    if(!canCastThunderwave(druid))
        return false;

    return
        target.health.hp >
        (target.health.maxHp * 60) / 100;
}

//==================================================
// Entangle
//==================================================

bool shouldCastEntangle(
    const Character& druid
)
{
    if(!canCastEntangle(druid))
        return false;

    if(
        druid.statistics.actionsTaken >= 2
    )
        return false;

    return
        rollDice(1,100) <= 70;
}

//==================================================
// Bonus Action
//==================================================

void chooseBonusAction(
    Character& druid
)
{
    //------------------------------------------
    // Already transformed
    //------------------------------------------

    if(isWildShaped(druid))
        return;

    //------------------------------------------
    // Healing Word
    //------------------------------------------

    if(
        shouldCastHealingWord(druid)
    )
    {
        castHealingWord(druid);
        return;
    }

    //------------------------------------------
    // Wild Shape
    //------------------------------------------

    if(
        shouldUseWildShape(druid)
    )
    {
        activateWolfForm(druid);
        return;
    }

    //------------------------------------------
    // Shillelagh
    //------------------------------------------

    if(
        shouldCastShillelagh(druid)
    )
    {
        castShillelagh(druid);
    }
}

//==================================================
// Wild Shape AI
//==================================================

void performWildShapeAction(
    Character& druid,
    Character& target
)
{
    switch(druid.status.wildShapeForm)
    {
        case WildShapeForm::Wolf:
        {
            executePhysicalAttack(
                druid,
                target
            );
            break;
        }

        case WildShapeForm::ConstrictorSnake:
        {
            if(!target.status.grappled)
            {
                executeConstrict(
                    druid,
                    target
                );
            }
            else
            {
                executePhysicalAttack(
                    druid,
                    target
                );
            }

            break;
        }

        default:
            break;
    }
}

//==================================================
// Main Action
//==================================================

void chooseMainAction(
    Character& druid,
    Character& target
)
{
    //------------------------------------------
    // Wild Shape
    //------------------------------------------

    if(isWildShaped(druid))
    {
        performWildShapeAction(
            druid,
            target
        );

        return;
    }

    //------------------------------------------
    // Cure Wounds
    //------------------------------------------

    if(
        shouldCastCureWounds(druid)
    )
    {
        castCureWounds(druid);
        return;
    }

    //------------------------------------------
    // Thunderwave
    //------------------------------------------

    if(
        shouldCastThunderwave(
            druid,
            target
        )
    )
    {
        castThunderwave(
            druid,
            target
        );

        return;
    }

    //------------------------------------------
    // Entangle
    //------------------------------------------

    if(
        shouldCastEntangle(druid)
    )
    {
        castEntangle(
            druid,
            target
        );

        return;
    }

    //------------------------------------------
    // Physical
    //------------------------------------------

    executePhysicalAttack(
        druid,
        target
    );
}

//==================================================
// End Turn
//==================================================

void finishTurn(
    Character& druid
)
{
    updateWildShape(druid);

    updateShillelagh(druid);

    druid.statistics.recentCriticalHits = 0;
}

} // namespace

//==================================================
// Druid AI
//==================================================

void druidTurnAI(
    Character& druid,
    Character& target
)
{
    //------------------------------------------
    // Bonus Action
    //------------------------------------------

    chooseBonusAction(
        druid
    );

    //------------------------------------------
    // Main Action
    //------------------------------------------

    chooseMainAction(
        druid,
        target
    );

    //------------------------------------------
    // End Turn
    //------------------------------------------

    finishTurn(
        druid
    );
}