#ifndef COMBAT_STATISTICS_H
#define COMBAT_STATISTICS_H

#include "../combat_rules.h"

//==================================================
// Combat Statistics
//==================================================

struct CombatStatistics
{
    //==================================================
    // Results
    //==================================================

    int victories = 0;
    int defeats = 0;

    int roundsSurvived = 0;

    //==================================================
    // Actions
    //==================================================

    int actionsTaken = 0;

    int successfulActions = 0;
    int failedActions = 0;

    //==================================================
    // Physical
    //==================================================

    int attacksMade = 0;
    int attacksHit = 0;
    int attacksMissed = 0;

    int criticalHits = 0;
    int criticalMisses = 0;

    int recentCriticalHits = 0;
    int criticalHitsTaken = 0;

    //==================================================
    // Damage
    //==================================================

    int totalDamageDealt = 0;
    int totalDamageTaken = 0;

    int highestHit = 0;

    //==================================================
    // Healing
    //==================================================

    int healsUsed = 0;

    int healingDone = 0;
    int healingReceived = 0;

    int totalHealingDone = 0;

    //==================================================
    // Magic
    //==================================================

    int spellsCast = 0;
    int cantripsCast = 0;

    int savingThrowSpellsCast = 0;
    int savingThrowCantripsCast = 0;

    //==================================================
    // Resources
    //==================================================

    int magicUsesSpent = 0;
    int healingUsesSpent = 0;
    int specialUsesSpent = 0;

    //==================================================
    // Specials
    //==================================================

    int specialsUsed = 0;

    //--------------------------------------------------
    // Barbarian
    //--------------------------------------------------

    int rageUses = 0;
    int recklessAttacks = 0;

    int rageRounds = 0;
    int recklessHits = 0;
    int recklessMisses = 0;

    //--------------------------------------------------
    // Bard
    //--------------------------------------------------

    int cuttingWordsUses = 0;

    //--------------------------------------------------
    // Cleric
    //--------------------------------------------------

    int channelDivinityUses = 0;

    //--------------------------------------------------
    // Druid
    //--------------------------------------------------

    int wildShapeUses = 0;

    //--------------------------------------------------
    // Fighter
    //--------------------------------------------------

    int secondWindUses = 0;
    int actionSurges = 0;

    int actionSurgeExtraTurns = 0;
    int secondWindHealing = 0;

    //--------------------------------------------------
    // Monk
    //--------------------------------------------------

    int flurryOfBlows = 0;

    //--------------------------------------------------
    // Paladin
    //--------------------------------------------------

    int divineSmites = 0;
    int divineSmiteDamage = 0;

    //--------------------------------------------------
    // Ranger
    //--------------------------------------------------

    int favoredEnemyUses = 0;

    //--------------------------------------------------
    // Rogue
    //--------------------------------------------------

    int sneakAttacks = 0;
    int sneakAttackDamage = 0;

    //--------------------------------------------------
    // Sorcerer
    //--------------------------------------------------

    int empoweredSpells = 0;

    //--------------------------------------------------
    // Warlock
    //--------------------------------------------------

    int hexUses = 0;
    int eldritchBlasts = 0;

    //--------------------------------------------------
    // Wizard
    //--------------------------------------------------

    int arcaneRecoveryUses = 0;

    //==================================================
    // Derived
    //==================================================

    int concentrationBreaks = 0;

    double accuracy = 0.0;
};

//==================================================
// Generic Registration
//==================================================

void registerTurn(
    CombatStatistics&
);

void registerAttack(
    CombatStatistics&,
    bool hit,
    bool criticalHit,
    bool criticalMiss
);

void registerDamage(
    CombatStatistics& attacker,
    CombatStatistics& defender,
    int damage,
    DamageType damageType
);

void registerHealing(
    CombatStatistics& healer,
    CombatStatistics& target,
    int healing
);

void registerSpellCast(
    CombatStatistics&
);

void registerCantripCast(
    CombatStatistics&
);

void registerSavingThrowSpell(
    CombatStatistics&
);

void registerSavingThrowCantrip(
    CombatStatistics&
);

void registerSpecialUse(
    CombatStatistics&
);

void registerMagicResource(
    CombatStatistics&
);

void registerHealingResource(
    CombatStatistics&
);

void registerSpecialResource(
    CombatStatistics&
);

void registerFailedAction(
    CombatStatistics&
);

void registerVictory(
    CombatStatistics& winner,
    CombatStatistics& loser
);

//==================================================
// Barbarian
//==================================================

void registerRageUse(
    CombatStatistics&
);

void registerRageRound(
    CombatStatistics&
);

void registerRecklessAttack(
    CombatStatistics&
);

//==================================================
// Bard
//==================================================

void registerCuttingWords(
    CombatStatistics&
);

//==================================================
// Cleric
//==================================================

void registerChannelDivinity(
    CombatStatistics&
);

//==================================================
// Druid
//==================================================

void registerWildShape(
    CombatStatistics&
);

//==================================================
// Fighter
//==================================================

void registerSecondWind(
    CombatStatistics&
);

void registerActionSurge(
    CombatStatistics&
);

//==================================================
// Monk
//==================================================

void registerFlurryOfBlows(
    CombatStatistics&
);

void registerMartialArts(
    CombatStatistics&
);

void registerPatientDefense(
    CombatStatistics&
);

void registerUncannyMetabolism(
    CombatStatistics&
);

//==================================================
// Paladin
//==================================================

void registerDivineSmite(
    CombatStatistics&
);

//==================================================
// Ranger
//==================================================

void registerFavoredEnemy(
    CombatStatistics&
);

void registerHuntersMark(
    CombatStatistics&
);

void registerHuntersPrey(
    CombatStatistics&
);

void registerZephyrStrike(
    CombatStatistics&
);

//==================================================
// Rogue
//==================================================

void registerSneakAttack(
    CombatStatistics&
);

//==================================================
// Sorcerer
//==================================================

void registerEmpoweredSpell(
    CombatStatistics&
);

//==================================================
// Warlock
//==================================================

void registerHex(
    CombatStatistics&
);

void registerEldritchBlast(
    CombatStatistics&
);

//==================================================
// Wizard
//==================================================

void registerArcaneRecovery(
    CombatStatistics&
);

//==================================================
// Final Statistics
//==================================================

void calculateFinalStatistics(
    CombatStatistics&
);

void accumulateStatistics(
    CombatStatistics& total,
    const CombatStatistics& battle
);

#endif