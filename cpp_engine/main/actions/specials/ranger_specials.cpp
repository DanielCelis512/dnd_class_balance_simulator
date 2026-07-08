#include "ranger_specials.h"

#include "../../combat_actions.h"
#include "../../combat_utils.h"
#include "../../combat/combat_statistics.h"

/////////////////////////////////////////////////////
// Favored Enemy
/////////////////////////////////////////////////////

bool hasFavoredEnemyUses(
    const Character& ranger
)
{
    const SpecialAction* favored =
        findSpecial(
            ranger,
            SpecialType::FavoredEnemy
        );

    return
        favored &&
        favored->currentUses > 0;
}

bool spendFavoredEnemyUse(
    Character& ranger
)
{
    SpecialAction* favored =
        findSpecial(
            ranger,
            SpecialType::FavoredEnemy
        );

    if(favored == nullptr)
        return false;

    if(favored->currentUses <= 0)
        return false;

    favored->currentUses--;

    return true;
}

/////////////////////////////////////////////////////
// Hunter's Mark
/////////////////////////////////////////////////////

bool canCastHuntersMark(
    const Character& ranger
)
{
    if(!ranger.health.alive)
        return false;

    if(ranger.status.concentrating)
        return false;

    if(!hasFavoredEnemyUses(ranger))
        return false;

    return true;
}

void castHuntersMark(
    Character& ranger
)
{
    if(!canCastHuntersMark(ranger))
        return;

    spendFavoredEnemyUse(
        ranger
    );

    ranger.status.huntersMark = true;

    ranger.status.concentrating = true;

    ranger.timers.huntersMarkRounds = 10;

    registerHuntersMark(
        ranger.statistics
    );
}

void updateHuntersMark(
    Character& ranger
)
{
    if(!ranger.status.huntersMark)
        return;

    ranger.timers.huntersMarkRounds--;

    if(
        ranger.timers.huntersMarkRounds <= 0
    )
    {
        removeHuntersMark(
            ranger
        );
    }
}

void removeHuntersMark(
    Character& ranger
)
{
    ranger.status.huntersMark = false;

    ranger.status.concentrating = false;

    ranger.timers.huntersMarkRounds = 0;
}

bool hasHuntersMark(
    const Character& ranger
)
{
    return ranger.status.huntersMark;
}

/////////////////////////////////////////////////////
// Hunter's Prey
/////////////////////////////////////////////////////

bool canPrepareHuntersPrey(
    const Character& ranger,
    const Character& target
)
{
    if(!hasFavoredEnemyUses(ranger))
        return false;

    return
        target.health.hp <
        target.health.maxHp;
}

void prepareHuntersPrey(
    Character& ranger
)
{
    ranger.status.huntersPreyReady = true;
}

void consumeHuntersPrey(
    Character& ranger
)
{
    if(!ranger.status.huntersPreyReady)
        return;

    spendFavoredEnemyUse(
        ranger
    );

    ranger.status.huntersPreyReady = false;

    registerHuntersPrey(
        ranger.statistics
    );
}

void clearHuntersPrey(
    Character& ranger
)
{
    ranger.status.huntersPreyReady = false;
}

bool hasHuntersPreyReady(
    const Character& ranger
)
{
    return ranger.status.huntersPreyReady;
}

/////////////////////////////////////////////////////
// Zephyr Strike
/////////////////////////////////////////////////////

bool canCastZephyrStrike(
    const Character& ranger
)
{
    return hasSpellSlot(
        ranger,
        SpellLevel::Level1
    );
}

void castZephyrStrike(
    Character& ranger
)
{
    if(!canCastZephyrStrike(ranger))
        return;

    consumeSpellSlot(
        ranger,
        SpellLevel::Level1
    );

    ranger.status.zephyrStrikeReady = true;

    ranger.status.hasAttackAdvantage = true;

    registerZephyrStrike(
        ranger.statistics
    );
}

void consumeZephyrStrike(
    Character& ranger
)
{
    if(!ranger.status.zephyrStrikeReady)
        return;

    ranger.status.zephyrStrikeReady = false;

    ranger.status.hasAttackAdvantage = false;
}

void clearZephyrStrike(
    Character& ranger
)
{
    ranger.status.zephyrStrikeReady = false;

    ranger.status.hasAttackAdvantage = false;
}

bool hasZephyrStrikeReady(
    const Character& ranger
)
{
    return ranger.status.zephyrStrikeReady;
}