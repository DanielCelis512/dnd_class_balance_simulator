#include "combat_modifiers.h"

#include "../specials/bard_specials.h"

/////////////////////////////////////////////////////
// Attack Rolls
/////////////////////////////////////////////////////

int modifyAttackRoll(
    Character& attacker,
    Character& defender,
    int attackTotal
)
{
    //------------------------------------------
    // Cutting Words
    //------------------------------------------

    if(
        canUseCuttingWords(
            defender,
            attackTotal,
            attacker
        )
    )
    {
        attackTotal -=
            useCuttingWordsAttack(
                defender
            );
    }

    return attackTotal;
}

int modifySpellAttackRoll(
    Character& caster,
    Character& target,
    int attackTotal
)
{
    if(
        canUseCuttingWords(
            target,
            attackTotal,
            caster
        )
    )
    {
        attackTotal -=
            useCuttingWordsAttack(
                target
            );
    }

    return attackTotal;
}

/////////////////////////////////////////////////////
// Damage
/////////////////////////////////////////////////////

int modifyDamageRoll(
    Character& attacker,
    Character& defender,
    int damage
)
{
    if(
        canReduceDamageWithCuttingWords(
            defender
        )
    )
    {
        damage -=
            useCuttingWordsDamage(
                defender
            );

        if(damage < 0)
            damage = 0;
    }

    return damage;
}

int modifySpellDamage(
    Character& caster,
    Character& target,
    int damage
)
{
    //------------------------------------------
    // Empowered Spell
    //------------------------------------------

    //------------------------------------------
    // Blade Ward
    //------------------------------------------

    return damage;
}

/////////////////////////////////////////////////////
// Saving Throws
/////////////////////////////////////////////////////

bool modifySavingThrowResult(
    Character& caster,
    Character& target,
    bool success
)
{
    //------------------------------------------
    // Cutting Words
    //------------------------------------------

    //------------------------------------------
    // Bardic Inspiration
    //------------------------------------------

    return success;
}