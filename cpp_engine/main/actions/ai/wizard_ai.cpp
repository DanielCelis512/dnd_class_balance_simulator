#include "wizard_ai.h"

#include "specials/wizard_specials.h"

#include "../../dice.h"

namespace
{

/////////////////////////////////////////////////////
// Arcane Recovery
/////////////////////////////////////////////////////

bool shouldUseArcaneRecovery(
    const Character& wizard
)
{
    if(!canUseArcaneRecovery(wizard))
        return false;

    return
        wizard.spellSlots.current[1] == 0;
}

/////////////////////////////////////////////////////
// Arcane Vigor
/////////////////////////////////////////////////////

bool shouldCastArcaneVigor(
    const Character& wizard
)
{
    if(!canCastArcaneVigor(wizard))
        return false;

    return
        wizard.health.hp <=
        wizard.health.maxHp / 3;
}

/////////////////////////////////////////////////////
// False Life
/////////////////////////////////////////////////////

bool shouldCastFalseLife(
    const Character& wizard
)
{
    if(!canCastFalseLife(wizard))
        return false;

    return
        wizard.health.tempHp == 0;
}

/////////////////////////////////////////////////////
// Tasha
/////////////////////////////////////////////////////

bool shouldCastTashas(
    const Character& wizard,
    const Character& target
)
{
    if(!canCastTashas(wizard))
        return false;

    if(target.status.incapacitated)
        return false;

    return rollDice(1,100) <= 40;
}

/////////////////////////////////////////////////////
// Chromatic Orb
/////////////////////////////////////////////////////

bool shouldCastChromaticOrb(
    const Character& wizard
)
{
    if(!canCastChromaticOrb(wizard))
        return false;

    return rollDice(1,100) <= 60;
}

/////////////////////////////////////////////////////
// Magic Missile
/////////////////////////////////////////////////////

bool shouldCastMagicMissile(
    const Character& wizard,
    const Character& target
)
{
    if(!canCastMagicMissile(wizard))
        return false;

    //------------------------------------------
    // Finish weakened enemies
    //------------------------------------------

    if(
        target.health.hp <=
        target.health.maxHp / 4
    )
    {
        return true;
    }

    return rollDice(1,100) <= 35;
}

/////////////////////////////////////////////////////
// Main Action
/////////////////////////////////////////////////////

void chooseAction(
    Character& wizard,
    Character& target
)
{
    //------------------------------------------
    // Recover spell slots
    //------------------------------------------

    if(
        shouldUseArcaneRecovery(
            wizard
        )
    )
    {
        useArcaneRecovery(
            wizard
        );

        return;
    }

    //------------------------------------------
    // Heal
    //------------------------------------------

    if(
        shouldCastArcaneVigor(
            wizard
        )
    )
    {
        castArcaneVigor(
            wizard
        );

        return;
    }

    //------------------------------------------
    // Temp HP
    //------------------------------------------

    if(
        shouldCastFalseLife(
            wizard
        )
    )
    {
        castFalseLife(
            wizard
        );

        return;
    }

    //------------------------------------------
    // Control
    //------------------------------------------

    if(
        shouldCastTashas(
            wizard,
            target
        )
    )
    {
        castTashas(
            wizard,
            target
        );

        return;
    }

    //------------------------------------------
    // Strong spell
    //------------------------------------------

    if(
        shouldCastChromaticOrb(
            wizard
        )
    )
    {
        castChromaticOrb(
            wizard,
            target
        );

        return;
    }

    //------------------------------------------
    // Guaranteed damage
    //------------------------------------------

    if(
        shouldCastMagicMissile(
            wizard,
            target
        )
    )
    {
        castMagicMissile(
            wizard,
            target
        );

        return;
    }

    //------------------------------------------
    // Cantrip
    //------------------------------------------

    castPoisonSpray(
        wizard,
        target
    );
}

/////////////////////////////////////////////////////
// End Turn
/////////////////////////////////////////////////////

void finishTurn(
    Character&
)
{
}

}

/////////////////////////////////////////////////////
// Wizard AI
/////////////////////////////////////////////////////

void wizardTurnAI(
    Character& wizard,
    Character& target
)
{
    chooseAction(
        wizard,
        target
    );

    finishTurn(
        wizard
    );
}