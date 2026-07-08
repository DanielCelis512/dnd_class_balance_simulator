#ifndef COMBAT_RULES_H
#define COMBAT_RULES_H

//==================================================
// Damage Types
//==================================================

enum class DamageType
{
    None,
    Acid,
    Bludgeoning,
    Cold,
    Fire,
    Force,
    Lightning,
    Necrotic,
    Piercing,
    Poison,
    Psychic,
    Radiant,
    Slashing,
    Thunder
};

//==================================================
// Conditions
//==================================================

enum class ConditionType
{
    None,

    Advantage,
    Disadvantage,

    Incapacitated,

    Concentrating,

    Raging,
    Reckless,

    Hexed,

    FavoredEnemy,

    WildShape
};

//==================================================
// Roll State
//==================================================

enum class RollState
{
    Normal,
    Advantage,
    Disadvantage
};

//==================================================
// Attack Result
//==================================================

enum class AttackResult
{
    Miss,
    Hit,
    CriticalHit,
    CriticalMiss
};

//==================================================
// Damage Resolution
//==================================================

enum class DamageResult
{
    Normal,
    Resistant,
    Vulnerable,
    Immune
};

//==================================================
// Attack Resolution
//==================================================

struct AttackResolution
{
    AttackResult attackResult =
        AttackResult::Miss;

    DamageResult damageResult =
        DamageResult::Normal;

    int damage = 0;

    bool concentrationBroken = false;
};

//==================================================
// Roll Rules
//==================================================

RollState resolveRollState(
    bool advantage,
    bool disadvantage
);

bool hasAttackAdvantage(
    bool advantage,
    bool disadvantage
);

bool hasSavingThrowAdvantage(
    bool advantage,
    bool disadvantage
);

//==================================================
// Damage Rules
//==================================================

int applyResistance(
    int damage
);

int applyVulnerability(
    int damage
);

int applyImmunity();

int resolveDamage(
    int damage,
    DamageResult result
);

//==================================================
// Critical Rules
//==================================================

int applyCriticalDamage(
    int diceDamage,
    int modifier,
    int multiplier = 2
);

//==================================================
// Concentration Rules
//==================================================

bool requiresConcentrationCheck(
    int damageTaken
);

int concentrationDC(
    int damageTaken
);

#endif