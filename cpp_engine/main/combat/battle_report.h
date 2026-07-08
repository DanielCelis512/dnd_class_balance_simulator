#ifndef BATTLE_REPORT_H
#define BATTLE_REPORT_H

#include "character.h"
#include "combat_statistics.h"

void printSingleBattleReport(
    const Character& winner,
    const Character& loser,
    int rounds
);

void printSimulationReport(
    const Character& character,
    const CombatStatistics& stats
);

#endif