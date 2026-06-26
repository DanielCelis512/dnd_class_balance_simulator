#ifndef BATTLE_H
#define BATTLE_H

#include "character.h"

// Function to conduct a battle between two characters
void battle(Character& character1,
            Character& character2);

// Function to print the status of a character
void printStatus(const Character& character);

#endif // BATTLE_H