#include "barbarian_ai.h"

#include "specials/barbarian_specials.h"

#include "../action_executor.h"
#include "../../dice.h"

namespace
{

//==================================================
// Reckless Decision
//==================================================

bool shouldUseReckless(
    const Character& barbarian
)
{
    int chance = 95;

    //------------------------------------------
    // Low HP
    //------------------------------------------

    if(
        barbarian.health.hp <=
        barbarian.health.maxHp / 2
    )
    {
        chance -= 15;
    }

    //------------------------------------------
    // Recently received a critical hit
    //------------------------------------------

    if(
        barbarian.statistics.recentCriticalHits > 0
    )
    {
        chance -= 10;
    }

    //------------------------------------------

    if(chance < 60)
        chance = 60;

    return rollDice(1,100) <= chance;
}

//==================================================
// Bonus Action
//==================================================

void chooseBonusAction(
    Character& barbarian
)
{
    if(canActivateRage(barbarian))
    {
        activateRage(barbarian);
    }
}

//==================================================
// Main Action
//==================================================

void chooseAttackMode(
    Character& barbarian
)
{
    clearRecklessAttack(barbarian);

    if(!canUseRecklessAttack(barbarian))
        return;

    if(shouldUseReckless(barbarian))
    {
        activateRecklessAttack(barbarian);
    }
}

//==================================================
// End Turn
//==================================================

void finishTurn(
    Character& barbarian
)
{
    //------------------------------------------
    // Only affects the current attack
    //------------------------------------------

    clearRecklessAttack(barbarian);

    //------------------------------------------

    barbarian.statistics.recentCriticalHits = 0;
}

} // namespace

//==================================================
// Barbarian AI
//==================================================

void barbarianTurnAI(
    Character& barbarian,
    Character& target
)
{
    //----------------------------------
    // Bonus Action
    //----------------------------------

    chooseBonusAction(barbarian);

    //----------------------------------
    // Main Action
    //----------------------------------

    chooseAttackMode(barbarian);

    executePhysicalAttack(
        barbarian,
        target
    );

    //----------------------------------
    // End Turn
    //----------------------------------

    finishTurn(barbarian);

    //----------------------------------
    // Timers
    //----------------------------------

    updateRage(barbarian);
}