#ifndef BARD_SPECIALS_H
#define BARD_SPECIALS_H

#include "../../character.h"

/////////////////////////////////////////////////////
// Bardic Inspiration
/////////////////////////////////////////////////////

bool canUseBardicInspiration(
    const Character& bard
);

bool canUseCuttingWords(
    Character& bard,
    int attackTotal,
    const Character& attacker
);

void castBardicInspiration(
    Character& bard,
    Character& ally
);

void consumeBardicInspiration(
    Character& bard
);

int useCuttingWordsAttack(
    Character& bard
);

bool canReduceDamageWithCuttingWords(
    Character& bard
);

int useCuttingWordsDamage(
    Character& bard
);

/////////////////////////////////////////////////////
// Cutting Words
/////////////////////////////////////////////////////

int applyCuttingWordsToAttack(
    Character& bard,
    int attackTotal
);

int applyCuttingWordsToDamage(
    Character& bard,
    int damage
);

int applyCuttingWordsToSavingThrow(
    Character& bard,
    int saveTotal
);

/////////////////////////////////////////////////////
// Bardic Inspiration Bonus
/////////////////////////////////////////////////////

bool hasBardicInspiration(
    const Character& character
);

int consumeBardicInspirationBonus(
    Character& character
);

void updateBardicInspiration(
    Character& character
);

/////////////////////////////////////////////////////
// Healing Word
/////////////////////////////////////////////////////

bool canCastHealingWord(
    const Character& bard
);

void castHealingWord(
    Character& bard
);

/////////////////////////////////////////////////////
// Vicious Mockery
/////////////////////////////////////////////////////

bool canCastViciousMockery(
    const Character& bard
);

void castViciousMockery(
    Character& bard,
    Character& target
);

/////////////////////////////////////////////////////
// Blade Ward
/////////////////////////////////////////////////////

bool canCastBladeWard(
    const Character& bard
);

void castBladeWard(
    Character& bard
);

void updateBladeWard(
    Character& bard
);

void removeBladeWard(
    Character& bard
);

/////////////////////////////////////////////////////
// Dissonant Whispers
/////////////////////////////////////////////////////

bool canCastDissonantWhispers(
    const Character& bard
);

void castDissonantWhispers(
    Character& bard,
    Character& target
);

/////////////////////////////////////////////////////
// Tasha's Hideous Laughter
/////////////////////////////////////////////////////

bool canCastTashasHideousLaughter(
    const Character& bard
);

void castTashasHideousLaughter(
    Character& bard,
    Character& target
);

void updateTashasHideousLaughter(
    Character& target
);

#endif