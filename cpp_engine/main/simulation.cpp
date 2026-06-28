#include "simulation.h"

#include "battle.h"

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

    for(int i = 0; i < simulations; i++)
    {
        Character first = player1;
        Character second = player2;

        BattleResult result =
            battle(
                first,
                second,
                showLog
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

    auto printResults =
        [&](const Character& character,
            int wins,
            int losses)
        {
            std::cout
                << character.name << "\n"
                << "Wins: "
                << wins << "\n"
                << "Losses: "
                << losses << "\n"
                << "Win Rate: "
                << std::fixed
                << std::setprecision(2)
                << (100.0 * wins / simulations)
                << "%\n\n";
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
        player2Wins
    );

    printResults(
        player2,
        player2Wins,
        player1Wins
    );

    std::cout
        << "Draws: "
        << draws
        << "\n"
        << "=====================================\n";
}