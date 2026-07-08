#include "warlock_specials.h"

#include "../../combat_actions.h"
#include "../../combat_utils.h"
#include "../../combat/combat_statistics.h"
#include "../../dice.h"

#include "../spell_utils.h"
#include "../combat/combat_modifiers.h"

/////////////////////////////////////////////////////
// Imp
/////////////////////////////////////////////////////

bool canSummonImp(
    const Character& warlock
)
{
    if(!warlock.health.alive)
        return false;

    if(warlock.status.impActive)
        return false;

    const SpecialAction* imp =
        findSpecial(
            warlock,
            SpecialType::Imp
        );

    if(imp == nullptr)
        return false;

    return
        imp->currentUses > 0;
}

void summonImp(
    Character& warlock
)
{
    if(!canSummonImp(warlock))
        return;

    SpecialAction* imp =
        findSpecial(
            warlock,
            SpecialType::Imp
        );

    if(imp == nullptr)
        return;

    imp->currentUses--;

    warlock.status.impActive = true;

    warlock.timers.impRounds = 10;

    warlock.health.tempHp = 10;
}

void updateImp(
    Character& warlock
)
{
    if(!warlock.status.impActive)
        return;

    if(warlock.health.tempHp <= 0)
    {
        removeImp(warlock);
        return;
    }

    warlock.timers.impRounds--;

    if(
        warlock.timers.impRounds <= 0
    )
    {
        removeImp(warlock);
    }
}

void removeImp(
    Character& warlock
)
{
    warlock.status.impActive = false;

    warlock.timers.impRounds = 0;
}

bool isImpActive(
    const Character& warlock
)
{
    return
        warlock.status.impActive;
}

/////////////////////////////////////////////////////
// Magical Cunning
/////////////////////////////////////////////////////

bool canUseMagicalCunning(
    const Character& warlock
)
{
    if(!warlock.health.alive)
        return false;

    const SpecialAction* magicalCunning =
        findSpecial(
            warlock,
            SpecialType::MagicalCunning
        );

    if(
        magicalCunning == nullptr ||
        magicalCunning->currentUses <= 0
    )
    {
        return false;
    }

    return
        warlock.spellSlots.current <
        warlock.spellSlots.maximum;
}

void useMagicalCunning(
    Character& warlock
)
{
    if(
        !canUseMagicalCunning(
            warlock
        )
    )
    {
        return;
    }

    SpecialAction* magicalCunning =
        findSpecial(
            warlock,
            SpecialType::MagicalCunning
        );

    if(magicalCunning == nullptr)
        return;

    magicalCunning->currentUses--;

    warlock.spellSlots.current[1]++;

    if(
        warlock.spellSlots.current >
        warlock.spellSlots.maximum
    )
    {
        warlock.spellSlots.current =
            warlock.spellSlots.maximum;
    }
}

/////////////////////////////////////////////////////
// Hex
/////////////////////////////////////////////////////

bool canCastHex(
    const Character& warlock
)
{
    if(!warlock.health.alive)
        return false;

    if(warlock.status.hexActive)
        return false;

    if(warlock.status.concentrating)
        return false;

    return
        hasSpellSlot(
            warlock,
            SpellLevel::Level1
        );
}

void castHex(
    Character& warlock,
    Character&
)
{
    const MagicalAction* spell =
        findSpell(
            warlock,
            "Hex"
        );

    if(
        spell == nullptr ||
        !castSpell(
            warlock,
            *spell
        )
    )
    {
        return;
    }

    warlock.status.hexActive = true;

    warlock.status.concentrating = true;

    warlock.timers.hexRounds = 10;
}

void updateHex(
    Character& warlock
)
{
    if(!warlock.status.hexActive)
        return;

    warlock.timers.hexRounds--;

    if(
        warlock.timers.hexRounds <= 0
    )
    {
        removeHex(
            warlock
        );
    }
}

void removeHex(
    Character& warlock
)
{
    warlock.status.hexActive = false;

    warlock.status.concentrating = false;

    warlock.timers.hexRounds = 0;
}

/////////////////////////////////////////////////////
// Eldritch Blast
/////////////////////////////////////////////////////

bool canCastEldritchBlast(
    const Character&
)
{
    return true;
}

void castEldritchBlast(
    Character& warlock,
    Character& target
)
{
    const MagicalAction* spell =
        findCantrip(
            warlock,
            "Eldritch Blast"
        );

    if(spell == nullptr)
        return;

    int attackRoll =
        rollDice(1,20) +
        getSpellAttackBonus(warlock);

    attackRoll =
        modifySpellAttackRoll(
            warlock,
            target,
            attackRoll
        );

    if(attackRoll < target.ac)
        return;

    int damage =
        rollDice(1,10);

    if(isImpActive(warlock))
    {
        damage +=
            rollDice(2,6);
    }

    if(warlock.status.hexActive)
    {
        damage +=
            rollDice(1,6);
    }

    damage =
        modifySpellDamage(
            warlock,
            target,
            damage
        );

    dealDamage(
        warlock,
        target,
        damage,
        DamageType::Force
    );
}

/////////////////////////////////////////////////////
// Witch Bolt
/////////////////////////////////////////////////////

bool canCastWitchBolt(
    const Character& warlock
)
{
    return
        hasSpellSlot(
            warlock,
            SpellLevel::Level1
        );
}

void castWitchBolt(
    Character& warlock,
    Character& target
)
{
    const MagicalAction* spell =
        findSpell(
            warlock,
            "Witch Bolt"
        );

    if(
        spell == nullptr ||
        !castSpell(
            warlock,
            *spell
        )
    )
    {
        return;
    }

    int attackRoll =
        rollDice(1,20) +
        getSpellAttackBonus(warlock);

    attackRoll =
        modifySpellAttackRoll(
            warlock,
            target,
            attackRoll
        );

    if(attackRoll < target.ac)
        return;

    int damage =
        rollDice(2,12);

    if(isImpActive(warlock))
    {
        damage +=
            rollDice(2,6);
    }

    if(warlock.status.hexActive)
    {
        damage +=
            rollDice(1,6);
    }

    damage =
        modifySpellDamage(
            warlock,
            target,
            damage
        );

    dealDamage(
        warlock,
        target,
        damage,
        DamageType::Lightning
    );
}