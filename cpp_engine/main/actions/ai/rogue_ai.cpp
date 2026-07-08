#include "rogue_ai.h"

#include "specials/rogue_specials.h"

#include "../action_executor.h"

#include "../../dice.h"

namespace
{

//==================================================
// Dodge Decision
//==================================================

bool shouldUseDodge(
    const Character& rogue
)
{
    //------------------------------------------
    // Low HP
    //------------------------------------------

    if(
        rogue.health.hp <=
        rogue.health.maxHp / 3
    )
    {
        return true;
    }

    //------------------------------------------
    // Recently suffered a critical hit
    //------------------------------------------

    if(
        rogue.statistics.recentCriticalHits > 0
    )
    {
        return true;
    }

    //------------------------------------------

    return false;
}

//==================================================
// Aim Decision
//==================================================

bool shouldUseAim(
    const Character& rogue
)
{
    //------------------------------------------
    // Already has advantage
    //------------------------------------------

    if(
        rogue.status.hasAttackAdvantage
    )
    {
        return false;
    }

    //------------------------------------------
    // Prefer preparing Sneak Attack
    //------------------------------------------

    return rollDice(1,100) <= 70;
}

//==================================================
// Off-Hand Decision
//==================================================

bool shouldUseOffHandAttack(
    const Character& rogue
)
{
    return true;
}

//==================================================
// Sneak Attack Decision
//==================================================

bool shouldPrepareSneakAttack(
    const Character& rogue,
    const Character& target
)
{
    (void)target;

    return
        canPrepareSneakAttack(
            rogue
        );
}

//==================================================
// Bonus Action
//==================================================

void chooseBonusAction(
    Character& rogue
)
{
    //------------------------------------------
    // Defensive
    //------------------------------------------

    if(
        shouldUseDodge(
            rogue
        )
    )
    {
        useDodge(
            rogue
        );

        return;
    }

    //------------------------------------------
    // Prepare next attack
    //------------------------------------------

    if(
        shouldUseAim(
            rogue
        )
    )
    {
        useAim(
            rogue
        );

        return;
    }

    //------------------------------------------
    // Extra attack
    //------------------------------------------

    if(
        shouldUseOffHandAttack(
            rogue
        )
    )
    {
        prepareOffHandAttack(
            rogue
        );
    }
}

//==================================================
// Main Action
//==================================================

void performAttack(
    Character& rogue,
    Character& target
)
{
    //------------------------------------------
    // Sneak Attack
    //------------------------------------------

    if(
        shouldPrepareSneakAttack(
            rogue,
            target
        )
    )
    {
        prepareSneakAttack(
            rogue
        );
    }

    //------------------------------------------
    // Main attack
    //------------------------------------------

    executePhysicalAttack(
        rogue,
        target
    );

    //------------------------------------------
    // Bonus dagger attack
    //------------------------------------------

    if(
        rogue.status.offHandAttackReady
    )
    {
        executePhysicalAttack(
            rogue,
            target
        );

        clearOffHandAttack(
            rogue
        );
    }
}

//==================================================
// End Turn
//==================================================

void finishTurn(
    Character& rogue
)
{
    //------------------------------------------
    // Aim only affects one attack
    //------------------------------------------

    clearAim(
        rogue
    );

    //------------------------------------------
    // Dodge lasts until next turn,
    // so we DO NOT clear it here.
    //------------------------------------------

    clearSneakAttack(
        rogue
    );

    rogue.statistics.recentCriticalHits = 0;
}

} // namespace

//==================================================
// Rogue AI
//==================================================

void rogueTurnAI(
    Character& rogue,
    Character& target
)
{
    //------------------------------------------
    // Start Turn
    //------------------------------------------

    clearDodge(
        rogue
    );

    //------------------------------------------
    // Bonus Action
    //------------------------------------------

    chooseBonusAction(
        rogue
    );

    //------------------------------------------
    // Action
    //------------------------------------------

    performAttack(
        rogue,
        target
    );

    //------------------------------------------
    // End Turn
    //------------------------------------------

    finishTurn(
        rogue
    );
}