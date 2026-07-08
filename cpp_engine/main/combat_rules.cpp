#include "combat_rules.h"

#include <algorithm>

//==================================================
// Roll Rules
//==================================================

RollState resolveRollState(
    bool advantage,
    bool disadvantage
)
{
    if (advantage && disadvantage)
    {
        return RollState::Normal;
    }

    if (advantage)
    {
        return RollState::Advantage;
    }

    if (disadvantage)
    {
        return RollState::Disadvantage;
    }

    return RollState::Normal;
}

bool hasAttackAdvantage(
    bool advantage,
    bool disadvantage
)
{
    return resolveRollState(
        advantage,
        disadvantage
    ) == RollState::Advantage;
}

bool hasSavingThrowAdvantage(
    bool advantage,
    bool disadvantage
)
{
    return resolveRollState(
        advantage,
        disadvantage
    ) == RollState::Advantage;
}

//==================================================
// Damage Rules
//==================================================

int applyResistance(
    int damage
)
{
    return damage / 2;
}

int applyVulnerability(
    int damage
)
{
    return damage * 2;
}

int applyImmunity()
{
    return 0;
}

int resolveDamage(
    int damage,
    DamageResult result
)
{
    switch(result)
    {
        case DamageResult::Normal:
            return damage;

        case DamageResult::Resistant:
            return applyResistance(damage);

        case DamageResult::Vulnerable:
            return applyVulnerability(damage);

        case DamageResult::Immune:
            return applyImmunity();
    }

    return damage;
}

//==================================================
// Critical Rules
//==================================================

int applyCriticalDamage(
    int diceDamage,
    int modifier,
    int multiplier
)
{
    return (diceDamage * multiplier)
        + modifier;
}

//==================================================
// Concentration Rules
//==================================================

bool requiresConcentrationCheck(
    int damageTaken
)
{
    return damageTaken > 0;
}

int concentrationDC(
    int damageTaken
)
{
    return std::max(
        10,
        damageTaken / 2
    );
}