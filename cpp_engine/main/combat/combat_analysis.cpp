#include "combat_analysis.h"

namespace
{
double divide(
    double numerator,
    double denominator
)
{
    if(denominator == 0.0)
    {
        return 0.0;
    }

    return numerator / denominator;
}
}

double getWinRate(
    const CombatStatistics& stats
)
{
    return divide(
        stats.wins * 100.0,
        stats.battles
    );
}

double getLossRate(
    const CombatStatistics& stats
)
{
    return divide(
        stats.losses * 100.0,
        stats.battles
    );
}

double getAverageRemainingHp(
    const CombatStatistics& stats
)
{
    return divide(
        stats.totalRemainingHp,
        stats.battles
    );
}

double getAverageRounds(
    const CombatStatistics& stats
)
{
    return divide(
        stats.totalRounds,
        stats.battles
    );
}

double getAverageDamageDealt(
    const CombatStatistics& stats
)
{
    return divide(
        stats.damageDealt,
        stats.battles
    );
}

double getAverageDamageTaken(
    const CombatStatistics& stats
)
{
    return divide(
        stats.damageTaken,
        stats.battles
    );
}

double getHitRate(
    const CombatStatistics& stats
)
{
    return divide(
        stats.hits * 100.0,
        stats.attacks
    );
}

double getMissRate(
    const CombatStatistics& stats
)
{
    return divide(
        stats.misses * 100.0,
        stats.attacks
    );
}

double getCriticalHitRate(
    const CombatStatistics& stats
)
{
    return divide(
        stats.criticalHits * 100.0,
        stats.attacks
    );
}

double getCriticalMissRate(
    const CombatStatistics& stats
)
{
    return divide(
        stats.criticalMisses * 100.0,
        stats.attacks
    );
}

double getSpellAccuracy(
    const CombatStatistics& stats
)
{
    return divide(
        stats.spellHits * 100.0,
        stats.spellsCast
    );
}

double getCantripAccuracy(
    const CombatStatistics& stats
)
{
    return divide(
        stats.cantripHits * 100.0,
        stats.cantripsCast
    );
}

double getAverageHealing(
    const CombatStatistics& stats
)
{
    return divide(
        stats.healingDone,
        stats.battles
    );
}

double getAverageSpecialUses(
    const CombatStatistics& stats
)
{
    return divide(
        stats.specialsUsed,
        stats.battles
    );
}

double getDamagePerRound(
    const CombatStatistics& stats
)
{
    return divide(
        stats.damageDealt,
        stats.totalRounds
    );
}

double getNetDamage(
    const CombatStatistics& stats
)
{
    return stats.damageDealt -
           stats.damageTaken;
}

double getSurvivalRate(
    const CombatStatistics& stats,
    int maxHp
)
{
    if(maxHp <= 0)
    {
        return 0.0;
    }

    return
        getAverageRemainingHp(stats)
        /
        maxHp
        *
        100.0;
}