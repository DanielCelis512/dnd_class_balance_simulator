#include "class_factory.h"

#include "class_factory_utils.h"

//==================================================
// Barbarian
//==================================================

Character createBarbarian(const std::string& name)
{
    Character character;

    //--------------------------------------------------
    // Identity
    //--------------------------------------------------

    initializeIdentity(
        character,
        name,
        ClassType::Barbarian
    );

    //--------------------------------------------------
    // Attributes
    //--------------------------------------------------

    initializeAbilities(
        character,
        4,  // STR
        2,  // DEX
        3,  // CON
        -1,  // INT
        1,  // WIS
        0   // CHA
    );

    initializeSavingThrows(
        character,
        6,
        2,
        5,
        -1,
        1,
        0
    );

    //--------------------------------------------------
    // Combat Stats
    //--------------------------------------------------

    initializeHealth(character, 45);

    initializeArmorClass(character, 15);

    initializeInitiative(character);

    //--------------------------------------------------
    // Physical Attack
    //--------------------------------------------------

    setPhysicalAttack(
        character,
        createPhysicalAction(
            "Greataxe",
            6,
            1,
            12,
            4,
            DamageType::Slashing
        )
    );

    //--------------------------------------------------
    // Specials
    //--------------------------------------------------

    addSpecial(
        character,
        createSpecial(
            "Rage",
            SpecialType::Rage,
            2
        )
    );

    addSpecial(
        character,
        createSpecial(
            "Reckless Attack",
            SpecialType::RecklessAttack,
            999
        )
    );

    //--------------------------------------------------
    // Resistances
    //--------------------------------------------------

    addResistance(character, DamageType::Slashing);
    addResistance(character, DamageType::Piercing);
    addResistance(character, DamageType::Bludgeoning);

    //--------------------------------------------------
    // Statistics
    //--------------------------------------------------

    initializeStatistics(character);

    return character;
}

//==================================================
// Bard
//==================================================

Character createBard(const std::string& name)
{
    Character character;

    initializeIdentity(character,name,ClassType::Bard);

    initializeAbilities(
        character,
        -1,
        3,
        2,
        0,
        1,
        4
    );

    initializeSavingThrows(
        character,
        -1,
        5,
        2,
        0,
        1,
        6
    );

    initializeHealth(character,30);

    initializeArmorClass(character,14);

    initializeInitiative(character);

    int spellcastingModifier = character.abilities.cha;
    character.spellcastingModifier = spellcastingModifier;

    initializeSpellcaster(
        character,
        false,
        true
    );

    initializeSpellSlots(
        character,
        3,
        0,
        0,
        0,
        0
    );

    setPhysicalAttack(
        character,
        createPhysicalAction(
            "Rapier",
            5,
            1,
            8,
            3,
            DamageType::Piercing
        )
    );

    addCantrip(
        character,
        createSpell(
            "Vicious Mockery",
            SpellLevel::Cantrip,
            MagicType::SavingThrow,
            DamageType::Psychic,
            1,
            6,
            0,
            SaveType::Wisdom,
            0,
            0
        )
    );

    addSpell(
        character,
        createSpell(
            "Dissonant Whispers",
            SpellLevel::Level1,
            MagicType::SavingThrow,
            DamageType::Psychic,
            3,
            6,
            0,
            SaveType::Wisdom,
            0,
            0
        )
    );

    addSpell(
        character,
        createSpell(
            "Tasha's Hideous Laughter",
            SpellLevel::Level1,
            MagicType::SavingThrow,
            DamageType::Psychic,
            0,
            0,
            0,
            SaveType::Wisdom,
            true,
            10,
            10
        )
    );

    addSpecial(
        character,
        createSpecial(
            "Bardic Inspiration",
            SpecialType::BardicInspiration,
            4
        )
    );

    initializeStatistics(character);

    return character;
}

//==================================================
// Cleric
//==================================================

Character createCleric(const std::string& name)
{
    Character character;

    //--------------------------------------------------
    // Identity
    //--------------------------------------------------

    initializeIdentity(
        character,
        name,
        ClassType::Cleric
    );

    //--------------------------------------------------
    // Ability Scores
    //--------------------------------------------------

    initializeAbilities(
        character,
        2,
        0,
        3,
        -1,
        4,
        1
    );

    initializeSavingThrows(
        character,
        2,
        0,
        3,
        -1,
        6,
        3
    );

    //--------------------------------------------------
    // Combat Stats
    //--------------------------------------------------

    initializeHealth(character, 33);

    initializeArmorClass(character, 16);

    initializeInitiative(character);

    enableShield(character);

    character.physical.oneHandedDiceSides = 8;
    character.physical.twoHandedDiceSides = 10;

    character.physical.versatile = true;

    int spellcastingModifier = character.abilities.wis;
    character.spellcastingModifier = spellcastingModifier;

    //--------------------------------------------------
    // Spellcasting
    //--------------------------------------------------

    initializeSpellcaster(
        character,
        true,
        false
    );

    initializeSpellSlots(
        character,
        3,
        0,
        0,
        0,
        0
    );

    //--------------------------------------------------
    // Physical Attack
    //--------------------------------------------------

    setPhysicalAttack(
        character,
        createPhysicalAction(
            "Warhammer",
            4,
            1,
            8,
            3,
            DamageType::Bludgeoning
        )
    );

    //--------------------------------------------------
    // Spells
    //--------------------------------------------------

    addSpell(
        character,
        createSpell(
            "Guiding Bolt",
            SpellLevel::Level1,
            MagicType::AttackRoll,
            DamageType::Radiant,
            4,
            6,
            0,
            SaveType::None,
            false,
            0,
            0,
            SpellEffectType::GuidingBolt
        )
    );

    //--------------------------------------------------
    // Specials
    //--------------------------------------------------

    addSpecial(
        character,
        createSpecial(
            "Channel Divinity",
            SpecialType::ChannelDivinity,
            2
        )
    );

    //--------------------------------------------------
    // Statistics
    //--------------------------------------------------

    initializeStatistics(character);

    return character;
}

//==================================================
// Druid
//==================================================

Character createDruid(const std::string& name)
{
    Character character;

    initializeIdentity(character,name,ClassType::Druid);

    initializeAbilities(
        character,
        1,
        2,
        3,
        -1,
        4,
        0
    );

    initializeSavingThrows(
        character,
        1,
        2,
        3,
        1,
        6,
        0
    );

    initializeHealth(character,33);

    initializeArmorClass(character,14);

    initializeInitiative(character);

    enableShield(character);

    character.physical.oneHandedDiceSides = 6;
    character.physical.twoHandedDiceSides = 8;

    character.physical.versatile = true;

    int spellcastingModifier = character.abilities.wis;
    character.spellcastingModifier = spellcastingModifier;

    initializeSpellcaster(
        character,
        false,
        false
    );

    initializeSpellSlots(
        character,
        3,
        0,
        0,
        0,
        0
    );

    setPhysicalAttack(
        character,
        createPhysicalAction(
            "Quarterstaff",
            4,
            1,
            6,
            1,
            DamageType::Bludgeoning
        )
    );

    addSpell(
        character,
        createSpell(
            "Entangle",
            SpellLevel::Level1,
            MagicType::SavingThrow,
            DamageType::None,
            0,
            0,
            0,
            SaveType::Strength,
            true,
            3
        )
    );

    addSpecial(
        character,
        createSpecial(
            "Wild Shape",
            SpecialType::WildShape,
            2
        )
    );

    initializeStatistics(character);

    return character;
}

//==================================================
// Fighter
//==================================================

Character createFighter(const std::string& name)
{
    Character character;

    //--------------------------------------------------
    // Identity
    //--------------------------------------------------

    initializeIdentity(
        character,
        name,
        ClassType::Fighter
    );

    //--------------------------------------------------
    // Ability Scores
    //--------------------------------------------------

    initializeAbilities(
        character,
        4,
        2,
        3,
        1,
        0,
        -1
    );

    initializeSavingThrows(
        character,
        6,
        2,
        5,
        1,
        0,
        -1
    );

    //--------------------------------------------------
    // Combat Stats
    //--------------------------------------------------

    initializeHealth(character, 39);

    initializeArmorClass(character, 17);

    initializeInitiative(character);

    enableShield(character);

    character.physical.oneHandedDiceSides = 8;
    character.physical.twoHandedDiceSides = 10;

    character.physical.versatile = true;

    //--------------------------------------------------
    // Physical Attack
    //--------------------------------------------------

    setPhysicalAttack(
        character,
        createPhysicalAction(
            "Longsword",
            6,
            1,
            8,
            4,
            DamageType::Slashing
        )
    );

    //--------------------------------------------------
    // Specials
    //--------------------------------------------------

    addSpecial(
        character,
        createSpecial(
            "Action Surge",
            SpecialType::ActionSurge,
            1
        )
    );

    addSpecial(
        character,
        createSpecial(
            "Second Wind",
            SpecialType::SecondWind,
            2
        )
    );

    //--------------------------------------------------
    // Statistics
    //--------------------------------------------------

    initializeStatistics(character);

    return character;
}

//==================================================
// Monk
//==================================================

Character createMonk(const std::string& name)
{
    Character character;

    initializeIdentity(
        character,
        name,
        ClassType::Monk
    );

    initializeAbilities(
        character,
        1,
        4,
        3,
        0,
        2,
        -1
    );

    initializeSavingThrows(
        character,
        3,
        6,
        3,
        0,
        2,
        -1
    );

    initializeHealth(character, 33);

    initializeArmorClass(character,16);

    initializeInitiative(character);

    setPhysicalAttack(
        character,
        createPhysicalAction(
            "Martial Arts",
            6,
            1,
            8,
            4,
            DamageType::Bludgeoning
        )
    );

    addSpecial(
        character,
        createSpecial(
            "Ki",
            SpecialType::Focus,
            2
        )
    );

    initializeStatistics(character);

    return character;
}

//==================================================
// Paladin
//==================================================

Character createPaladin(const std::string& name)
{
    Character character;

    initializeIdentity(
        character,
        name,
        ClassType::Paladin
    );

    initializeAbilities(
        character,
        4,
        -1,
        2,
        0,
        1,
        3
    );

    initializeSavingThrows(
        character,
        4,
        -1,
        2,
        0,
        3,
        5
    );

    initializeHealth(character,36);

    initializeArmorClass(character,16);

    initializeInitiative(character);

    enableShield(character);

    character.physical.oneHandedDiceSides = 8;
    character.physical.twoHandedDiceSides = 10;

    character.physical.versatile = true;

    initializeSpellcaster(
        character,
        true,
        false
    );

    initializeSpellSlots(
        character,
        2,
        0,
        0,
        0,
        0
    );

    setPhysicalAttack(
        character,
        createPhysicalAction(
            "Longsword",
            6,
            1,
            8,
            4,
            DamageType::Slashing
        )
    );

    addSpell(
        character,
        createSpell(
            "Shield of Faith",
            SpellLevel::Level1,
            MagicType::Buff,
            DamageType::None,
            0,
            0,
            0,
            SaveType::None,
            true,
            10,
            0,
            SpellEffectType::ShieldOfFaith
        )
    );

    addSpell(
        character,
        createSpell(
            "Divine Smite",
            SpellLevel::Level1,
            MagicType::Special,
            DamageType::None,
            2,
            8,
            0,
            SaveType::None,
            true,
            0,
            0,
            SpellEffectType::DivineSmite
        )
    );

    addSpecial(
        character,
        createSpecial(
            "Divine Smite",
            SpecialType::DivineSmite,
            1
        )
    );

    initializeStatistics(character);

    return character;
}

//==================================================
// Ranger
//==================================================

Character createRanger(const std::string& name)
{
    Character character;

    initializeIdentity(
        character,
        name,
        ClassType::Ranger
    );

    initializeAbilities(
        character,
        1,
        4,
        2,
        0,
        3,
        -1
    );

    initializeSavingThrows(
        character,
        3,
        6,
        2,
        0,
        3,
        -1
    );

    initializeSpellcaster(
        character,
        true,
        false
    );

    initializeSpellSlots(
        character,
        2,
        0,
        0,
        0,
        0
    );

    initializeHealth(character,36);

    initializeArmorClass(character,16);

    initializeInitiative(character);

    int spellcastingModifier = character.abilities.wis;
    character.spellcastingModifier = spellcastingModifier;

    setPhysicalAttack(
        character,
        createPhysicalAction(
            "Longbow",
            6,
            1,
            8,
            4,
            DamageType::Piercing,
            RangeType::Ranged
        )
    );

    addSpecial(
        character,
        createSpecial(
            "Favored Enemy",
            SpecialType::FavoredEnemy,
            4
        )
    );

    initializeStatistics(character);

    return character;
}

//==================================================
// Rogue
//==================================================

Character createRogue(const std::string& name)
{
    Character character;

    initializeIdentity(
        character,
        name,
        ClassType::Rogue
    );

    initializeAbilities(
        character,
        -1,
        4,
        3,
        2,
        0,
        1
    );

    initializeSavingThrows(
        character,
        -1,
        6,
        3,
        4,
        0,
        1
    );

    initializeHealth(character, 33);

    initializeArmorClass(character, 15);

    initializeInitiative(character);

    setPhysicalAttack(
        character,
        createPhysicalAction(
            "Rapier",
            8,
            1,
            8,
            4,
            DamageType::Piercing
        )
    );

    character.physical.finesse = true;

    addSpecial(
        character,
        createSpecial(
            "Sneak Attack",
            SpecialType::SneakAttack,
            999
        )
    );

    initializeStatistics(character);

    return character;
}

//==================================================
// Sorcerer
//==================================================

Character createSorcerer(const std::string& name)
{
    Character character;

    initializeIdentity(
        character,
        name,
        ClassType::Sorcerer
    );

    initializeAbilities(
        character,
        -1,
        2,
        3,
        1,
        0,
        4
    );

    initializeSavingThrows(
        character,
        -1,
        2,
        5,
        1,
        0,
        6
    );

    initializeHealth(character, 27);

    initializeArmorClass(character, 15);

    initializeInitiative(character);

    int spellcastingModifier = character.abilities.cha;
    character.spellcastingModifier = spellcastingModifier;

    initializeSpellcaster(
        character,
        false,
        false
    );

    initializeSpellSlots(
        character,
        3,
        0,
        0,
        0,
        0
    );

    addSpell(
        character,
        createSpell(
            "Chaos Bolt",
            SpellLevel::Level1,
            MagicType::AttackRoll,
            DamageType::Force,
            2,
            8,
            4,
            SaveType::None,
            false,
            0,
            0,
            SpellEffectType::ChaosBolt
        )
    );

    addSpecial(
        character,
        createSpecial(
            "Metamagic",
            SpecialType::Metamagic,
            3
        )
    );

    initializeStatistics(character);

    return character;
}

//==================================================
// Warlock
//==================================================

Character createWarlock(const std::string& name)
{
    Character character;

    initializeIdentity(
        character,
        name,
        ClassType::Warlock
    );

    initializeAbilities(
        character,
        0,
        2,
        3,
        1,
        -1,
        4
    );

    initializeSavingThrows(
        character,
        0,
        2,
        3,
        1,
        1,
        6
    );

    initializeHealth(character, 33);

    initializeArmorClass(character, 15);

    initializeInitiative(character);

    int spellcastingModifier = character.abilities.cha;
    character.spellcastingModifier = spellcastingModifier;

    initializeSpellcaster(
        character,
        false,
        true
    );

    initializeSpellSlots(
        character,
        2,
        0,
        0,
        0,
        0
    );

    addCantrip(
        character,
        createSpell(
            "Eldritch Blast",
            SpellLevel::Cantrip,
            MagicType::AttackRoll,
            DamageType::Force,
            1,
            10,
            4,
            SaveType::None,
            false,
            0,
            0,
            SpellEffectType::EldritchBlast
        )
    );

    addSpell(
        character,
        createSpell(
            "Witch Bolt",
            SpellLevel::Level1,
            MagicType::AttackRoll,
            DamageType::Lightning,
            2,
            12,
            4,
            SaveType::None,
            false,
            0,
            0,
            SpellEffectType::WitchBolt
        )
    );

    addSpecial(
        character,
        createSpecial(
            "Imp",
            SpecialType::Imp,
            2
        )
    );

    addSpecial(
        character,
        createSpecial(
            "Magical Cunning",
            SpecialType::MagicalCunning,
            1
        )
    );

    initializeStatistics(character);

    return character;
}

//==================================================
// Wizard
//==================================================

Character createWizard(const std::string& name)
{
    Character character;

    initializeIdentity(
        character,
        name,
        ClassType::Wizard
    );

    initializeAbilities(
        character,
        -1,
        2,
        3,
        4,
        2,
        0
    );

    initializeSavingThrows(
        character,
        -1,
        2,
        2,
        6,
        4,
        0
    );

    initializeHealth(character, 27);

    initializeArmorClass(character, 15);

    initializeInitiative(character);

    int spellcastingModifier = character.abilities.intel;
    character.spellcastingModifier = spellcastingModifier;

    initializeSpellcaster(
        character,
        false,
        false
    );

    initializeSpellSlots(
        character,
        3,
        0,
        0,
        0,
        0
    );

    addSpell(
        character,
        createSpell(
            "Chromatic Orb",
            SpellLevel::Level1,
            MagicType::AttackRoll,
            DamageType::Force,
            3,
            8,
            0,
            SaveType::None,
            false,
            0,
            0,
            SpellEffectType::ChromaticOrb
        )
    );

    addSpell(
        character,
        createSpell(
            "Magic Missile",
            SpellLevel::Level1,
            MagicType::Automatic,
            DamageType::Force,
            3,
            4,
            0,
            SaveType::None,
            false,
            0,
            0,
            SpellEffectType::MagicMissile
        )
    );

    addSpell(
        character,
        createSpell(
            "Tasha's Hideous Laughter",
            SpellLevel::Level1,
            MagicType::SavingThrow,
            DamageType::Psychic,
            0,
            0,
            0,
            SaveType::Wisdom,
            true,
            3,
            3,
            SpellEffectType::TashasHideousLaughter
        )
    );

    addSpecial(
        character,
        createSpecial(
            "Arcane Recovery",
            SpecialType::ArcaneRecovery,
            1
        )
    );

    initializeStatistics(character);

    return character;
} 

//==================================================
// Class Factory
//==================================================

Character createCharacter(
    ClassType classType,
    const std::string& name
)
{
    switch(classType)
    {
        case ClassType::Barbarian:
            return createBarbarian(name);

        case ClassType::Bard:
            return createBard(name);

        case ClassType::Cleric:
            return createCleric(name);

        case ClassType::Druid:
            return createDruid(name);

        case ClassType::Fighter:
            return createFighter(name);

        case ClassType::Monk:
            return createMonk(name);

        case ClassType::Paladin:
            return createPaladin(name);

        case ClassType::Ranger:
            return createRanger(name);

        case ClassType::Rogue:
            return createRogue(name);

        case ClassType::Sorcerer:
            return createSorcerer(name);

        case ClassType::Warlock:
            return createWarlock(name);

        case ClassType::Wizard:
            return createWizard(name);

        default:
            return createBarbarian(name);
    }
}