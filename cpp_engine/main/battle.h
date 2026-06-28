#ifndef BATTLE_H
#define BATTLE_H

#include "character.h"

enum class BattleResult
{
    Player1Win,
    Player2Win,
    Draw
};

BattleResult battle(
    Character& player1,
    Character& player2,
    bool showLog = true
);

#endif