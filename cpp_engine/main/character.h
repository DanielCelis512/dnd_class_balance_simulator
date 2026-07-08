#ifndef CHARACTER_H
#define CHARACTER_H

#include <array>
#include <string>
#include <vector>

#include "combat_statistics.h"
#include "combat_rules.h"

//==================================================
// Character Classes
//==================================================

enum class ClassType
{
    Barbarian = 0,
    Bard,
    Cleric,
    Druid,
    Fighter,
    Monk,
    Paladin,
    Ranger,
    Rogue,
    Sorcerer,
    Warlock,
    Wizard,

    Count
};

//==================================================
// Combat Actions
//==================================================

enum class ActionType
{
    PhysicalAttack,

    MagicAttack,
    SavingThrowSpell,

    CantripAttack,
    SavingThrowCantrip,

    Heal,

    Special
};

//==================================================
// Divine Smite Source
//==================================================

enum class DivineSmiteSource
{
    None,
    Free,
    SpellSlot
};

//==================================================
// Saving Throw Results
//==================================================

enum class SaveResult
{
    CriticalFailure,
    Failure,
    Success,
    CriticalSuccess
};

//==================================================
// Saving Throw Types
//==================================================

enum class SaveType
{
    Strength,
    Dexterity,
    Constitution,
    Intelligence,
    Wisdom,
    Charisma,
    None
};

//==================================================
// Magic Resolution
//==================================================

enum class MagicType
{
    AttackRoll,
    SavingThrow,
    Automatic,
    Healing,
    Buff,
    Special
};

//==================================================
// Wild Shape Forms
//==================================================

enum class WildShapeForm
{
    None,

    Wolf,
    ConstrictorSnake
};

//==================================================
// Range
//==================================================

enum class RangeType
{
    Melee,
    Ranged
};

//==================================================
// Spell Slot Levels
//==================================================

enum class SpellLevel
{
    Cantrip = 0,

    Level1,
    Level2,
    Level3,
    Level4,
    Level5
};

//==================================================
// Special Abilities
//==================================================

enum class SpecialType
{
    None,

    Rage,
    RecklessAttack,

    BardicInspiration,
    CuttingWords,

    ChannelDivinity,

    WildShape,

    ActionSurge,
    SecondWind,

    Focus,

    DivineSmite,

    FavoredEnemy,

    SneakAttack,

    Metamagic,

    Imp,
    MagicalCunning,

    ArcaneRecovery
};

//==================================================
// Spells
//==================================================

enum class SpellEffectType
{
    None,

    GuidingBolt,

    HealingWord,

    CureWounds,

    DivineSmite,

    ShieldOfFaith,

    TollTheDead,

    Entangle,

    Shillelagh,

    Thunderwave,

    ViciousMockery,

    DissonantWhispers,

    TashasHideousLaughter,

    ChaosBolt,

    ChromaticOrb,

    FalseLife,

    FireBolt,

    SorcerousBurst,

    EldritchBlast,

    WitchBolt,

    MagicMissile
};

//==================================================
// Identity
//==================================================

struct Identity
{
    std::string name;

    ClassType classType =
        ClassType::Barbarian;

    int level = 2;
};

//==================================================
// AI
//==================================================

struct AIData
{
    ActionType preferredAction =
        ActionType::PhysicalAttack;

    ActionType currentAction =
        ActionType::PhysicalAttack;
};

//==================================================
// Ability Scores
//==================================================

struct AbilityScores
{
    int str = 0;
    int dex = 0;
    int con = 0;
    int intel = 0;
    int wis = 0;
    int cha = 0;
};

//==================================================
// Saving Throws
//==================================================

struct SavingThrows
{
    int str = 0;
    int dex = 0;
    int con = 0;
    int intel = 0;
    int wis = 0;
    int cha = 0;
};

//==================================================
// Initiative
//==================================================

struct Initiative
{
    int modifier = 0;

    int lastRoll = 0;

    int total = 0;
};

//==================================================
// Physical Action
//==================================================

struct PhysicalAction
{
    std::string name;

    int attackBonus = 0;

    int damageDiceNumber = 0;
    int damageDiceSides = 0;
    int damageModifier = 0;

    int extraDamageDiceNumber = 0;
    int extraDamageDiceSides = 0;
    int extraDamageModifier = 0;

    DamageType damageType =
        DamageType::Slashing;

    RangeType range =
        RangeType::Melee;

    bool usesAttackRoll = true;

    bool requiresSavingThrow = false;

    SaveType saveType =
        SaveType::None;

    int oneHandedDiceSides = 8;

    int twoHandedDiceSides = 10;

    bool versatile = false;

    bool finesse = false;
};

//==================================================
// Magical Action
//==================================================

struct MagicalAction
{
    std::string name;

    SpellLevel level =
        SpellLevel::Level1;

    MagicType magicType =
        MagicType::AttackRoll;

    SaveType saveType =
        SaveType::None;

    DamageType damageType =
        DamageType::Force;

    int spellDC = 0;

    int attackBonus = 0;

    int effectDiceNumber = 0;
    int effectDiceSides = 0;
    int effectModifier = 0;

    bool requiresConcentration = false;

    int concentrationRounds = 0;

    int incapacitatedRounds = 0;

    bool grantsAdvantage = false;

    bool grantsDisadvantage = false;

    enum class ActionType
    {
        Action,
        BonusAction,
        Reaction
    };
    
    ActionType actionType =
    ActionType::Action;

    SpellEffectType effect =
    SpellEffectType::None;

};

//==================================================
// Healing Action
//==================================================

struct HealingAction
{
    std::string name;

    SpellLevel level =
        SpellLevel::Level1;

    int healingDiceNumber = 0;
    int healingDiceSides = 0;
    int healingModifier = 0;
};

//==================================================
// Special Action
//==================================================

struct SpecialAction
{
    std::string name;

    SpecialType type =
        SpecialType::None;

    int currentUses = 0;

    int maxUses = 0;
};

//==================================================
// Spell Slots
//==================================================

struct SpellSlots
{
    std::array<int,5> current =
    {
        0,0,0,0,0
    };

    std::array<int,5> maximum =
    {
        0,0,0,0,0
    };
};

//==================================================
// Damage Profile
//==================================================

struct DamageProfile
{
    std::vector<DamageType> resistances;

    std::vector<DamageType> immunities;

    std::vector<DamageType> vulnerabilities;
};

//==================================================
// Status Effects
//==================================================

struct StatusEffects
{
    bool raging = false;

    bool reckless = false;

    bool recklessAttack = false;

    bool cuttingWordsActive = false;

    bool favoredEnemy = false;

    bool flurryReady = false;

    bool sneakAttackReady = false;

    bool cursed = false;

    bool actionSurgeActive = false;

    bool wildShapeActive = false;

    WildShapeForm wildShapeForm = WildShapeForm::None;

    bool empoweredSpell = false;

    bool shieldEquipped = false;

    bool concentrating = false;

    bool incapacitated = false;

    bool hasAdvantage = false;

    bool hasDisadvantage = false;

    bool strengthSaveAdvantage = false;

    bool dexteritySaveAdvantage = false;

    bool hasAttackAdvantage = false;

    bool grantsAdvantageToAttackers = false;

    bool grantsDisadvantageToAttackers = false;

    bool attackersHaveAdvantage = false;

    bool attackersHaveDisadvantage = false;

    bool divineSmiteReady = false;

    bool shieldOfFaith = false;

    bool layOnHandsUsed = false;

    bool bonusActionUsed = false;

    DivineSmiteSource divineSmiteSource = DivineSmiteSource::None;

    bool dodgeReady = false;

    bool aimReady = false;

    bool offHandAttackReady = false;

    bool martialArtsReady = false;

    bool patientDefense = false;

    bool huntersMark = false;

    bool zephyrStrikeReady = false;

    bool huntersPreyReady = false;

    bool guidingBoltAdvantage = false;

    bool shillelaghActive = false;

    bool grappled = false;

    bool restrained = false;

    bool prone = false;

    // Strength
    bool strengthSaveAdvantage = false;
    bool strengthSaveDisadvantage = false;

    // Dexterity
    bool dexteritySaveAdvantage = false;
    bool dexteritySaveDisadvantage = false;

    // Constitution
    bool constitutionSaveAdvantage = false;
    bool constitutionSaveDisadvantage = false;

    // Intelligence
    bool intelligenceSaveAdvantage = false;
    bool intelligenceSaveDisadvantage = false;

    // Wisdom
    bool wisdomSaveAdvantage = false;
    bool wisdomSaveDisadvantage = false;

    // Charisma
    bool charismaSaveAdvantage = false;
    bool charismaSaveDisadvantage = false;

    bool stunned = false;

    bool frightened = false;

    bool poisoned = false;

    bool blinded = false;

    bool deafened = false;

    bool hasAttackDisadvantage = false;

    bool speedReducedToZero = false;

    bool canTakeActions = false;

    bool canTakeBonusActions = false;

    bool canTakeReactions = false;

    bool bardicInspirationActive = false;

    bool bardicInspirationUsed = false;

    bool disadvantageNextAttack = false;

    bool bladeWard = false;

    bool hideousLaughter = false;

    bool viciousMockery = false;

    bool grantsAdvantageToAttack = false;

    bool grantsDisadvantageToAttack = false;

    bool shouldSpendCuttingWords = false;

    bool innateSorceryActive = false;

    bool impActive = false;

    bool hexActive = false;

    bool goodPortentAvailable = false;

    bool badPortentAvailable = false;
};

//==================================================
// Effect Timers
//==================================================

struct EffectTimers
{
    int rageRounds = 0;

    int recentCriticalHit = 0;

    int cuttingWordsRounds = 0;

    int favoredEnemyRounds = 0;

    int sneakAttackRounds = 0;

    int curseRounds = 0;

    int wildShapeRounds = 0;

    int empoweredSpellRounds = 0;

    int concentrationRounds = 0;

    int incapacitatedRounds = 0;

    int bonusAcRounds = 0;

    int shieldOfFaithRounds = 0;

    int huntersMarkRounds = 0;

    int shillelaghRounds = 0;

    int restrainedRounds = 0;

    int frightenedRounds = 0;

    int poisonedRounds = 0;

    int stunnedRounds = 0;

    int bardicInspirationRounds = 0;

    int bladeWardRounds = 0;

    int hideousLaughterRounds = 0;

    int viciousMockeryRounds = 0;  
    
    int innateSorceryRounds = 0;

    int impRounds = 0;

    int hexRounds = 0;
};

//==================================================
// Wild Shape Backup
//==================================================

struct WildShapeData
{
    WildShapeForm form =
        WildShapeForm::None;

    int originalAc = 0;

    PhysicalAction originalAttack;

    int originalAttackBonus = 0;

    int originalDamageDiceNumber = 0;

    int originalDamageDiceSides = 0;

    int originalDamageModifier = 0;

    bool originalHasAdvantage = false;
};

//--------------------------------------------------
// Vital Statistics
//--------------------------------------------------

struct VitalStatistics
{
    int hp = 0;

    int maxHp = 0;

    int tempHp = 0;

    bool alive = true;
};

//--------------------------------------------------
// Combat Modifiers
//--------------------------------------------------

struct CombatModifiers
{
    int bonusDamage = 0;

    int extraAttacks = 0;

    int criticalRange = 20;

    int criticalMultiplier = 2;

    int bonusAttackRoll = 0;

    int bonusAC = 0;

    bool hasAdvantage = false;

    bool hasDisadvantage = false;

    bool attackersHaveAdvantage = false;

    int temporaryHitPoints = 0;
};

//==================================================
// Character
//==================================================

struct Character
{
    //--------------------------------------------------
    // Identity
    //--------------------------------------------------

    Identity identity;

    //--------------------------------------------------
    // Artificial Intelligence
    //--------------------------------------------------

    AIData ai;

    //--------------------------------------------------
    // Core Attributes
    //--------------------------------------------------

    AbilityScores abilities;

    SavingThrows savingThrows;

    Initiative initiative;

    int proficiencyBonus = 2;

    int spellcastingModifier = 0;

    //--------------------------------------------------
    // Defense
    //--------------------------------------------------

    int ac = 10;

    int bonusAc = 0;

    int damageReduction = 0;

    bool usesShield = false;

    DamageProfile damageProfile;

    //--------------------------------------------------
    // Combat Actions
    //--------------------------------------------------

    PhysicalAction physical;

    std::vector<MagicalAction> spells;

    std::vector<MagicalAction> cantrips;

    std::vector<SpecialAction> specials;

    CombatModifiers combat;

    //--------------------------------------------------
    // Spellcasting
    //--------------------------------------------------

    SpellSlots spellSlots;

    bool isCaster = false;

    bool canHeal = false;

    bool canUseCantrips = false;

    //--------------------------------------------------
    // Status Effects
    //--------------------------------------------------

    StatusEffects status;

    EffectTimers timers;

    //--------------------------------------------------
    // Wild Shape
    //--------------------------------------------------

    WildShapeData wildShape;

    //--------------------------------------------------
    // Statistics
    //--------------------------------------------------

    CombatStatistics statistics;

    VitalStatistics health; 
};

#endif