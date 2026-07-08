#include "physical_actions.h"

#include "character.h"
#include "magical_actions.h"
#include "spell_utils.h"
#include "spell_effects.h"

#include "../combat_utils.h"
#include "../combat/combat_modifiers.h"
#include "../dice.h"


//==================================================
// Physical Attack
//==================================================

AttackResolution resolvePhysicalAttack(
    Character& attacker,
    Character& defender,
    PhysicalAction& action,
    bool hasAdvantage,
    bool hasDisadvantage
)
{
    AttackResolution result;

    //--------------------------------------------------
    // Attack Roll
    //--------------------------------------------------

    int attackRoll;

    if(hasAdvantage)
    {
        attackRoll =
            std::max(
                rollD20(),
                rollD20()
            );
    }
    else if(hasDisadvantage)
    {
        attackRoll =
            std::min(
                rollD20(),
                rollD20()
            );
    }
    else
    {
        attackRoll =
            rollD20();
    }

    int attackTotal =
        attackRoll +
        action.attackBonus;

    attackTotal =
        modifyAttackRoll(
            attacker,
            defender,
            attackTotal
        );

    int defenderAC =
        defender.ac +
        defender.bonusAc;

    //--------------------------------------------------
    // Critical Miss
    //--------------------------------------------------

    if(attackRoll == 1)
    {
        result.attackResult =
            AttackResult::CriticalMiss;

        return result;
    }

    //--------------------------------------------------
    // Critical Hit
    //--------------------------------------------------

    bool critical =
        attackRoll >=
        attacker.combat.criticalRange;

    //--------------------------------------------------
    // Miss
    //--------------------------------------------------

    if(!critical &&
       attackTotal < defenderAC)
    {
        result.attackResult =
            AttackResult::Miss;

        return result;
    }

    //--------------------------------------------------
    // Damage Dice
    //--------------------------------------------------

    int damage = rollDice(
        action.damageDiceNumber,
        action.damageDiceSides
    );

    damage +=
        rollDice(
            action.extraDamageDiceNumber,
            action.extraDamageDiceSides
        );

    damage +=
        action.damageModifier;

    damage +=
        action.extraDamageModifier;

    //--------------------------------------------------
    // Critical
    //--------------------------------------------------

    if(critical)
    {
        result.attackResult =
            AttackResult::CriticalHit;

        damage =
            applyCriticalDamage(
                damage,
                0,
                attacker.combat.criticalMultiplier
            );
    }
    else
    {
        result.attackResult =
            AttackResult::Hit;
    }

    //--------------------------------------------------
    // Resistances
    //--------------------------------------------------

    if(hasImmunity(
        defender,
        action.damageType))
    {
        result.damageResult =
            DamageResult::Immune;
    }
    else if(hasResistance(
        defender,
        action.damageType))
    {
        result.damageResult =
            DamageResult::Resistant;
    }
    else if(hasVulnerability(
        defender,
        action.damageType))
    {
        result.damageResult =
            DamageResult::Vulnerable;
    }
    else
    {
        result.damageResult =
            DamageResult::Normal;
    }

    //--------------------------------------------------
    // Final Damage
    //--------------------------------------------------

    damage =
        modifyDamageRoll(
            attacker,
            defender,
            damage
    );

    result.damage = damage;

    //--------------------------------------------------
    // Apply
    //--------------------------------------------------

    applyDamage(
        defender,
        damage
    );

    //--------------------------------------------------
    // Concentration
    //--------------------------------------------------

    if(defender.status.concentrating)
    {
        result.concentrationBroken =
            requiresConcentrationCheck(
                damage
            );
    }

    return result;
}