#ifndef DRUID_SPECIALS_H
#define DRUID_SPECIALS_H

#include "../../character.h"

//==================================================
// Wild Shape
//==================================================

enum class WildShapeForm
{
    None,
    Wolf,
    ConstrictorSnake
};

bool canUseWildShape(
    const Character& druid
);

void activateWolfForm(
    Character& druid
);

void activateSnakeForm(
    Character& druid
);

void deactivateWildShape(
    Character& druid
);

void updateWildShape(
    Character& druid
);

bool isWildShaped(
    const Character& druid
);

WildShapeForm getCurrentWildShape(
    const Character& druid
);

bool canCastHealingWord(
    const Character& druid
);

void castHealingWord(
    Character& druid
);

bool canCastShillelagh(
    const Character& druid
);

void castShillelagh(
    Character& druid
);

void updateShillelagh(
    Character& druid
);

void removeShillelagh(
    Character& druid
);

bool hasShillelagh(
    const Character& druid
);

bool canCastCureWounds(
    const Character& druid
);

void castCureWounds(
    Character& druid
);

bool canCastThunderwave(
    const Character& druid
);

void castThunderwave(
    Character& druid,
    Character& target
);

bool canCastEntangle(
    const Character& druid
);

void castEntangle(
    Character& druid,
    Character& target
);

#endif