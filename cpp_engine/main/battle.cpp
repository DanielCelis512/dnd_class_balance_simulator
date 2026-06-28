#include "battle.h"

#include "logger.h"
#include "turn_manager.h"

BattleResult battle(
    Character& player1,
    Character& player2,
    bool showLog
)
{
    showCombatLog = showLog;

    const int maxRounds = 10;
    int round = 1;

    combatLog("\n=====================================\n");
    combatLog(player1.name);
    combatLog(" vs ");
    combatLog(player2.name);
    combatLog("\n");
    combatLog("=====================================\n");

    while(player1.alive &&
          player2.alive &&
          round <= maxRounds)
    {
        combatLog("\n=====================================\n");
        combatLog("             ROUND ");
        combatLog(round);
        combatLog("\n");
        combatLog("=====================================\n");

        executeTurn(
            player1,
            player2
        );

        if(player2.alive)
        {
            executeTurn(
                player2,
                player1
            );
        }

        combatLog("\n-------------------------------------\n");

        combatLog(player1.name);
        combatLog(" HP: ");
        combatLog(player1.hp);
        combatLog("/");
        combatLog(player1.maxHp);

        if(player1.tempHp > 0)
        {
            combatLog(" (+");
            combatLog(player1.tempHp);
            combatLog(" Temp)");
        }

        combatLog("\n");

        combatLog(player2.name);
        combatLog(" HP: ");
        combatLog(player2.hp);
        combatLog("/");
        combatLog(player2.maxHp);

        if(player2.tempHp > 0)
        {
            combatLog(" (+");
            combatLog(player2.tempHp);
            combatLog(" Temp)");
        }

        combatLog("\n");
        combatLog("-------------------------------------\n");

        round++;
    }

    combatLog("\n=====================================\n");
    combatLog("          BATTLE RESULT\n");
    combatLog("=====================================\n");

    BattleResult result;

    if(player1.alive &&
       !player2.alive)
    {
        combatLog(player1.name);
        combatLog(" wins by knockout!\n");

        result = BattleResult::Player1Win;
    }
    else if(player2.alive &&
            !player1.alive)
    {
        combatLog(player2.name);
        combatLog(" wins by knockout!\n");

        result = BattleResult::Player2Win;
    }
    else if(player1.hp > player2.hp)
    {
        combatLog("Maximum rounds reached.\n");
        combatLog(player1.name);
        combatLog(" wins by remaining HP!\n");

        result = BattleResult::Player1Win;
    }
    else if(player2.hp > player1.hp)
    {
        combatLog("Maximum rounds reached.\n");
        combatLog(player2.name);
        combatLog(" wins by remaining HP!\n");

        result = BattleResult::Player2Win;
    }
    else
    {
        combatLog("Maximum rounds reached.\n");
        combatLog("Battle ends in a draw.\n");

        result = BattleResult::Draw;
    }

    combatLog("\nFinal HP:\n");

    combatLog(player1.name);
    combatLog(": ");
    combatLog(player1.hp);
    combatLog("/");
    combatLog(player1.maxHp);

    if(player1.tempHp > 0)
    {
        combatLog(" (+");
        combatLog(player1.tempHp);
        combatLog(" Temp)");
    }

    combatLog("\n");

    combatLog(player2.name);
    combatLog(": ");
    combatLog(player2.hp);
    combatLog("/");
    combatLog(player2.maxHp);

    if(player2.tempHp > 0)
    {
        combatLog(" (+");
        combatLog(player2.tempHp);
        combatLog(" Temp)");
    }

    combatLog("\n");
    combatLog("=====================================\n");

    return result;
}