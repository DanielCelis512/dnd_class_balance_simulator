#include "action_executor.h"

#include "physical_actions.h"
#include "magical_actions.h"


namespace
{

void beforeAttackRoll(
    Character& attacker,
    Character& defender
)
{
    // Futuro:
    // Cutting Words
}

void beforeSpellAttack(
    Character& caster,
    Character& target
)
{
    // Futuro:
    // Cutting Words
}

void beforeSavingThrow(
    Character& caster,
    Character& target
)
{
    // Futuro:
    // Cutting Words
}

void beforeDamage(
    Character& attacker,
    Character& defender
)
{
    // Futuro:
    // Blade Ward
    // Cutting Words
}

}

//==================================================
// Physical
//==================================================

AttackResolution executePhysicalAttack(
    Character& attacker,
    Character& defender
)
{
    //--------------------------------------------------
    // Advantage
    //--------------------------------------------------

    bool hasAdvantage = false;
    bool hasDisadvantage = false;

    //--------------------------------------------------
    // Attacker
    //--------------------------------------------------

    if(attacker.status.hasAdvantage)
        hasAdvantage = true;

    if(attacker.status.hasDisadvantage)
        hasDisadvantage = true;

    if(attacker.status.grantsAdvantageToAttack)
        hasAdvantage = true;

    if(attacker.status.grantsDisadvantageToAttack)
        hasDisadvantage = true;

    //--------------------------------------------------
    // Defender
    //--------------------------------------------------

    if(defender.status.attackersHaveAdvantage)
        hasAdvantage = true;

    if(defender.status.attackersHaveDisadvantage)
        hasDisadvantage = true;

    //--------------------------------------------------
    // Cancel
    //--------------------------------------------------

    if(hasAdvantage && hasDisadvantage)
    {
        hasAdvantage = false;
        hasDisadvantage = false;
    }

    //--------------------------------------------------
    // Execute
    //--------------------------------------------------

    return resolvePhysicalAttack(
        attacker,
        defender,
        attacker.physical,
        hasAdvantage,
        hasDisadvantage
    );
}

//==================================================
// Spell
//==================================================

AttackResolution executeSpell(
    Character& caster,
    Character& target,
    int spellIndex
)
{
    return resolveSpell(
        caster,
        target,
        spellIndex
    );
}

//==================================================
// Cantrip
//==================================================

AttackResolution executeCantrip(
    Character& caster,
    Character& target,
    int cantripIndex
)
{
    return resolveCantrip(
        caster,
        target,
        cantripIndex
    );
}

//==================================================
// Special
//==================================================

void executeSpecial(
    Character& user,
    Character& target,
    int specialIndex
)
{
    (void)user;
    (void)target;
    (void)specialIndex;

    // Actualmente los especiales se ejecutan
    // directamente desde cada archivo
    // *_specials.cpp.
}