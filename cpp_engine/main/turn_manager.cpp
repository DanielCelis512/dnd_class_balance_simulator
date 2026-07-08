#include "turn_manager.h"

#include "ai/barbarian_ai.h"
#include "ai/bard_ai.h"
#include "ai/cleric_ai.h"
#include "ai/druid_ai.h"

#include "ai/fighter_ai.h"
#include "ai/monk_ai.h"
#include "ai/paladin_ai.h"
#include "ai/ranger_ai.h"

#include "ai/rogue_ai.h"
#include "ai/sorcerer_ai.h"
#include "ai/warlock_ai.h"
#include "ai/wizard_ai.h"

void executeTurn(
    Character& attacker,
    Character& defender,
    CombatStatistics& attackerStats,
    CombatStatistics& defenderStats
)
{
    (void)attackerStats;
    (void)defenderStats;

    if(
        !attacker.health.alive ||
        !defender.health.alive
    )
    {
        return;
    }

    switch(attacker.identity.classType)
    {
        case ClassType::Barbarian:
            barbarianTurnAI(attacker, defender);
            break;

        case ClassType::Bard:
            bardTurnAI(attacker, defender);
            break;

        case ClassType::Cleric:
            clericTurnAI(attacker, defender);
            break;

        case ClassType::Druid:
            druidTurnAI(attacker, defender);
            break;

        case ClassType::Fighter:
            fighterTurnAI(attacker, defender);
            break;

        case ClassType::Monk:
            monkTurnAI(attacker, defender);
            break;

        case ClassType::Paladin:
            paladinTurnAI(attacker, defender);
            break;

        case ClassType::Ranger:
            rangerTurnAI(attacker, defender);
            break;

        case ClassType::Rogue:
            rogueTurnAI(attacker, defender);
            break;

        case ClassType::Sorcerer:
            sorcererTurnAI(attacker, defender);
            break;

        case ClassType::Warlock:
            warlockTurnAI(attacker, defender);
            break;

        case ClassType::Wizard:
            wizardTurnAI(attacker, defender);
            break;

        default:
            break;
    }
}

bool battleContinues(
    const Character& characterA,
    const Character& characterB
)
{
    return
        characterA.health.alive &&
        characterB.health.alive;
}