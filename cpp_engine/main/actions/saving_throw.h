#ifndef SAVING_THROW_H
#define SAVING_THROW_H

#include "../character.h"

//==================================================
// Spell Save DC
//==================================================

int getSpellSaveDC(
    const Character& caster
);

//==================================================
// Saving Throw
//==================================================

bool performSavingThrow(
    const Character& caster,
    Character& target,
    SaveType saveType
);

//==================================================
// Helpers
//==================================================

int getSavingThrowModifier(
    const Character& target,
    SaveType saveType
);

int rollSavingThrowD20(
    const Character& target,
    SaveType saveType
);

#endif