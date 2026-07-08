#include "warlock_ai.h"

#include "specials/warlock_specials.h"

#include "../action_executor.h"

#include "../../dice.h"

namespace
{

/////////////////////////////////////////////////////
// Imp
/////////////////////////////////////////////////////

bool shouldSummonImp(
    const Character& warlock
)
{
    if(!canSummonImp(warlock))
        return false;

    return true;
}

/////////////////////////////////////////////////////
// Magical Cunning
/////////////////////////////////////////////////////

bool shouldUseMagicalCunning(
    const Character& warlock
)
{
    if(!canUseMagicalCunning(warlock))
        return false;

    //--------------------------------------------------
    // Recover spell slot only when empty
    //--------------------------------------------------

    return
        warlock.spellSlots.current[1] == 0;
}

/////////////////////////////////////////////////////
// Hex
/////////////////////////////////////////////////////

bool shouldCastHex(
    const Character& warlock
)
{
    if(!canCastHex(warlock))
        return false;

    //--------------------------------------------------
    // Prefer Hex at beginning of combat
    //--------------------------------------------------

    if(
        warlock.statistics.actionsTaken <= 2
    )
    {
        return true;
    }

    return rollDice(1,100) <= 25;
}

/////////////////////////////////////////////////////
// Witch Bolt
/////////////////////////////////////////////////////

bool shouldCastWitchBolt(
    const Character& warlock
)
{
    if(!canCastWitchBolt(warlock))
        return false;

    //--------------------------------------------------
    // Save spell slots if enemy is almost dead
    //--------------------------------------------------

    return rollDice(1,100) <= 60;
}

/////////////////////////////////////////////////////
// Bonus / Utility
/////////////////////////////////////////////////////

void chooseUtility(
    Character& warlock,
    Character& target
)
{
    //--------------------------------------------------
    // Imp
    //--------------------------------------------------

    if(
        shouldSummonImp(
            warlock
        )
    )
    {
        summonImp(
            warlock
        );

        return;
    }

    //--------------------------------------------------
    // Recover spell slot
    //--------------------------------------------------

    if(
        shouldUseMagicalCunning(
            warlock
        )
    )
    {
        useMagicalCunning(
            warlock
        );

        return;
    }

    //--------------------------------------------------
    // Hex
    //--------------------------------------------------

    if(
        shouldCastHex(
            warlock
        )
    )
    {
        castHex(
            warlock,
            target
        );
    }
}

/////////////////////////////////////////////////////
// Main Action
/////////////////////////////////////////////////////

void chooseAttack(
    Character& warlock,
    Character& target
)
{
    //--------------------------------------------------
    // Witch Bolt
    //--------------------------------------------------

    if(
        shouldCastWitchBolt(
            warlock
        )
    )
    {
        castWitchBolt(
            warlock,
            target
        );

        return;
    }

    //--------------------------------------------------
    // Eldritch Blast
    //--------------------------------------------------

    castEldritchBlast(
        warlock,
        target
    );
}

/////////////////////////////////////////////////////
// End Turn
/////////////////////////////////////////////////////

void finishTurn(
    Character& warlock
)
{
    updateImp(
        warlock
    );

    updateHex(
        warlock
    );

    warlock.status.bonusActionUsed =
        false;
}

}

/////////////////////////////////////////////////////
// AI
/////////////////////////////////////////////////////

void warlockTurnAI(
    Character& warlock,
    Character& target
)
{
    //------------------------------------------
    // Utility
    //------------------------------------------

    chooseUtility(
        warlock,
        target
    );

    //------------------------------------------
    // Action
    //------------------------------------------

    chooseAttack(
        warlock,
        target
    );

    //------------------------------------------
    // End Turn
    //------------------------------------------

    finishTurn(
        warlock
    );
}