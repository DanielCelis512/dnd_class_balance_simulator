#include "spell_effects.h"

#include "combat_utils.h"
#include "dice.h"

#include "specials/paladin_specials.h"


namespace
{

/////////////////////////////////////////////////////
// Individual Spell Effects
/////////////////////////////////////////////////////

void applyShieldOfFaith(
    Character& caster,
    Character&,
    AttackResolution&
)
{
    caster.status.concentrating = true;

    caster.status.shieldOfFaith = true;

    caster.bonusAc += 2;

    caster.timers.shieldOfFaithRounds = 10;
}

void applyDivineSmite(
    Character& caster,
    Character& target,
    AttackResolution& result
)
{
    //------------------------------------------
    // Must be prepared
    //------------------------------------------

    if(
        !caster.status.divineSmiteReady
    )
    {
        return;
    }

    //------------------------------------------
    // Extra radiant damage
    //------------------------------------------

    int radiantDamage =
        rollDice(2,8);

    //------------------------------------------
    // Critical hit
    //------------------------------------------

    if(
        result.attackResult ==
        AttackResult::CriticalHit
    )
    {
        radiantDamage +=
            rollDice(2,8);
    }

    //------------------------------------------
    // Apply damage
    //------------------------------------------

    dealDamage(
        caster,
        target,
        radiantDamage,
        DamageType::Radiant
    );

    //------------------------------------------
    // Statistics
    //------------------------------------------

    registerDivineSmite(
        caster.statistics
    );

    //------------------------------------------
    // Consume
    //------------------------------------------

    consumeDivineSmite(
        caster
    );
}

void applyGuidingBolt(
    Character&,
    Character&,
    AttackResolution&
)
{
}

void applyViciousMockery(
    Character&,
    Character&,
    AttackResolution&
)
{
}

void applyTashas(
    Character&,
    Character&,
    AttackResolution&
)
{
}

void applyEntangle(
    Character&,
    Character&,
    AttackResolution&
)
{
}

void applyShillelagh(
    Character&,
    Character&,
    AttackResolution&
)
{
}

void applyFalseLife(
    Character&,
    Character&,
    AttackResolution&
)
{
}

void applySorcerousBurst(
    Character&,
    Character&,
    AttackResolution&
)
{
}

}

/////////////////////////////////////////////////////
// Dispatcher
/////////////////////////////////////////////////////

void applySpellEffect(
    Character& caster,
    Character& target,
    const MagicalAction& spell,
    AttackResolution& result
)
{
    switch(spell.effect)
{
    //--------------------------------------------------
    // Cleric
    //--------------------------------------------------

    case SpellEffectType::GuidingBolt:

        applyGuidingBolt(
            caster,
            target,
            result
        );
        break;

    case SpellEffectType::ShieldOfFaith:

        applyShieldOfFaith(
            caster,
            target,
            result
        );
        break;

    //--------------------------------------------------
    // Druid
    //--------------------------------------------------

    case SpellEffectType::Entangle:

        applyEntangle(
            caster,
            target,
            result
        );
        break;

    case SpellEffectType::Shillelagh:

        applyShillelagh(
            caster,
            target,
            result
        );
        break;

    case SpellEffectType::FalseLife:

        applyFalseLife(
            caster,
            target,
            result
        );
        break;

    //--------------------------------------------------
    // Bard
    //--------------------------------------------------

    case SpellEffectType::ViciousMockery:

        applyViciousMockery(
            caster,
            target,
            result
        );
        break;

    case SpellEffectType::TashasHideousLaughter:

        applyTashas(
            caster,
            target,
            result
        );
        break;

    //--------------------------------------------------
    // Sorcerer
    //--------------------------------------------------

    case SpellEffectType::SorcerousBurst:

        applySorcerousBurst(
            caster,
            target,
            result
        );
        break;

    //--------------------------------------------------
    // Paladin
    //--------------------------------------------------

    case SpellEffectType::DivineSmite:

        applyDivineSmite(
            caster,
            target,
            result
        );
        break;

    default:
        break;
}

}