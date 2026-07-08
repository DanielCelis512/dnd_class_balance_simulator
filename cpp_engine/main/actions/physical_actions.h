#ifndef PHYSICAL_ACTIONS_H
#define PHYSICAL_ACTIONS_H

#include "../character.h"
#include "../combat_rules.h"

//==================================================
// Physical Attack
//==================================================

AttackResolution resolvePhysicalAttack(
    Character& attacker,
    Character& defender,
    PhysicalAction& action,
    bool hasAdvantage = false,
    bool hasDisadvantage = false
);

#endif