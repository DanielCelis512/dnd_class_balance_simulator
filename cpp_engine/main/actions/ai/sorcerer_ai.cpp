#include "sorcerer_ai.h"

#include "specials/sorcerer_specials.h"

#include "../../dice.h"

namespace
{

/////////////////////////////////////////////////////
// Innate Sorcery
/////////////////////////////////////////////////////

bool shouldUseInnateSorcery(
    const Character& sorcerer
)
{
    if(
        !canUseInnateSorcery(
            sorcerer
        )
    )
    {
        return false;
    }

    //------------------------------------------
    // Always activate early
    //------------------------------------------

    return
        sorcerer.statistics.actionsTaken == 0;
}

/////////////////////////////////////////////////////
// False Life
/////////////////////////////////////////////////////

bool shouldCastFalseLife(
    const Character& sorcerer
)
{
    if(
        !canCastFalseLife(
            sorcerer
        )
    )
    {
        return false;
    }

    if(
        sorcerer.health.tempHp > 0
    )
    {
        return false;
    }

    return
        sorcerer.health.hp <=
        (sorcerer.health.maxHp * 50) / 100;
}

/////////////////////////////////////////////////////
// Chromatic Orb
/////////////////////////////////////////////////////

bool shouldCastChromaticOrb(
    const Character& sorcerer
)
{
    return
        canCastChromaticOrb(
            sorcerer
        );
}

/////////////////////////////////////////////////////
// Chaos Bolt
/////////////////////////////////////////////////////

bool shouldCastChaosBolt(
    const Character& sorcerer
)
{
    return
        canCastChaosBolt(
            sorcerer
        );
}

/////////////////////////////////////////////////////
// Main Action
/////////////////////////////////////////////////////

void chooseAction(
    Character& sorcerer,
    Character& target
)
{
    //------------------------------------------
    // Defensive spell
    //------------------------------------------

    if(
        shouldCastFalseLife(
            sorcerer
        )
    )
    {
        castFalseLife(
            sorcerer
        );

        return;
    }

    //------------------------------------------
    // Strongest spell
    //------------------------------------------

    if(
        shouldCastChromaticOrb(
            sorcerer
        )
    )
    {
        castChromaticOrb(
            sorcerer,
            target
        );

        return;
    }

    //------------------------------------------
    // Second spell
    //------------------------------------------

    if(
        shouldCastChaosBolt(
            sorcerer
        )
    )
    {
        castChaosBolt(
            sorcerer,
            target
        );

        return;
    }

    //------------------------------------------
    // Best cantrip
    //------------------------------------------

    if(
        canCastSorcerousBurst(
            sorcerer
        )
    )
    {
        castSorcerousBurst(
            sorcerer,
            target
        );

        return;
    }

    //------------------------------------------
    // Backup
    //------------------------------------------

    castFireBolt(
        sorcerer,
        target
    );
}

}

/////////////////////////////////////////////////////
// Sorcerer AI
/////////////////////////////////////////////////////

void sorcererTurnAI(
    Character& sorcerer,
    Character& target
)
{
    //------------------------------------------
    // Update timers
    //------------------------------------------

    updateInnateSorcery(
        sorcerer
    );

    //------------------------------------------
    // Bonus Action
    //------------------------------------------

    if(
        shouldUseInnateSorcery(
            sorcerer
        )
    )
    {
        activateInnateSorcery(
            sorcerer
        );
    }

    //------------------------------------------
    // Action
    //------------------------------------------

    chooseAction(
        sorcerer,
        target
    );

    //------------------------------------------
    // End Turn
    //------------------------------------------

    sorcerer.status.bonusActionUsed =
        false;
}