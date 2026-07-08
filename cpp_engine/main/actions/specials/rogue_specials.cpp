#include "rogue_specials.h"

#include "../../combat_actions.h"
#include "../../combat_utils.h"
#include "../../combat/combat_statistics.h"

/////////////////////////////////////////////////////
// Aim
/////////////////////////////////////////////////////

bool canUseAim(
    const Character& rogue
)
{
    return
        rogue.health.alive;
}

void useAim(
    Character& rogue
)
{
    if(!canUseAim(rogue))
        return;

    rogue.status.hasAttackAdvantage = true;
    rogue.status.aimReady = true;
}

void clearAim(
    Character& rogue
)
{
    rogue.status.hasAttackAdvantage = false;
    rogue.status.aimReady = false;
}

/////////////////////////////////////////////////////
// Dodge
/////////////////////////////////////////////////////

bool canUseDodge(
    const Character& rogue
)
{
    return rogue.health.alive;
}

void useDodge(
    Character& rogue
)
{
    if(!canUseDodge(rogue))
        return;

    rogue.status.attackersHaveDisadvantage = true;
    rogue.status.dexteritySaveAdvantage = true;
    rogue.status.dodgeReady = true;
}

void clearDodge(
    Character& rogue
)
{
    rogue.status.attackersHaveDisadvantage = false;
    rogue.status.dexteritySaveAdvantage = false;
    rogue.status.dodgeReady = false;
}

/////////////////////////////////////////////////////
// Off-Hand Attack
/////////////////////////////////////////////////////

bool canUseOffHandAttack(
    const Character& rogue
)
{
    return rogue.health.alive;
}

void prepareOffHandAttack(
    Character& rogue
)
{
    if(!canUseOffHandAttack(rogue))
        return;

    rogue.status.offHandAttackReady = true;
}

void clearOffHandAttack(
    Character& rogue
)
{
    rogue.status.offHandAttackReady = false;
}

/////////////////////////////////////////////////////
// Sneak Attack
/////////////////////////////////////////////////////

bool canPrepareSneakAttack(
    const Character& rogue
)
{
    return
        rogue.status.hasAttackAdvantage;
}

void prepareSneakAttack(
    Character& rogue
)
{
    if(!canPrepareSneakAttack(rogue))
        return;

    rogue.status.sneakAttackReady = true;
}

bool shouldTriggerSneakAttack(
    const Character& rogue
)
{
    return rogue.status.sneakAttackReady;
}

void consumeSneakAttack(
    Character& rogue
)
{
    if(!rogue.status.sneakAttackReady)
        return;

    rogue.status.sneakAttackReady = false;

    registerSneakAttack(
        rogue.statistics
    );
}

void clearSneakAttack(
    Character& rogue
)
{
    rogue.status.sneakAttackReady = false;
}