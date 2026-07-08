#include "class_factory_utils.h"

#include <algorithm>

//==================================================
// Character Initialization
//==================================================

void initializeIdentity(
    Character& character,
    const std::string& name,
    ClassType classType,
    int level)
{
    character.identity.name = name;
    character.identity.classType = classType;
    character.identity.level = level;
}

void initializeAbilities(
    Character& character,
    int str,
    int dex,
    int con,
    int intel,
    int wis,
    int cha)
{
    character.abilities.str = str;
    character.abilities.dex = dex;
    character.abilities.con = con;
    character.abilities.intel = intel;
    character.abilities.wis = wis;
    character.abilities.cha = cha;
}

void initializeSavingThrows(
    Character& character,
    int str,
    int dex,
    int con,
    int intel,
    int wis,
    int cha)
{
    character.savingThrows.str = str;
    character.savingThrows.dex = dex;
    character.savingThrows.con = con;
    character.savingThrows.intel = intel;
    character.savingThrows.wis = wis;
    character.savingThrows.cha = cha;
}

void initializeHealth(
    Character& character,
    int maxHp)
{
    character.health.maxHp = maxHp;
    character.health.hp = maxHp;
    character.health.tempHp = 0;
    character.health.alive = true;
}

void initializeArmorClass(
    Character& character,
    int armorClass)
{
    character.ac = armorClass;
    character.bonusAc = 0;
}

void initializeInitiative(
    Character& character)
{
    character.initiative.modifier =
        character.abilities.dex;

    character.initiative.lastRoll = 0;
    character.initiative.total = 0;
}

//==================================================
// Spellcasting
//==================================================

void initializeSpellcaster(
    Character& character,
    bool canHeal,
    bool canUseCantrips)
{
    character.isCaster = true;
    character.canHeal = canHeal;
    character.canUseCantrips = canUseCantrips;
}

void initializeSpellSlots(
    Character& character,
    int level1,
    int level2,
    int level3,
    int level4,
    int level5)
{
    character.spellSlots.current =
    {
        level1,
        level2,
        level3,
        level4,
        level5
    };

    character.spellSlots.maximum =
    {
        level1,
        level2,
        level3,
        level4,
        level5
    };
}

//==================================================
// Action Builders
//==================================================

PhysicalAction createPhysicalAction(
    const std::string& name,
    int attackBonus,
    int diceNumber,
    int diceSides,
    int modifier,
    DamageType damageType,
    RangeType range)
{
    PhysicalAction action;

    action.name = name;

    action.attackBonus = attackBonus;

    action.damageDiceNumber = diceNumber;
    action.damageDiceSides = diceSides;
    action.damageModifier = modifier;

    action.damageType = damageType;
    action.range = range;

    return action;
}

MagicalAction createSpell(
    const std::string& name,
    SpellLevel level,
    MagicType magicType,
    DamageType damageType,
    int attackBonus,
    int spellDC,
    int diceNumber,
    int diceSides,
    int modifier,
    SaveType saveType,
    bool concentration,
    int concentrationRounds,
    int incapacitatedRounds)
{
    MagicalAction spell;

    spell.name = name;

    spell.level = level;
    spell.magicType = magicType;
    spell.damageType = damageType;

    spell.attackBonus = attackBonus;
    spell.spellDC = spellDC;

    spell.damageDiceNumber = diceNumber;
    spell.damageDiceSides = diceSides;
    spell.damageModifier = modifier;

    spell.saveType = saveType;

    spell.requiresConcentration = concentration;
    spell.concentrationRounds = concentrationRounds;
    spell.incapacitatedRounds = incapacitatedRounds;

    return spell;
}

HealingAction createHealingSpell(
    const std::string& name,
    SpellLevel level,
    int diceNumber,
    int diceSides,
    int modifier)
{
    HealingAction heal;

    heal.name = name;
    heal.level = level;

    heal.healingDiceNumber = diceNumber;
    heal.healingDiceSides = diceSides;
    heal.healingModifier = modifier;

    return heal;
}

SpecialAction createSpecial(
    const std::string& name,
    SpecialType type,
    int uses)
{
    SpecialAction special;

    special.name = name;

    special.type = type;

    special.currentUses = uses;
    special.maxUses = uses;

    return special;
}

SpecialAction* getSpecial(
    Character& character,
    SpecialType type
)
{
    for(auto& special : character.specials)
    {
        if(special.type == type)
            return &special;
    }

    return nullptr;
}

//==================================================
// Character Loaders
//==================================================

void setPhysicalAttack(
    Character& character,
    const PhysicalAction& attack)
{
    character.physical = attack;
}

void addSpell(
    Character& character,
    const MagicalAction& spell)
{
    character.spells.push_back(spell);
}

void addCantrip(
    Character& character,
    const MagicalAction& cantrip)
{
    character.cantrips.push_back(cantrip);
}

void addHealingSpell(
    Character& character,
    const HealingAction& spell)
{
    character.healingSpells.push_back(spell);
}

void addSpecial(
    Character& character,
    const SpecialAction& special)
{
    character.specials.push_back(special);
}

//==================================================
// Damage Profile
//==================================================

void addResistance(
    Character& character,
    DamageType damageType)
{
    character.damageProfile.resistances.push_back(damageType);
}

void addImmunity(
    Character& character,
    DamageType damageType)
{
    character.damageProfile.immunities.push_back(damageType);
}

void addVulnerability(
    Character& character,
    DamageType damageType)
{
    character.damageProfile.vulnerabilities.push_back(damageType);
}

//==================================================
// Misc
//==================================================

void enableShield(
    Character& character)
{
    character.usesShield = true;
    character.status.shieldEquipped = true;
}

void initializeStatistics(
    Character& character)
{
    character.statistics = CharacterStatistics{};
}