#include "fighter_specials.h"

#include "../../combat_utils.h"
#include "../../combat/combat_statistics.h"
#include "../../dice.h"
#include "../../combat_actions.h"


//==================================================
// Second Wind
//==================================================

bool canUseSecondWind(
    const Character& fighter
)
{
    const SpecialAction* secondWind =
        findSpecial(
            fighter,
            SpecialType::SecondWind
        );

    if(secondWind == nullptr)
        return false;

    return secondWind->currentUses > 0;
}

void useSecondWind(
    Character& fighter
)
{
    SpecialAction* secondWind =
        findSpecial(
            fighter,
            SpecialType::SecondWind
        );

    if(secondWind == nullptr)
        return;

    if(secondWind->currentUses <= 0)
        return;

    secondWind->currentUses--;

    int healing =
        rollDice(
            1,
            10
        ) +
        fighter.abilities.con;

    healCharacter(
        fighter,
        healing
    );

    registerSecondWind(
        fighter.statistics
    );

    fighter.status.bonusActionUsed = true;
}

//==================================================
// Action Surge
//==================================================

bool canUseActionSurge(
    const Character& fighter
)
{
    const SpecialAction* surge =
        findSpecial(
            fighter,
            SpecialType::ActionSurge
        );

    if(surge == nullptr)
        return false;

    return surge->currentUses > 0;
}

void activateActionSurge(
    Character& fighter
)
{
    SpecialAction* surge =
        findSpecial(
            fighter,
            SpecialType::ActionSurge
        );

    if(surge == nullptr)
        return;

    if(surge->currentUses <= 0)
        return;

    surge->currentUses--;

    fighter.status.actionSurgeActive = true;

    registerActionSurge(
        fighter.statistics
    );
}

void clearActionSurge(
    Character& fighter
)
{
    fighter.status.actionSurgeActive = false;
}

bool hasActionSurge(
    const Character& fighter
)
{
    return fighter.status.actionSurgeActive;
}