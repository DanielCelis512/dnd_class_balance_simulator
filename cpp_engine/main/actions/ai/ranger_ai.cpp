#include "ranger_ai.h"

#include "specials/ranger_specials.h"

#include "../action_executor.h"

#include "../../dice.h"

namespace
{

//==================================================
// Healing
//==================================================

bool shouldHeal(
    const Character& ranger
)
{
    return
        ranger.health.hp <=
        ranger.health.maxHp / 3;
}

//==================================================
// Hunter's Mark
//==================================================

bool shouldCastHuntersMark(
    const Character& ranger
)
{
    if(hasHuntersMark(ranger))
        return false;

    return canCastHuntersMark(ranger);
}

//==================================================
// Zephyr Strike
//==================================================

bool shouldCastZephyrStrike(
    const Character& ranger
)
{
    if(hasZephyrStrikeReady(ranger))
        return false;

    if(!hasHuntersMark(ranger))
        return false;

    if(!canCastZephyrStrike(ranger))
        return false;

    return rollDice(1,100) <= 60;
}

//==================================================
// Hunter's Prey
//==================================================

bool shouldPrepareHuntersPrey(
    const Character& ranger,
    const Character& target
)
{
    return
        canPrepareHuntersPrey(
            ranger,
            target
        );
}

//==================================================
// Bonus Action
//==================================================

void chooseBonusAction(
    Character& ranger
)
{
    //------------------------------------------
    // Hunter's Mark
    //------------------------------------------

    if(
        shouldCastHuntersMark(
            ranger
        )
    )
    {
        castHuntersMark(
            ranger
        );

        return;
    }

    //------------------------------------------
    // Zephyr Strike
    //------------------------------------------

    if(
        shouldCastZephyrStrike(
            ranger
        )
    )
    {
        castZephyrStrike(
            ranger
        );

        return;
    }
}

//==================================================
// Action
//==================================================

bool chooseAction(
    Character& ranger
)
{
    //------------------------------------------
    // Heal
    //------------------------------------------

    if(
        shouldHeal(
            ranger
        )
    )
    {
        castCureWounds(
            ranger
        );

        return false;
    }

    return true;
}

//==================================================
// Prepare Attack
//==================================================

void prepareAttack(
    Character& ranger,
    Character& target
)
{
    if(
        shouldPrepareHuntersPrey(
            ranger,
            target
        )
    )
    {
        prepareHuntersPrey(
            ranger
        );
    }
}

//==================================================
// End Turn
//==================================================

void finishTurn(
    Character& ranger
)
{
    clearHuntersPrey(
        ranger
    );

    clearZephyrStrike(
        ranger
    );

    ranger.statistics.recentCriticalHits = 0;
}

} // namespace

//==================================================
// Ranger AI
//==================================================

void rangerTurnAI(
    Character& ranger,
    Character& target
)
{
    //------------------------------------------
    // Start Turn
    //------------------------------------------

    updateHuntersMark(
        ranger
    );

    //------------------------------------------
    // Bonus Action
    //------------------------------------------

    chooseBonusAction(
        ranger
    );

    //------------------------------------------
    // Action
    //------------------------------------------

    if(
        !chooseAction(
            ranger
        )
    )
    {
        finishTurn(
            ranger
        );

        return;
    }

    //------------------------------------------
    // Prepare Attack
    //------------------------------------------

    prepareAttack(
        ranger,
        target
    );

    //------------------------------------------
    // Main Attack
    //------------------------------------------

    executePhysicalAttack(
        ranger,
        target
    );

    //------------------------------------------
    // End Turn
    //------------------------------------------

    finishTurn(
        ranger
    );
}