#ifndef SIMULATION_H
#define SIMULATION_H

#include "character.h"

void simulateBattles(
    Character player1,
    Character player2,
    int simulations,
    bool showLog = false
);

#endif