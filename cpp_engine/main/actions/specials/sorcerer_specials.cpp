#include "sorcerer_specials.h"

#include "../combat/combat_modifiers.h"
#include "../../combat_actions.h"
#include "../../combat_utils.h"
#include "../../combat/combat_statistics.h"
#include "../../dice.h"

#include "../spell_utils.h"


namespace
{

int rollSpellAttack(
    Character& sorcerer
)
{
    int attackRoll;

    if(isInnateSorceryActive(sorcerer))
    {
        attackRoll =
            std::max(
                rollD20(),
                rollD20()
            );
    }
    else
    {
        attackRoll =
            rollD20();
    }

    attackRoll +=
        getSpellAttackBonus(
            sorcerer
        );

    return attackRoll;
}

}

/////////////////////////////////////////////////////
// Metamagic
/////////////////////////////////////////////////////

bool canUseMetamagic(
    const Character& sorcerer
)
{
    const SpecialAction* metamagic =
        findSpecial(
            sorcerer,
            SpecialType::Metamagic
        );

    if(metamagic == nullptr)
        return false;

    return
        metamagic->currentUses > 0;
}

bool canUseEmpoweredSpell(
    const Character& sorcerer
)
{
    return
        canUseMetamagic(
            sorcerer
        );
}

int applyEmpoweredSpell(
    Character& sorcerer,
    int damage,
    int diceNumber,
    int diceSides,
    bool criticalHit
)
{
    if(
        !canUseEmpoweredSpell(
            sorcerer
        )
    )
    {
        return damage;
    }

    SpecialAction* metamagic =
        findSpecial(
            sorcerer,
            SpecialType::Metamagic
        );

    if(metamagic == nullptr)
        return damage;

    metamagic->currentUses--;

    int extraDice =
        criticalHit ? 2 : 1;

    extraDice =
        std::min(
            extraDice,
            diceNumber
        );

    for(
        int i = 0;
        i < extraDice;
        ++i
    )
    {
        damage +=
            rollDice(
                1,
                diceSides
            );
    }

    return damage;
}

/////////////////////////////////////////////////////
// Innate Sorcery
/////////////////////////////////////////////////////

bool canUseInnateSorcery(
    const Character& sorcerer
)
{
    if(!sorcerer.health.alive)
        return false;

    if(sorcerer.status.innateSorceryActive)
        return false;

    const SpecialAction* metamagic =
        findSpecial(
            sorcerer,
            SpecialType::Metamagic
        );

    if(metamagic == nullptr)
        return false;

    return
        metamagic->currentUses > 0;
}

void activateInnateSorcery(
    Character& sorcerer
)
{
    if(
        !canUseInnateSorcery(
            sorcerer
        )
    )
    {
        return;
    }

    SpecialAction* metamagic =
        findSpecial(
            sorcerer,
            SpecialType::Metamagic
        );

    if(metamagic == nullptr)
        return;

    metamagic->currentUses--;

    sorcerer.status.innateSorceryActive =
        true;

    sorcerer.timers.innateSorceryRounds =
        10;
}

void deactivateInnateSorcery(
    Character& sorcerer
)
{
    sorcerer.status.innateSorceryActive =
        false;

    sorcerer.timers.innateSorceryRounds =
        0;
}

void updateInnateSorcery(
    Character& sorcerer
)
{
    if(
        !sorcerer.status.innateSorceryActive
    )
    {
        return;
    }

    if(
        sorcerer.status.incapacitated
    )
    {
        deactivateInnateSorcery(
            sorcerer
        );

        return;
    }

    sorcerer.timers.innateSorceryRounds--;

    if(
        sorcerer.timers.innateSorceryRounds <= 0
    )
    {
        deactivateInnateSorcery(
            sorcerer
        );
    }
}

bool isInnateSorceryActive(
    const Character& sorcerer
)
{
    return
        sorcerer.status.innateSorceryActive;
}

/////////////////////////////////////////////////////
// Sorcerous Burst
/////////////////////////////////////////////////////

bool canCastSorcerousBurst(
    const Character& sorcerer
)
{
    return true;
}

void castSorcerousBurst(
    Character& sorcerer,
    Character& target
)
{
    const MagicalAction* spell =
        findCantrip(
            sorcerer,
            "Sorcerous Burst"
        );

    if(spell == nullptr)
        return;

    int attackRoll =
        rollSpellAttack(
            sorcerer
        );

    attackRoll =
        modifySpellAttackRoll(
            sorcerer,
            target,
            attackRoll
        );

    if(attackRoll < target.ac)
        return;

    int damage = 0;

    int explosions = 0;

    int roll = rollDice(1,8);

    damage += roll;

    while(
        roll == 8 &&
        explosions <
        sorcerer.abilities.cha
    )
    {
        explosions++;

        roll = rollDice(1,8);

        damage += roll;
    }

    damage =
        modifySpellDamage(
            sorcerer,
            target,
            damage
        );
    
    damage =
        applyEmpoweredSpell(
            sorcerer,
            damage,
            1,
            8,
            false
        );

    dealDamage(
        sorcerer,
        target,
        damage,
        DamageType::Lightning
    );
}

/////////////////////////////////////////////////////
// Fire Bolt
/////////////////////////////////////////////////////

bool canCastFireBolt(
    const Character&
)
{
    return true;
}

void castFireBolt(
    Character& sorcerer,
    Character& target
)
{
    const MagicalAction* spell =
        findCantrip(
            sorcerer,
            "Fire Bolt"
        );

    if(spell == nullptr)
        return;

    int attackRoll =
        rollSpellAttack(
            sorcerer
        );

    attackRoll =
        modifySpellAttackRoll(
            sorcerer,
            target,
            attackRoll
        );

    if(attackRoll < target.ac)
        return;

    int damage =
        rollDice(1,10);

    damage =
        modifySpellDamage(
            sorcerer,
            target,
            damage
        );

    damage =
        applyEmpoweredSpell(
            sorcerer,
            damage,
            1,
            10,
            false
        );

    dealDamage(
        sorcerer,
        target,
        damage,
        DamageType::Fire
    );
}

/////////////////////////////////////////////////////
// Chaos Bolt
/////////////////////////////////////////////////////

bool canCastChaosBolt(
    const Character& sorcerer
)
{
    return
        hasSpellSlot(
            sorcerer,
            SpellLevel::Level1
        );
}

void castChaosBolt(
    Character& sorcerer,
    Character& target
)
{
    const MagicalAction* spell =
        findSpell(
            sorcerer,
            "Chaos Bolt"
        );

    if(
        spell == nullptr ||
        !castSpell(
            sorcerer,
            *spell
        )
    )
    {
        return;
    }

    int attackRoll =
        rollSpellAttack(
            sorcerer
        );

    attackRoll =
        modifySpellAttackRoll(
            sorcerer,
            target,
            attackRoll
        );

    if(attackRoll < target.ac)
        return;

    int damage =
        rollDice(2,8) +
        rollDice(1,6);

    damage =
        modifySpellDamage(
            sorcerer,
            target,
            damage
        );

    damage =
        applyEmpoweredSpell(
            sorcerer,
            damage,
            1,
            8,
            false
        );

    dealDamage(
        sorcerer,
        target,
        damage,
        DamageType::Psychic
    );
}

/////////////////////////////////////////////////////
// Chromatic Orb
/////////////////////////////////////////////////////

bool canCastChromaticOrb(
    const Character& sorcerer
)
{
    return
        hasSpellSlot(
            sorcerer,
            SpellLevel::Level1
        );
}

void castChromaticOrb(
    Character& sorcerer,
    Character& target
)
{
    const MagicalAction* spell =
        findSpell(
            sorcerer,
            "Chromatic Orb"
        );

    if(
        spell == nullptr ||
        !castSpell(
            sorcerer,
            *spell
        )
    )
    {
        return;
    }

    int attackRoll =
        rollSpellAttack(
            sorcerer
        );

    attackRoll =
        modifySpellAttackRoll(
            sorcerer,
            target,
            attackRoll
        );

    if(attackRoll < target.ac)
        return;

    int damage =
        rollDice(3,8);

    damage =
        modifySpellDamage(
            sorcerer,
            target,
            damage
        );

    damage =
        applyEmpoweredSpell(
            sorcerer,
            damage,
            1,
            8,
            false
        );

    dealDamage(
        sorcerer,
        target,
        damage,
        DamageType::Poison
    );
}

/////////////////////////////////////////////////////
// False Life
/////////////////////////////////////////////////////

bool canCastFalseLife(
    const Character& sorcerer
)
{
    return
        hasSpellSlot(
            sorcerer,
            SpellLevel::Level1
        );
}

void castFalseLife(
    Character& sorcerer
)
{
    const MagicalAction* spell =
        findSpell(
            sorcerer,
            "False Life"
        );

    if(
        spell == nullptr ||
        !castSpell(
            sorcerer,
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
        sorcerer.health.tempHp
    )
    {
        sorcerer.health.tempHp =
            tempHp;
    }
}