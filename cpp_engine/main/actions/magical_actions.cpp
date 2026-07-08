#include "magical_actions.h"

#include "../combat_utils.h"
#include "../combat/combat_modifiers.h"
#include "../actions/spell_utils.h"
#include "../actions/saving_throw.h"
#include "spell_effects.h"

#include "../dice.h"

#include "../combat/combat_statistics.h"


static AttackResolution resolveMagic(
    Character& caster,
    Character& target,
    MagicalAction& spell
);

AttackResolution resolveSpell(
    Character& caster,
    Character& target,
    int spellIndex
)
{
    AttackResolution result;

    if(
        spellIndex < 0 ||
        spellIndex >= caster.spells.size()
    )
    {
        return result;
    }

    MagicalAction& spell =
        caster.spells[spellIndex];

    return resolveMagic(
        caster,
        target,
        spell
    );
}

AttackResolution resolveCantrip(
    Character& caster,
    Character& target,
    int cantripIndex
)
{
    AttackResolution result;

    if(
        cantripIndex < 0 ||
        cantripIndex >= caster.cantrips.size()
    )
    {
        return result;
    }

    MagicalAction& cantrip =
        caster.cantrips[cantripIndex];

    return resolveMagic(
        caster,
        target,
        cantrip
    );
}

static AttackResolution resolveMagic(
    Character& caster,
    Character& target,
    MagicalAction& spell
)
{
    AttackResolution result;

    //------------------------------------------
    // Can Cast
    //------------------------------------------

    if(!canCastSpell(caster, spell))
    {
        return result;
    }

    castSpell(caster, spell);

    //--------------------------------------------------
    // Attack Roll Spells
    //--------------------------------------------------

    if(spell.magicType == MagicType::AttackRoll)
    {
        int attackRoll =
            rollD20();

        int attackTotal =
            attackRoll +
            spell.attackBonus;

        attackTotal =
            modifySpellAttackRoll(
                caster,
                target,
                attackTotal
            );

        if(attackRoll == 1)
        {
            result.attackResult =
                AttackResult::CriticalMiss;

            return result;
        }

        bool critical =
            attackRoll >=
            caster.combat.criticalRange;

        int defenderAC =
            target.ac +
            target.bonusAc;

        if(!critical &&
           attackTotal < defenderAC)
        {
            result.attackResult =
                AttackResult::Miss;

            return result;
        }

        int damage =
            rollDice(
                spell.effectDiceNumber,
                spell.effectDiceSides
            );

        damage +=
            spell.effectModifier;

        damage =
            modifySpellDamage(
                caster,
                target,
                damage
            );

        if(critical)
        {
            damage =
                applyCriticalDamage(
                    damage,
                    0,
                    caster.combat.criticalMultiplier
                );

            result.attackResult =
                AttackResult::CriticalHit;
        }
        else
        {
            result.attackResult =
                AttackResult::Hit;
        }

        if(hasImmunity(target,spell.damageType))
        {
            result.damageResult =
                DamageResult::Immune;
        }
        else if(hasResistance(target,spell.damageType))
        {
            result.damageResult =
                DamageResult::Resistant;
        }
        else if(hasVulnerability(target,spell.damageType))
        {
            result.damageResult =
                DamageResult::Vulnerable;
        }
        else
        {
            result.damageResult =
                DamageResult::Normal;
        }

        damage =
            resolveDamage(
                damage,
                result.damageResult
            );

        result.damage =
            damage;

        applyDamage(
            target,
            damage
        );

        applySpellEffect(
            caster,
            target,
            spell,
            result
        );

        if(target.status.concentrating)
        {
            result.concentrationBroken =
                requiresConcentrationCheck(
                    damage
                );
        }

        return result;
    }

    //--------------------------------------------------
    // Saving Throw Spells
    //--------------------------------------------------

    if(spell.magicType == MagicType::SavingThrow)
    {
        bool success =
            performSavingThrow(
                caster,
                target,
                spell.saveType
            );

        success =
            modifySavingThrowResult(
                caster,
                target,
                0,
                0
            );

        if(success)
        {
            result.attackResult =
                AttackResult::Miss;

            return result;
        }

        int damage =
            rollDice(
                spell.effectDiceNumber,
                spell.effectDiceSides
            );

        damage +=
            spell.effectModifier;

        damage =
            modifySpellDamage(
                caster,
                target,
                damage
            );

        if(hasImmunity(target,spell.damageType))
        {
            result.damageResult =
                DamageResult::Immune;
        }
        else if(hasResistance(target,spell.damageType))
        {
            result.damageResult =
                DamageResult::Resistant;
        }
        else if(hasVulnerability(target,spell.damageType))
        {
            result.damageResult =
                DamageResult::Vulnerable;
        }
        else
        {
            result.damageResult =
                DamageResult::Normal;
        }

        damage =
            resolveDamage(
                damage,
                result.damageResult
            );

        result.damage =
            damage;

        applyDamage(
            target,
            damage
        );

        applySpellEffect(
            caster,
            target,
            spell,
            result
        );

        if(target.status.concentrating)
        {
            result.concentrationBroken =
                requiresConcentrationCheck(
                    damage
                );
        }

        result.attackResult =
            AttackResult::Hit;

        return result;
    }

    //--------------------------------------------------
    // Healing
    //--------------------------------------------------

    if(spell.magicType == MagicType::Healing)
    {
        int healing =
            rollDice(
                spell.effectDiceNumber,
                spell.effectDiceSides
            );

        healing +=
            spell.effectModifier;

        healCharacter(
            caster,
            healing
        );

        registerHealing(
            caster.statistics,
            caster.statistics,
            healing
        );

        result.attackResult =
            AttackResult::Hit;

        return result;
    }

    return result;
}
