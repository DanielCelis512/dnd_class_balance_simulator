#include "combat_utils.h"

#include "class_factory_utils.h"

#include <algorithm>

//==================================================
// Damage Profile
//==================================================

bool hasResistance(
    const Character& character,
    DamageType type
)
{
    return std::find(
        character.damageProfile.resistances.begin(),
        character.damageProfile.resistances.end(),
        type
    ) != character.damageProfile.resistances.end();
}

bool hasImmunity(
    const Character& character,
    DamageType type
)
{
    return std::find(
        character.damageProfile.immunities.begin(),
        character.damageProfile.immunities.end(),
        type
    ) != character.damageProfile.immunities.end();
}

bool hasVulnerability(
    const Character& character,
    DamageType type
)
{
    return std::find(
        character.damageProfile.vulnerabilities.begin(),
        character.damageProfile.vulnerabilities.end(),
        type
    ) != character.damageProfile.vulnerabilities.end();
}

void applyDamage(
    Character& character,
    int damage
)
{
    character.health.hp -= damage;

    if(character.health.hp < 0)
        character.health.hp = 0;

    if(character.health.hp == 0)
        character.health.alive = false;
}

void healCharacter(
    Character& character,
    int healing
)
{
    character.health.hp += healing;

    if(character.health.hp >
        character.health.maxHp)
    {
        character.health.hp =
            character.health.maxHp;
    }
}

void consumeSpellSlot(
    Character& character,
    SpellLevel level
)
{
    if(level == SpellLevel::Cantrip)
        return;

    int index =
        static_cast<int>(level) - 1;

    if(index >= 0 &&
       index < 5 &&
       character.spellSlots.current[index] > 0)
    {
        character.spellSlots.current[index]--;
    }
}

bool useSpecial(
    Character& character,
    SpecialType type
)
{
    SpecialAction* special =
        getSpecial(character, type);

    if(special == nullptr)
        return false;

    if(special->currentUses <= 0)
        return false;

    special->currentUses--;

    character.statistics.specialUsesSpent++;

    return true;
}

//==================================================
// Equipment
//==================================================

void equipShield(
    Character& character
)
{
    if(character.physical.versatile)
    {
        character.physical.damageDiceSides =
            character.physical.oneHandedDiceSides;
    }
}

void unequipShield(
    Character& character
)
{
    if(character.physical.versatile)
    {
        character.physical.damageDiceSides =
            character.physical.twoHandedDiceSides;
    }
}

bool isShieldEquipped(
    const Character& character
)
{
    return character.status.shieldEquipped;
}

void dealDamage(
    Character& attacker,
    Character& target,
    int damage,
    DamageType damageType
)
{
    //------------------------------------------
    // Already dead
    //------------------------------------------

    if(!target.health.alive)
        return;

    //------------------------------------------
    // Apply damage
    //------------------------------------------

    applyDamage(
        target,
        damage
    );

    //------------------------------------------
    // Statistics
    //------------------------------------------

    registerDamage(
        attacker.statistics,
        target.statistics,
        damage,
        damageType
    );
}

void dealHealing(
    Character& healer,
    Character& target,
    int healing
)
{
    healCharacter(
        target,
        healing
    );

    registerHealing(
        healer.statistics,
        target.statistics,
        healing
    );
}

void giveTemporaryHP(
    Character& target,
    int amount
)
{
    if(amount > target.health.tempHp)
    {
        target.health.tempHp = amount;
    }
}

