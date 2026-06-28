#ifndef CLASS_FACTORY_H
#define CLASS_FACTORY_H

#include "character.h"

// Function declarations for creating characters of different classes
Character createBarbarian();
Character createBard();
Character createCleric();
Character createDruid();
Character createFighter();
Character createMonk();
Character createPaladin();
Character createRanger();
Character createRogue();
Character createSorcerer();
Character createWarlock();
Character createWizard();

Character createCharacter(ClassType classType);

#endif