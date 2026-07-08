#include "cleric_specials.h"

#include "../../combat_actions.h"
#include "../../combat_utils.h"
#include "../../combat/combat_statistics.h"
#include "../../dice.h"

#include "../saving_throw.h"
#include "../spell_utils.h"

/////////////////////////////////////////////////////
// Shield
/////////////////////////////////////////////////////

void equipShield(
    Character& cleric
)
{
    if(cleric.status.shieldEquipped)
        return;

    cleric.status.shieldEquipped = true;

    cleric.ac += 2;

    cleric.physical.damageDiceSides =
        cleric.physical.oneHandedDiceSides;
}

void unequipShield(
    Character& cleric
)
{
    if(!cleric.status.shieldEquipped)
        return;

    cleric.status.shieldEquipped = false;

    cleric.ac -= 2;

    cleric.physical.damageDiceSides =
        cleric.physical.twoHandedDiceSides;
}

bool isUsingShield(
    const Character& cleric
)
{
    return cleric.status.shieldEquipped;
}

/////////////////////////////////////////////////////
// Guiding Bolt
/////////////////////////////////////////////////////

bool canCastGuidingBolt(
    const Character& cleric
)
{
    if(cleric.status.shieldEquipped)
        return false;

    return hasSpellSlot(
        cleric,
        SpellLevel::Level1
    );
}

void castGuidingBolt(
    Character& cleric,
    Character& target
)
{
    const MagicalAction* spell =
        findSpell(
            cleric,
            "Guiding Bolt"
        );

    if(
        spell == nullptr ||
        !castSpell(cleric,*spell)
    )
    {
        return;
    }

    int attackRoll =
        rollDice(1,20) +
        getSpellAttackBonus(cleric);

    if(attackRoll >= target.ac)
    {
        int damage =
            rollDice(4,6);

        dealDamage(
            cleric,
            target,
            damage,
            DamageType::Radiant
        );

        if(target.health.alive)
        {
            applyGuidingBoltAdvantage(
                target
            );
        }
    }
}

void applyGuidingBoltAdvantage(
    Character& target
)
{
    target.status.guidingBoltAdvantage =
        true;
}

void clearGuidingBoltAdvantage(
    Character& target
)
{
    target.status.guidingBoltAdvantage =
        false;
}

/////////////////////////////////////////////////////
// Toll the Dead
/////////////////////////////////////////////////////

bool canCastTollTheDead(
    const Character& cleric
)
{
    return
        !cleric.status.shieldEquipped;
}

void castTollTheDead(
    Character& cleric,
    Character& target
)
{
    int diceSides =
        target.health.hp <
        target.health.maxHp
        ? 12
        : 8;

    bool saved =
        performSavingThrow(
            cleric,
            target,
            SaveType::Wisdom
        );

    if(saved)
        return;

    int damage =
        rollDice(1,diceSides);

    dealDamage(
        cleric,
        target,
        damage,
        DamageType::Necrotic
    );
}

/////////////////////////////////////////////////////
// Cure Wounds
/////////////////////////////////////////////////////

bool canCastCureWounds(
    const Character& cleric
)
{
    if(cleric.status.shieldEquipped)
        return false;

    return hasSpellSlot(
        cleric,
        SpellLevel::Level1
    );
}

void castCureWounds(
    Character& cleric
)
{
    const MagicalAction* spell =
        findSpell(
            cleric,
            "Cure Wounds"
        );

    if(
        spell == nullptr ||
        !castSpell(cleric,*spell)
    )
    {
        return;
    }

    int healing =
        rollDice(2,8)
        +
        cleric.abilities.wis;

    healCharacter(
        cleric,
        healing
    );
}

/////////////////////////////////////////////////////
// Shield of Faith
/////////////////////////////////////////////////////

bool canCastShieldOfFaith(
    const Character& cleric
)
{
    if(cleric.status.shieldEquipped)
        return false;

    if(cleric.status.concentrating)
        return false;

    return hasSpellSlot(
        cleric,
        SpellLevel::Level1
    );
}

void castShieldOfFaith(
    Character& cleric
)
{
    const MagicalAction* spell =
        findSpell(
            cleric,
            "Shield of Faith"
        );

    if(
        spell == nullptr ||
        !castSpell(cleric,*spell)
    )
    {
        return;
    }

    cleric.status.concentrating = true;

    cleric.status.shieldOfFaith = true;

    cleric.bonusAc += 2;

    cleric.timers.shieldOfFaithRounds = 10;
}

void updateShieldOfFaith(
    Character& cleric
)
{
    if(!cleric.status.shieldOfFaith)
        return;

    cleric.timers.shieldOfFaithRounds--;

    if(
        cleric.timers.shieldOfFaithRounds <= 0
    )
    {
        removeShieldOfFaith(
            cleric
        );
    }
}

void removeShieldOfFaith(
    Character& cleric
)
{
    cleric.status.shieldOfFaith = false;

    cleric.status.concentrating = false;

    cleric.bonusAc -= 2;

    cleric.timers.shieldOfFaithRounds = 0;
}

/////////////////////////////////////////////////////
// Channel Divinity
/////////////////////////////////////////////////////

bool canUseChannelDivinity(
    const Character& cleric
)
{
    const SpecialAction* channel =
        findSpecial(
            cleric,
            SpecialType::ChannelDivinity
        );

    return
        channel &&
        channel->currentUses > 0;
}

void useChannelDivinityHeal(
    Character& cleric
)
{
    SpecialAction* channel =
        findSpecial(
            cleric,
            SpecialType::ChannelDivinity
        );

    if(channel == nullptr)
        return;

    channel->currentUses--;

    int healing =
        rollDice(1,8)
        +
        cleric.abilities.wis;

    healCharacter(
        cleric,
        healing
    );
}

void useChannelDivinityRadiance(
    Character& cleric,
    Character& target
)
{
    SpecialAction* channel =
        findSpecial(
            cleric,
            SpecialType::ChannelDivinity
        );

    if(channel == nullptr)
        return;

    if(channel->currentUses <= 0)
        return;

    channel->currentUses--;

    bool saved =
        performSavingThrow(
            cleric,
            target,
            SaveType::Constitution
        );

    if(saved)
        return;

    int damage =
        rollDice(1,8);

    dealDamage(
        cleric,
        target,
        damage,
        DamageType::Radiant
    );
}