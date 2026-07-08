#include "../combat/combat_modifiers.h"
#include "../saving_throw.h"
#include "../spell_utils.h"

#include "../../combat_actions.h"
#include "../../combat_utils.h"
#include "../../combat/combat_statistics.h"
#include "../../dice.h"

/////////////////////////////////////////////////////
// Arcane Recovery
/////////////////////////////////////////////////////

bool canUseArcaneRecovery(
    const Character& wizard
)
{
    if(!wizard.health.alive)
        return false;

    const SpecialAction* recovery =
        findSpecial(
            wizard,
            SpecialType::ArcaneRecovery
        );

    if(
        recovery == nullptr ||
        recovery->currentUses <= 0
    )
    {
        return false;
    }

    return
        wizard.spellSlots.current[1] <
        wizard.spellSlots.maximum[1];
}

void useArcaneRecovery(
    Character& wizard
)
{
    if(
        !canUseArcaneRecovery(
            wizard
        )
    )
    {
        return;
    }

    SpecialAction* recovery =
        findSpecial(
            wizard,
            SpecialType::ArcaneRecovery
        );

    recovery->currentUses--;

    wizard.spellSlots.current[1] =
        std::min(
            wizard.spellSlots.current[1] + 2,
            wizard.spellSlots.maximum[1]
        );
}

/////////////////////////////////////////////////////
// Portent
/////////////////////////////////////////////////////

bool canUseGoodPortent(
    const Character& wizard
)
{
    return
        wizard.status.goodPortentAvailable;
}

bool canUseBadPortent(
    const Character& wizard
)
{
    return
        wizard.status.badPortentAvailable;
}

int useGoodPortent(
    Character& wizard
)
{
    wizard.status.goodPortentAvailable =
        false;

    return 18;
}

int useBadPortent(
    Character& wizard
)
{
    wizard.status.badPortentAvailable =
        false;

    return 5;
}

/////////////////////////////////////////////////////
// Poison Spray
/////////////////////////////////////////////////////

bool canCastPoisonSpray(
    const Character&
)
{
    return true;
}

void castPoisonSpray(
    Character& wizard,
    Character& target
)
{
    const MagicalAction* spell =
        findCantrip(
            wizard,
            "Poison Spray"
        );

    if(spell == nullptr)
        return;

    int attackRoll =
        rollDice(1,20) +
        getSpellAttackBonus(wizard);

    attackRoll =
        modifySpellAttackRoll(
            wizard,
            target,
            attackRoll
        );

    if(
        attackRoll <
        target.ac
    )
    {
        return;
    }

    int damage =
        rollDice(1,12);

    damage =
        modifySpellDamage(
            wizard,
            target,
            damage
        );

    dealDamage(
        wizard,
        target,
        damage,
        DamageType::Poison
    );
}

/////////////////////////////////////////////////////
// Blade Ward
/////////////////////////////////////////////////////

bool canCastBladeWard(
    const Character&
)
{
    return true;
}

void castBladeWard(
    Character& wizard
)
{
    wizard.status.bladeWard =
        true;

    wizard.timers.bladeWardRounds =
        1;
}

/////////////////////////////////////////////////////
// Chromatic Orb
/////////////////////////////////////////////////////

bool canCastChromaticOrb(
    const Character& wizard
)
{
    return
        hasSpellSlot(
            wizard,
            SpellLevel::Level1
        );
}

void castChromaticOrb(
    Character& wizard,
    Character& target
)
{
    const MagicalAction* spell =
        findSpell(
            wizard,
            "Chromatic Orb"
        );

    if(
        spell == nullptr ||
        !castSpell(
            wizard,
            *spell
        )
    )
    {
        return;
    }

    int attackRoll =
        rollDice(1,20) +
        getSpellAttackBonus(wizard);

    attackRoll =
        modifySpellAttackRoll(
            wizard,
            target,
            attackRoll
        );

    if(
        attackRoll <
        target.ac
    )
    {
        return;
    }

    int damage =
        rollDice(3,8);

    damage =
        modifySpellDamage(
            wizard,
            target,
            damage
        );

    dealDamage(
        wizard,
        target,
        damage,
        DamageType::Force
    );
}

/////////////////////////////////////////////////////
// Magic Missile
/////////////////////////////////////////////////////

bool canCastMagicMissile(
    const Character& wizard
)
{
    return
        hasSpellSlot(
            wizard,
            SpellLevel::Level1
        );
}

void castMagicMissile(
    Character& wizard,
    Character& target
)
{
    const MagicalAction* spell =
        findSpell(
            wizard,
            "Magic Missile"
        );

    if(
        spell == nullptr ||
        !castSpell(
            wizard,
            *spell
        )
    )
    {
        return;
    }

    int damage =
        rollDice(3,4) + 3;

    damage =
        modifySpellDamage(
            wizard,
            target,
            damage
        );

    dealDamage(
        wizard,
        target,
        damage,
        DamageType::Force
    );
}

/////////////////////////////////////////////////////
// Tasha's Hideous Laughter
/////////////////////////////////////////////////////

bool canCastTashas(
    const Character& wizard
)
{
    return
        hasSpellSlot(
            wizard,
            SpellLevel::Level1
        );
}

void castTashas(
    Character& wizard,
    Character& target
)
{
    const MagicalAction* spell =
        findSpell(
            wizard,
            "Tasha's Hideous Laughter"
        );

    if(
        spell == nullptr ||
        !castSpell(
            wizard,
            *spell
        )
    )
    {
        return;
    }

    bool success =
        performSavingThrow(
            wizard,
            target,
            SaveType::Wisdom
        );

    success =
        modifySavingThrowResult(
            wizard,
            target,
            0,
            0
        );

    if(success)
        return;

    target.status.incapacitated =
        true;

    target.timers.incapacitatedRounds =
        3;

    wizard.status.concentrating =
        true;
}

/////////////////////////////////////////////////////
// Arcane Vigor
/////////////////////////////////////////////////////

bool canCastArcaneVigor(
    const Character& wizard
)
{
    return
        hasSpellSlot(
            wizard,
            SpellLevel::Level1
        );
}

void castArcaneVigor(
    Character& wizard
)
{
    const MagicalAction* spell =
        findSpell(
            wizard,
            "Arcane Vigor"
        );

    if(
        spell == nullptr ||
        !castSpell(
            wizard,
            *spell
        )
    )
    {
        return;
    }

    int healing =
        rollDice(1,6) + 4;

    healCharacter(
        wizard,
        healing
    );

    registerHealing(
        wizard.statistics,
        wizard.statistics,
        healing
    );
}

/////////////////////////////////////////////////////
// False Life
/////////////////////////////////////////////////////

bool canCastFalseLife(
    const Character& wizard
)
{
    return
        hasSpellSlot(
            wizard,
            SpellLevel::Level1
        );
}

void castFalseLife(
    Character& wizard
)
{
    const MagicalAction* spell =
        findSpell(
            wizard,
            "False Life"
        );

    if(
        spell == nullptr ||
        !castSpell(
            wizard,
            *spell
        )
    )
    {
        return;
    }

    int tempHp =
        rollDice(2,4) + 4;

    if(
        tempHp >
        wizard.health.tempHp
    )
    {
        wizard.health.tempHp =
            tempHp;
    }
}

/////////////////////////////////////////////////////
// Tasha's Hideous Laughter
/////////////////////////////////////////////////////

bool canCastTashas(
    const Character& wizard
)
{
    return
        hasSpellSlot(
            wizard,
            SpellLevel::Level1
        );
}

void castTashas(
    Character& wizard,
    Character& target
)
{
    const MagicalAction* spell =
        findSpell(
            wizard,
            "Tasha's Hideous Laughter"
        );

    if(
        spell == nullptr ||
        !castSpell(
            wizard,
            *spell
        )
    )
    {
        return;
    }

    bool success =
        performSavingThrow(
            wizard,
            target,
            SaveType::Wisdom
        );

    success =
        modifySavingThrowResult(
            wizard,
            target,
            0,
            0
        );

    if(success)
        return;

    target.status.incapacitated = true;
    target.timers.incapacitatedRounds = 3;

    wizard.status.concentrating = true;
}

/////////////////////////////////////////////////////
// Chromatic Orb
/////////////////////////////////////////////////////

bool canCastChromaticOrb(
    const Character& wizard
)
{
    return
        hasSpellSlot(
            wizard,
            SpellLevel::Level1
        );
}

void castChromaticOrb(
    Character& wizard,
    Character& target
)
{
    const MagicalAction* spell =
        findSpell(
            wizard,
            "Chromatic Orb"
        );

    if(
        spell == nullptr ||
        !castSpell(
            wizard,
            *spell
        )
    )
    {
        return;
    }

    int attackRoll =
        rollDice(1,20) +
        getSpellAttackBonus(
            wizard
        );

    attackRoll =
        modifySpellAttackRoll(
            wizard,
            target,
            attackRoll
        );

    if(
        attackRoll <
        target.ac
    )
    {
        return;
    }

    int damage =
        rollDice(3,8);

    damage =
        modifySpellDamage(
            wizard,
            target,
            damage
        );

    dealDamage(
        wizard,
        target,
        damage,
        DamageType::Force
    );
}

/////////////////////////////////////////////////////
// False Life
/////////////////////////////////////////////////////

bool canCastFalseLife(
    const Character& wizard
)
{
    return
        hasSpellSlot(
            wizard,
            SpellLevel::Level1
        );
}

void castFalseLife(
    Character& wizard
)
{
    const MagicalAction* spell =
        findSpell(
            wizard,
            "False Life"
        );

    if(
        spell == nullptr ||
        !castSpell(
            wizard,
            *spell
        )
    )
    {
        return;
    }

    int tempHp =
        rollDice(2,4) + 4;

    if(
        tempHp >
        wizard.health.tempHp
    )
    {
        wizard.health.tempHp =
            tempHp;
    }
}