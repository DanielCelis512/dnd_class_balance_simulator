#include "barbarian_specials.h"

#include "combat/combat_statistics.h"

//==================================================
// Rage
//==================================================

bool canActivateRage(
    const Character& barbarian
)
{
    if(barbarian.status.raging)
        return false;

    if(barbarian.specials.empty())
        return false;

    return barbarian.specials[0].currentUses > 0;
}

void activateRage(
    Character& barbarian
)
{
    if(!canActivateRage(barbarian))
        return;

    barbarian.specials[0].currentUses--;

    barbarian.status.raging = true;

    barbarian.timers.rageRounds = 10;

    //------------------------------------------
    // Rage bonuses
    //------------------------------------------

    barbarian.combat.bonusDamage += 2;

    barbarian.status.strengthSaveAdvantage = true;

    //------------------------------------------

    registerRageUse(
        barbarian.statistics
    );
}

void deactivateRage(
    Character& barbarian
)
{
    if(!barbarian.status.raging)
        return;

    barbarian.status.raging = false;

    barbarian.timers.rageRounds = 0;

    //------------------------------------------
    // Remove bonuses
    //------------------------------------------

    barbarian.combat.bonusDamage -= 2;

    barbarian.status.strengthSaveAdvantage = false;

    clearRecklessAttack(barbarian);
}

void updateRage(
    Character& barbarian
)
{
    if(!barbarian.status.raging)
        return;

    if(barbarian.timers.rageRounds > 0)
    {
        barbarian.timers.rageRounds--;

        registerRageRound(
            barbarian.statistics
        );
    }

    if(barbarian.timers.rageRounds == 0)
    {
        deactivateRage(barbarian);
    }
}

bool isRaging(
    const Character& barbarian
)
{
    return barbarian.status.raging;
}

//==================================================
// Reckless Attack
//==================================================

bool canUseRecklessAttack(
    const Character& barbarian
)
{
    if(!barbarian.status.raging)
        return false;

    return true;
}

void activateRecklessAttack(
    Character& barbarian
)
{
    if(!canUseRecklessAttack(barbarian))
        return;

    barbarian.status.reckless = true;

    //------------------------------------------
    // This attack has advantage
    //------------------------------------------

    barbarian.status.hasAttackAdvantage = true;

    //------------------------------------------
    // Enemies gain advantage until next turn
    //------------------------------------------

    barbarian.status.grantsAdvantageToAttackers = true;

    //------------------------------------------

    registerRecklessAttack(
        barbarian.statistics
    );
}

void clearRecklessAttack(
    Character& barbarian
)
{
    barbarian.status.reckless = false;

    barbarian.status.hasAttackAdvantage = false;
}

void clearRecklessDefensePenalty(
    Character& barbarian
)
{
    barbarian.status.grantsAdvantageToAttackers = false;
}

bool isUsingRecklessAttack(
    const Character& barbarian
)
{
    return barbarian.status.reckless;
}