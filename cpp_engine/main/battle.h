#ifndef BATTLE_H
#define BATTLE_H

#include "character.h"
#include "combat_statistics.h"

enum class BattleResult
{
    Player1Win,
    Player2Win,
    Draw
};

BattleResult battle(
    Character& player1,
    Character& player2,
    CombatStatistics& player1Stats,
    CombatStatistics& player2Stats,
    bool showLog = true
);

#endif