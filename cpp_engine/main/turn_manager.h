#ifndef TURN_MANAGER_H
#define TURN_MANAGER_H

#include "character.h"

// Ejecuta un turno completo
void executeTurn(
    Character& current,
    Character& enemy
);

// Decide la acción que realizará el personaje
void chooseAction(
    Character& current,
    Character& enemy
);

// Ejecuta la acción elegida
bool performAction(
    Character& current,
    Character& enemy
);

#endif