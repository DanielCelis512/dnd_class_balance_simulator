#include "conditions.h"

/////////////////////////////////////////////////////
// Prone
/////////////////////////////////////////////////////

void applyProne(
    Character& target
)
{
    target.status.prone = true;

    //------------------------------------------
    // Melee attacks gain advantage.
    // Ranged attacks gain disadvantage.
    // (Handled inside Action Executor.)
    //------------------------------------------
}

void removeProne(
    Character& target
)
{
    target.status.prone = false;
}

/////////////////////////////////////////////////////
// Grappled
/////////////////////////////////////////////////////

void applyGrappled(
    Character& target
)
{
    target.status.grappled = true;
}

void removeGrappled(
    Character& target
)
{
    target.status.grappled = false;
}

/////////////////////////////////////////////////////
// Restrained
/////////////////////////////////////////////////////

void applyRestrained(
    Character& target
)
{
    target.status.restrained = true;

    //------------------------------------------
    // Cannot move
    //------------------------------------------

    target.status.speedReducedToZero = true;

    //------------------------------------------
    // Attacks against target
    //------------------------------------------

    target.status.grantsAdvantageToAttackers = true;

    //------------------------------------------
    // Own attacks
    //------------------------------------------

    target.status.hasAttackDisadvantage = true;

    //------------------------------------------
    // Saving Throws
    //------------------------------------------

    target.status.dexteritySaveDisadvantage = true;
}

void removeRestrained(
    Character& target
)
{
    target.status.restrained = false;

    target.status.speedReducedToZero = false;

    target.status.grantsAdvantageToAttackers = false;

    target.status.hasAttackDisadvantage = false;

    target.status.dexteritySaveDisadvantage = false;
}

/////////////////////////////////////////////////////
// Incapacitated
/////////////////////////////////////////////////////

void applyIncapacitated(
    Character& target
)
{
    target.status.incapacitated = true;

    //------------------------------------------
    // Cannot act
    //------------------------------------------

    target.status.canTakeActions = false;

    target.status.canTakeBonusActions = false;

    target.status.canTakeReactions = false;
}

void removeIncapacitated(
    Character& target
)
{
    target.status.incapacitated = false;

    target.status.canTakeActions = true;

    target.status.canTakeBonusActions = true;

    target.status.canTakeReactions = true;
}

/////////////////////////////////////////////////////
// Stunned
/////////////////////////////////////////////////////

void applyStunned(
    Character& target
)
{
    target.status.stunned = true;

    applyIncapacitated(target);

    target.status.grantsAdvantageToAttackers = true;

    target.status.strengthSaveDisadvantage = true;

    target.status.dexteritySaveDisadvantage = true;
}

void removeStunned(
    Character& target
)
{
    target.status.stunned = false;

    removeIncapacitated(target);

    target.status.grantsAdvantageToAttackers = false;

    target.status.strengthSaveDisadvantage = false;

    target.status.dexteritySaveDisadvantage = false;
}

/////////////////////////////////////////////////////
// Frightened
/////////////////////////////////////////////////////

void applyFrightened(
    Character& target
)
{
    target.status.frightened = true;
}

void removeFrightened(
    Character& target
)
{
    target.status.frightened = false;
}

/////////////////////////////////////////////////////
// Poisoned
/////////////////////////////////////////////////////

void applyPoisoned(
    Character& target
)
{
    target.status.poisoned = true;

    target.status.hasAttackDisadvantage = true;
}

void removePoisoned(
    Character& target
)
{
    target.status.poisoned = false;

    target.status.hasAttackDisadvantage = false;
}

/////////////////////////////////////////////////////
// Round Update
/////////////////////////////////////////////////////

void updateConditions(
    Character& character
)
{
    //------------------------------------------
    // Restrained
    //------------------------------------------

    if(
        character.status.restrained &&
        character.timers.restrainedRounds > 0
    )
    {
        character.timers.restrainedRounds--;

        if(
            character.timers.restrainedRounds <= 0
        )
        {
            removeRestrained(
                character
            );
        }
    }

    //------------------------------------------
    // Frightened
    //------------------------------------------

    if(
        character.status.frightened &&
        character.timers.frightenedRounds > 0
    )
    {
        character.timers.frightenedRounds--;

        if(
            character.timers.frightenedRounds <= 0
        )
        {
            removeFrightened(
                character
            );
        }
    }

    //------------------------------------------
    // Poisoned
    //------------------------------------------

    if(
        character.status.poisoned &&
        character.timers.poisonedRounds > 0
    )
    {
        character.timers.poisonedRounds--;

        if(
            character.timers.poisonedRounds <= 0
        )
        {
            removePoisoned(
                character
            );
        }
    }

    //------------------------------------------
    // Stunned
    //------------------------------------------

    if(
        character.status.stunned &&
        character.timers.stunnedRounds > 0
    )
    {
        character.timers.stunnedRounds--;

        if(
            character.timers.stunnedRounds <= 0
        )
        {
            removeStunned(
                character
            );
        }
    }
}