#ifndef COMBAT_ANALYSIS_H
#define COMBAT_ANALYSIS_H

#include "combat_statistics.h"

//==================================================
// Battle Results
//==================================================

double getWinRate(
    const CombatStatistics& stats
);

double getLossRate(
    const CombatStatistics& stats
);

//==================================================
// Survival
//==================================================

double getAverageRemainingHp(
    const CombatStatistics& stats
);

double getSurvivalRate(
    const CombatStatistics& stats,
    int maxHp
);

double getAverageRounds(
    const CombatStatistics& stats
);

//==================================================
// Damage
//==================================================

double getAverageDamageDealt(
    const CombatStatistics& stats
);

double getAverageDamageTaken(
    const CombatStatistics& stats
);

//==================================================
// Physical Combat
//==================================================

double getHitRate(
    const CombatStatistics& stats
);

double getMissRate(
    const CombatStatistics& stats
);

double getCriticalHitRate(
    const CombatStatistics& stats
);

double getCriticalMissRate(
    const CombatStatistics& stats
);

//==================================================
// Magic
//==================================================

double getSpellAccuracy(
    const CombatStatistics& stats
);

double getCantripAccuracy(
    const CombatStatistics& stats
);

//==================================================
// Healing
//==================================================

double getAverageHealing(
    const CombatStatistics& stats
);

//==================================================
// Specials
//==================================================

double getAverageSpecialUses(
    const CombatStatistics& stats
);

//==================================================
// Efficiency
//==================================================

double getDamagePerRound(
    const CombatStatistics& stats
);

double getNetDamage(
    const CombatStatistics& stats
);

#endif