#include "simulation.h"

#include "battle.h"
#include "combat_statistics.h"

#include <iomanip>
#include <iostream>

void simulateBattles(
    Character player1,
    Character player2,
    int simulations,
    bool showLog
)
{
    int player1Wins = 0;
    int player2Wins = 0;
    int draws = 0;

    CombatStatistics player1Totals{};
    CombatStatistics player2Totals{};

    for(
        int i = 0;
        i < simulations;
        ++i
    )
    {
        //--------------------------------------
        // Fresh copies every battle
        //--------------------------------------

        Character first = player1;
        Character second = player2;

        CombatStatistics player1BattleStats{};
        CombatStatistics player2BattleStats{};

        BattleResult result =
            battle(
                first,
                second,
                player1BattleStats,
                player2BattleStats,
                showLog
            );

        accumulateStatistics(
            player1Totals,
            player1BattleStats
        );

        accumulateStatistics(
            player2Totals,
            player2BattleStats
        );

        switch(result)
        {
            case BattleResult::Player1Win:
                player1Wins++;
                break;

            case BattleResult::Player2Win:
                player2Wins++;
                break;

            case BattleResult::Draw:
                draws++;
                break;
        }
    }

    calculateFinalStatistics(
        player1Totals
    );

    calculateFinalStatistics(
        player2Totals
    );

    auto printResults =
    [&](const Character& character,
        int wins,
        int losses,
        const CombatStatistics& stats)
    {
        std::cout
            << character.identity.name << "\n"
            << "Wins: "
            << wins << "\n"
            << "Losses: "
            << losses << "\n"
            << "Win Rate: "
            << std::fixed
            << std::setprecision(2)
            << (100.0 * wins / simulations)
            << "%\n\n";

        std::cout
            << "Damage Dealt: "
            << stats.totalDamageDealt << "\n";

        std::cout
            << "Damage Taken: "
            << stats.totalDamageTaken << "\n";

        std::cout
            << "Healing Done: "
            << stats.totalHealingDone << "\n";

        std::cout
            << "Attacks Made: "
            << stats.attacksMade << "\n";

        std::cout
            << "Hits: "
            << stats.attacksHit << "\n";

        std::cout
            << "Accuracy: "
            << std::fixed
            << std::setprecision(2)
            << stats.accuracy * 100.0
            << "%\n";

        std::cout
            << "Critical Hits: "
            << stats.criticalHits << "\n";

        std::cout
            << "Critical Misses: "
            << stats.criticalMisses << "\n";

        std::cout
            << "Highest Hit: "
            << stats.highestHit << "\n\n";
    };

    std::cout
        << "\n=====================================\n"
        << "SIMULATION RESULTS\n"
        << "=====================================\n"
        << "Battles: "
        << simulations
        << "\n\n";

    printResults(
        player1,
        player1Wins,
        player2Wins,
        player1Totals
    );

    printResults(
        player2,
        player2Wins,
        player1Wins,
        player2Totals
    );

    std::cout
        << "Draws: "
        << draws
        << "\n"
        << "=====================================\n";
}