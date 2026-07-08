#ifndef TURN_MANAGER_H
#define TURN_MANAGER_H

#include "character.h"
#include "combat_statistics.h"

//==========================================
// Executes one complete turn.
//==========================================

void executeTurn(
    Character& attacker,
    Character& defender,
    CombatStatistics& attackerStats,
    CombatStatistics& defenderStats
);

//==========================================
// Checks if the combat should continue.
//==========================================

bool battleContinues(
    const Character& characterA,
    const Character& characterB
);

#endif