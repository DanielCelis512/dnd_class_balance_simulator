#include "ai_utils.h"

//==================================================
// Resources
//==================================================

bool hasMagic(const Character& character)
{
    return character.magicUses > 0;
}

bool hasHealing(const Character& character)
{
    return character.healingUses > 0;
}

bool hasSpecial(const Character& character)
{
    return character.specialUses > 0;
}

//==================================================
// Health
//==================================================

double healthPercentage(
    const Character& character
)
{
    if(character.maxHp == 0)
    {
        return 0.0;
    }

    return static_cast<double>(character.hp)
           / character.maxHp;
}

bool isHealthy(
    const Character& character
)
{
    return healthPercentage(character) >= 0.75;
}

bool isInjured(
    const Character& character
)
{
    return healthPercentage(character) <= 0.50;
}

bool isCritical(
    const Character& character
)
{
    return healthPercentage(character) <= 0.25;
}

//==================================================
// Action availability
//==================================================

bool canUseMagic(
    const Character& character
)
{
    return character.isCaster &&
           hasMagic(character);
}

bool canUseCantrip(
    const Character& character
)
{
    return character.canUseCantrips;
}

bool canHealSelf(
    const Character& character
)
{
    return character.canHeal &&
           hasHealing(character);
}

bool canUseSpecial(
    const Character& character
)
{
    return hasSpecial(character);
}

//==================================================
// Damage estimation
//==================================================

int estimatePhysicalDamage(
    const Character& character
)
{
    return character.damageDiceNumber *
           ((character.damageDiceSides + 1) / 2)
           + character.damageModifier;
}

int estimateMagicDamage(
    const Character& character
)
{
    return character.magicDiceNumber *
           ((character.magicDiceSides + 1) / 2)
           + character.magicModifier;
}

int estimateCantripDamage(
    const Character& character
)
{
    return character.cantripDiceNumber *
           ((character.cantripDiceSides + 1) / 2)
           + character.cantripModifier;
}

int estimateHealing(
    const Character& character
)
{
    return character.healingDiceNumber *
           ((character.healingDiceSides + 1) / 2)
           + character.healingModifier;
}

//==================================================
// Enemy
//==================================================

bool enemyIsWeak(
    const Character& enemy
)
{
    return healthPercentage(enemy) <= 0.50;
}

bool enemyIsNearDeath(
    const Character& enemy
)
{
    return healthPercentage(enemy) <= 0.20;
}

//==================================================
// Spell type
//==================================================

bool spellUsesAttackRoll(
    const Character& character
)
{
    return character.magicType ==
           MagicType::AttackRoll;
}

bool spellUsesSavingThrow(
    const Character& character
)
{
    return character.magicType ==
           MagicType::SavingThrow;
}

bool cantripUsesAttackRoll(
    const Character& character
)
{
    return character.cantripType ==
           MagicType::AttackRoll;
}

bool cantripUsesSavingThrow(
    const Character& character
)
{
    return character.cantripType ==
           MagicType::SavingThrow;
}