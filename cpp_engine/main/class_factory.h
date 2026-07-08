#ifndef CLASS_FACTORY_H
#define CLASS_FACTORY_H

#include "character.h"

//==================================================
// Character Factory
//==================================================

Character createBarbarian(
    const std::string& name
);

Character createBard(
    const std::string& name
);

Character createCleric(
    const std::string& name
);

Character createDruid(
    const std::string& name
);

Character createFighter(
    const std::string& name
);

Character createMonk(
    const std::string& name
);

Character createPaladin(
    const std::string& name
);

Character createRanger(
    const std::string& name
);

Character createRogue(
    const std::string& name
);

Character createSorcerer(
    const std::string& name
);

Character createWarlock(
    const std::string& name
);

Character createWizard(
    const std::string& name
);

//==================================================
// Generic Factory
//==================================================

Character createCharacter(
    ClassType classType,
    const std::string& name
);

#endif