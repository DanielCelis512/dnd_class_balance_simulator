#include "turn_manager.h"
#include "actions.h"

#include <iostream>

void takeTurn(Character& attacker,
              Character& defender)
{
    switch(attacker.classType)
    {
        case ClassType::Barbarian:
            attack(attacker, defender);
            break;

        case ClassType::Wizard:
            attack(attacker, defender);
            break;

        default:
            attack(attacker, defender);
            break;
    }
}