#include "saving_throw.h"

#include "../dice.h"

#include <algorithm>

/////////////////////////////////////////////////////
// Spell Save DC
/////////////////////////////////////////////////////

int getSpellSaveDC(
    const Character& caster
)
{
    return
        8
        +
        caster.proficiencyBonus
        +
        caster.spellcastingModifier;
}

/////////////////////////////////////////////////////
// Saving Throw Modifier
/////////////////////////////////////////////////////

int getSavingThrowModifier(
    const Character& target,
    SaveType saveType
)
{
    switch(saveType)
    {
        case SaveType::Strength:
            return target.savingThrows.str;

        case SaveType::Dexterity:
            return target.savingThrows.dex;

        case SaveType::Constitution:
            return target.savingThrows.con;

        case SaveType::Intelligence:
            return target.savingThrows.intel;

        case SaveType::Wisdom:
            return target.savingThrows.wis;

        case SaveType::Charisma:
            return target.savingThrows.cha;     
    }

    return 0;
}

/////////////////////////////////////////////////////
// Saving Throw Roll
/////////////////////////////////////////////////////

int rollSavingThrowD20(
    const Character& target,
    SaveType saveType
)
{
    int roll =
        rollDice(
            1,
            20
        );

    return
        roll +
        getSavingThrowModifier(
            target,
            saveType
        );
}

/////////////////////////////////////////////////////
// Saving Throw
/////////////////////////////////////////////////////

bool performSavingThrow(
    const Character& caster,
    Character& target,
    SaveType saveType
)
{
    int dc =
        getSpellSaveDC(
            caster
        );

    int result =
        rollSavingThrowD20(
            target,
            saveType
        );

    return result >= dc;
}