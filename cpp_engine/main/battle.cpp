#include "battle.h"

#include "logger.h"
#include "turn_manager.h"

BattleResult battle(
    Character& player1,
    Character& player2,
    CombatStatistics& player1Stats,
    CombatStatistics& player2Stats,
    bool showLog
)
{
    player1Stats = CombatStatistics{};
    player2Stats = CombatStatistics{};

    showCombatLog = showLog;

    constexpr int MAX_ROUNDS = 10;

    int round = 1;

    combatLog("\n=====================================\n");
    combatLog(player1.identity.name);
    combatLog(" vs ");
    combatLog(player2.identity.name);
    combatLog("\n=====================================\n");

    while(
        battleContinues(player1, player2) &&
        round <= MAX_ROUNDS
    )
    {
        combatLog("\n=====================================\n");
        combatLog("ROUND ");
        combatLog(round);
        combatLog("\n=====================================\n");

        executeTurn(
            player1,
            player2,
            player1Stats,   
            player2Stats
        );

        if(player2.health.alive)
        {
            executeTurn(
                player2,
                player1,
                player2Stats,
                player1Stats
            );
        }

        combatLog("\n");
        combatLog(player1.identity.name);
        combatLog(" HP: ");
        combatLog(player1.health.hp);
        combatLog("/");
        combatLog(player1.health.maxHp);

        if(player1.health.tempHp > 0)
        {
            combatLog(" (+");
            combatLog(player1.health.tempHp);
            combatLog(")");
        }

        combatLog("\n");

        combatLog(player2.identity.name);
        combatLog(" HP: ");
        combatLog(player2.health.hp);
        combatLog("/");
        combatLog(player2.health.maxHp);

        if(player2.health.tempHp > 0)
        {
            combatLog(" (+");
            combatLog(player2.health.tempHp);
            combatLog(")");
        }

        combatLog("\n");

        round++;
    }

    BattleResult result;

    if(player1.health.alive && !player2.health.alive)
    {
        result = BattleResult::Player1Win;

        registerVictory(
            player1Stats,
            player2Stats
        );

        combatLog("\n");
        combatLog(player1.identity.name);
        combatLog(" wins!\n");
    }
    else if(player2.health.alive && !player1.health.alive)
    {
        result = BattleResult::Player2Win;

        registerVictory(
            player2Stats,
            player1Stats
        );

        combatLog("\n");
        combatLog(player2.identity.name);
        combatLog(" wins!\n");
    }
    else
    {
        if(player1.health.hp > player2.health.hp)
        {
            result = BattleResult::Player1Win;

            registerVictory(
                player1Stats,
                player2Stats
            );

            combatLog("\nMaximum rounds reached.\n");
            combatLog(player1.identity.name);
            combatLog(" wins by remaining HP.\n");
        }
        else if(player2.health.hp > player1.health.hp)
        {
            result = BattleResult::Player2Win;

            registerVictory(
                player2Stats,
                player1Stats
            );

            combatLog("\nMaximum rounds reached.\n");
            combatLog(player2.identity.name);
            combatLog(" wins by remaining HP.\n");
        }
        else
        {
            result = BattleResult::Draw;

            combatLog("\nMaximum rounds reached.\n");
            combatLog("Draw.\n");
        }
    }

    player1Stats.roundsSurvived = round - 1;
    player2Stats.roundsSurvived = round - 1;

    calculateFinalStatistics(player1Stats);
    calculateFinalStatistics(player2Stats);

    combatLog("\n=====================================\n");
    combatLog("FINAL HP\n");
    combatLog("=====================================\n");

    combatLog(player1.identity.name);
    combatLog(": ");
    combatLog(player1.health.hp);
    combatLog("/");
    combatLog(player1.health.maxHp);

    if(player1.health.tempHp > 0)
    {
        combatLog(" (+");
        combatLog(player1.health.tempHp);
        combatLog(")");
    }

    combatLog("\n");

    combatLog(player2.identity.name);
    combatLog(": ");
    combatLog(player2.health.hp);
    combatLog("/");
    combatLog(player2.health.maxHp);

    if(player2.health.tempHp > 0)
    {
        combatLog(" (+");
        combatLog(player2.health.tempHp);
        combatLog(")");
    }

    combatLog("\n=====================================\n");

    return result;
}