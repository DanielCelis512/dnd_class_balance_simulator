#include "monk_ai.h"

#include "specials/monk_specials.h"

#include "../action_executor.h"

#include "../../dice.h"

namespace
{

//==================================================
// Decisions
//==================================================

bool shouldUseUncannyMetabolism(
    const Character& monk
)
{
    if(!canUseUncannyMetabolism(monk))
        return false;

    if(getFocus(monk) > 0)
        return false;

    return
        monk.health.hp <=
        monk.health.maxHp / 2;
}

bool shouldUsePatientDefense(
    const Character& monk
)
{
    if(
        monk.health.hp >
        monk.health.maxHp / 3
    )
    {
        return false;
    }

    return rollDice(1,100) <= 70;
}

bool shouldUseFlurry(
    const Character& monk
)
{
    if(!canUseFlurryOfBlows(monk))
        return false;

    //------------------------------------------
    // Usually prefers offense
    //------------------------------------------

    return rollDice(1,100) <= 75;
}

//==================================================
// Bonus Action
//==================================================

bool chooseBonusAction(
    Character& monk
)
{
    //------------------------------------------
    // Entire turn
    //------------------------------------------

    if(
        shouldUseUncannyMetabolism(
            monk
        )
    )
    {
        useUncannyMetabolism(
            monk
        );

        return false;
    }

    //------------------------------------------
    // Defensive
    //------------------------------------------

    if(
        shouldUsePatientDefense(
            monk
        )
    )
    {
        activatePatientDefense(
            monk
        );

        return true;
    }

    //------------------------------------------
    // Offensive
    //------------------------------------------

    if(
        shouldUseFlurry(
            monk
        )
    )
    {
        prepareFlurryOfBlows(
            monk
        );

        return true;
    }

    //------------------------------------------
    // Default
    //------------------------------------------

    prepareMartialArts(
        monk
    );

    return true;
}

//==================================================
// Bonus Attacks
//==================================================

void performBonusAttacks(
    Character& monk,
    Character& target
)
{
    //------------------------------------------
    // Flurry
    //------------------------------------------

    if(
        hasFlurryReady(
            monk
        )
    )
    {
        executePhysicalAttack(
            monk,
            target
        );

        executePhysicalAttack(
            monk,
            target
        );

        clearFlurryOfBlows(
            monk
        );

        return;
    }

    //------------------------------------------
    // Martial Arts
    //------------------------------------------

    if(
        hasMartialArtsReady(
            monk
        )
    )
    {
        executePhysicalAttack(
            monk,
            target
        );

        clearMartialArts(
            monk
        );
    }
}

void finishTurn(
    Character& monk
)
{
    clearPatientDefense(
        monk
    );

    monk.statistics.recentCriticalHits = 0;
}

} // namespace

//==================================================
// Monk AI
//==================================================

void monkTurnAI(
    Character& monk,
    Character& target
)
{
    //------------------------------------------
    // Bonus Action
    //------------------------------------------

    bool canAttack =
        chooseBonusAction(
            monk
        );

    //------------------------------------------
    // Uncanny Metabolism
    //------------------------------------------

    if(!canAttack)
    {
        finishTurn(
            monk
        );

        return;
    }

    //------------------------------------------
    // Main Action
    //------------------------------------------

    executePhysicalAttack(
        monk,
        target
    );

    //------------------------------------------
    // Bonus Attacks
    //------------------------------------------

    performBonusAttacks(
        monk,
        target
    );

    //------------------------------------------
    // End Turn
    //------------------------------------------

    finishTurn(
        monk
    );
}