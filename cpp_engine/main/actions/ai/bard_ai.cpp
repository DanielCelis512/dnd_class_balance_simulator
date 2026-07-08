#include "bard_ai.h"

#include "specials/bard_specials.h"

#include "../action_executor.h"

#include "../../dice.h"

namespace
{

/////////////////////////////////////////////////////
// Healing Word
/////////////////////////////////////////////////////

bool shouldCastHealingWord(
    const Character& bard
)
{
    if(!canCastHealingWord(bard))
        return false;

    return
        bard.health.hp <=
        (bard.health.maxHp * 35) / 100;
}

/////////////////////////////////////////////////////
// Bardic Inspiration
/////////////////////////////////////////////////////

bool shouldUseBardicInspiration(
    const Character& bard
)
{
    if(!canUseBardicInspiration(bard))
        return false;

    if(bard.status.bardicInspirationActive)
        return false;

    return true;
}

/////////////////////////////////////////////////////
// Vicious Mockery
/////////////////////////////////////////////////////

bool shouldCastViciousMockery(
    const Character& bard
)
{
    if(!canCastViciousMockery(bard))
        return false;

    return true;
}

/////////////////////////////////////////////////////
// Blade Ward
/////////////////////////////////////////////////////

bool shouldCastBladeWard(
    const Character& bard
)
{
    if(!canCastBladeWard(bard))
        return false;

    if(bard.status.concentrating)
        return false;

    return
        bard.statistics.actionsTaken == 0;
}

/////////////////////////////////////////////////////
// Dissonant Whispers
/////////////////////////////////////////////////////

bool shouldCastDissonantWhispers(
    const Character& bard,
    const Character& target
)
{
    if(!canCastDissonantWhispers(bard))
        return false;

    return
        target.health.hp >
        (target.health.maxHp * 50) / 100;
}

/////////////////////////////////////////////////////
// Tasha's Hideous Laughter
/////////////////////////////////////////////////////

bool shouldCastTashasHideousLaughter(
    const Character& bard,
    const Character& target
)
{
    if(!canCastTashasHideousLaughter(bard))
        return false;

    if(bard.status.concentrating)
        return false;

    if(target.status.incapacitated)
        return false;

    return
        bard.statistics.actionsTaken <= 1;
}

/////////////////////////////////////////////////////
// Bonus Action
/////////////////////////////////////////////////////

void chooseBonusAction(
    Character& bard
)
{
    //------------------------------------------
    // Healing Word
    //------------------------------------------

    if(
        shouldCastHealingWord(bard)
    )
    {
        castHealingWord(bard);
        return;
    }

    //------------------------------------------
    // Bardic Inspiration
    //------------------------------------------

    if(
        shouldUseBardicInspiration(bard)
    )
    {
        castBardicInspiration(
            bard,
            bard
        );

        return;
    }
}

/////////////////////////////////////////////////////
// Main Action
/////////////////////////////////////////////////////

void chooseMainAction(
    Character& bard,
    Character& target
)
{
    //------------------------------------------
    // Tasha's Hideous Laughter
    //------------------------------------------

    if(
        shouldCastTashasHideousLaughter(
            bard,
            target
        )
    )
    {
        castTashasHideousLaughter(
            bard,
            target
        );

        return;
    }

    //------------------------------------------
    // Dissonant Whispers
    //------------------------------------------

    if(
        shouldCastDissonantWhispers(
            bard,
            target
        )
    )
    {
        castDissonantWhispers(
            bard,
            target
        );

        return;
    }

    //------------------------------------------
    // Blade Ward
    //------------------------------------------

    if(
        shouldCastBladeWard(
            bard
        )
    )
    {
        castBladeWard(
            bard
        );

        return;
    }

    //------------------------------------------
    // Vicious Mockery
    //------------------------------------------

    if(
        shouldCastViciousMockery(
            bard
        )
    )
    {
        castViciousMockery(
            bard,
            target
        );

        return;
    }

    //------------------------------------------
    // Physical Attack
    //------------------------------------------

    executePhysicalAttack(
        bard,
        target
    );
}

/////////////////////////////////////////////////////
// End Turn
/////////////////////////////////////////////////////

void finishTurn(
    Character& bard
)
{
    updateBardicInspiration(
        bard
    );

    updateBladeWard(
        bard
    );

    updateTashasHideousLaughter(
        bard
    );

    bard.statistics.recentCriticalHits = 0;
}

} // namespace

/////////////////////////////////////////////////////
// Bard AI
/////////////////////////////////////////////////////

void bardTurnAI(
    Character& bard,
    Character& target
)
{
    //------------------------------------------
    // Bonus Action
    //------------------------------------------

    chooseBonusAction(
        bard
    );

    //------------------------------------------
    // Main Action
    //------------------------------------------

    chooseMainAction(
        bard,
        target
    );

    //------------------------------------------
    // End Turn
    //------------------------------------------

    finishTurn(
        bard
    );
}