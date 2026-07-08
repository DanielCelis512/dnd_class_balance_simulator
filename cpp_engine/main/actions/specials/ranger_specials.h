#ifndef RANGER_SPECIALS_H
#define RANGER_SPECIALS_H

#include "../../character.h"

//==================================================
// Favored Enemy
//==================================================

bool hasFavoredEnemyUses(
    const Character& ranger
);

bool spendFavoredEnemyUse(
    Character& ranger
);

//==================================================
// Hunter's Mark
//==================================================

bool canCastHuntersMark(
    const Character& ranger
);

void castHuntersMark(
    Character& ranger
);

void updateHuntersMark(
    Character& ranger
);

void removeHuntersMark(
    Character& ranger
);

bool hasHuntersMark(
    const Character& ranger
);

//==================================================
// Hunter's Prey
//==================================================

bool canPrepareHuntersPrey(
    const Character& ranger,
    const Character& target
);

void prepareHuntersPrey(
    Character& ranger
);

void consumeHuntersPrey(
    Character& ranger
);

void clearHuntersPrey(
    Character& ranger
);

bool hasHuntersPreyReady(
    const Character& ranger
);

//==================================================
// Zephyr Strike
//==================================================

bool canCastZephyrStrike(
    const Character& ranger
);

void castZephyrStrike(
    Character& ranger
);

void consumeZephyrStrike(
    Character& ranger
);

void clearZephyrStrike(
    Character& ranger
);

bool hasZephyrStrikeReady(
    const Character& ranger
);

//==================================================
// Cure Wounds
//==================================================

bool canCastCureWounds(
    const Character& ranger
);

void castCureWounds(
    Character& ranger
);

#endif