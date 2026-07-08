#include "battle_report.h"

#include <iostream>
#include <iomanip>

#include "combat_analysis.h"

void printSingleBattleReport(
    const Character& winner,
    const Character& loser,
    int rounds
)
{
    std::cout << "\n";
    std::cout << "==============================\n";
    std::cout << "        BATTLE REPORT\n";
    std::cout << "==============================\n";

    std::cout
        << "Winner : "
        << winner.name
        << "\n";

    std::cout
        << "Loser  : "
        << loser.name
        << "\n";

    std::cout
        << "Rounds : "
        << rounds
        << "\n";

    std::cout
        << "Remaining HP : "
        << winner.hp
        << "/"
        << winner.maxHp
        << "\n";

    std::cout << "==============================\n\n";
}

void printSimulationReport(
    const Character& character,
    const CombatStatistics& stats
)
{
    using std::cout;
    using std::fixed;
    using std::setprecision;

    cout << "\n";
    cout << "=====================================\n";
    cout << "          SIMULATION REPORT\n";
    cout << "=====================================\n";

    cout << "Class: "
         << character.name
         << "\n\n";

    cout << fixed << setprecision(2);

    cout << "Battles           : "
         << stats.battles << "\n";

    cout << "Wins              : "
         << stats.wins << "\n";

    cout << "Losses            : "
         << stats.losses << "\n";

    cout << "Win Rate          : "
         << getWinRate(stats)
         << "%\n\n";

    cout << "Average Rounds    : "
         << getAverageRounds(stats)
         << "\n";

    cout << "Average HP Left   : "
         << getAverageRemainingHp(stats)
         << "\n";

    cout << "Survival Rate     : "
         << getSurvivalRate(
                stats,
                character.maxHp
            )
         << "%\n\n";

    cout << "Damage Dealt      : "
         << getAverageDamageDealt(stats)
         << "\n";

    cout << "Damage Taken      : "
         << getAverageDamageTaken(stats)
         << "\n";

    cout << "Damage / Round    : "
         << getDamagePerRound(stats)
         << "\n";

    cout << "Net Damage        : "
         << getNetDamage(stats)
         << "\n\n";

    cout << "Hit Rate          : "
         << getHitRate(stats)
         << "%\n";

    cout << "Miss Rate         : "
         << getMissRate(stats)
         << "%\n";

    cout << "Critical Hits     : "
         << getCriticalHitRate(stats)
         << "%\n";

    cout << "Critical Misses   : "
         << getCriticalMissRate(stats)
         << "%\n\n";

    cout << "Spell Accuracy    : "
         << getSpellAccuracy(stats)
         << "%\n";

    cout << "Cantrip Accuracy  : "
         << getCantripAccuracy(stats)
         << "%\n\n";

    cout << "Average Healing   : "
         << getAverageHealing(stats)
         << "\n";

    cout << "Special Uses      : "
         << getAverageSpecialUses(stats)
         << "\n";

    cout << "=====================================\n";
}

