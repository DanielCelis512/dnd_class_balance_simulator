#ifndef MONK_SPECIALS_H
#define MONK_SPECIALS_H

#include "../../character.h"

//==================================================
// Focus
//==================================================

bool hasFocus(
    const Character& monk
);

int getFocus(
    const Character& monk
);

void restoreFocus(
    Character& monk
);

bool spendFocus(
    Character& monk,
    int amount
);

//==================================================
// Martial Arts
//==================================================

void prepareMartialArts(
    Character& monk
);

void clearMartialArts(
    Character& monk
);

bool hasMartialArtsReady(
    const Character& monk
);

//==================================================
// Flurry of Blows
//==================================================

bool canUseFlurryOfBlows(
    const Character& monk
);

void prepareFlurryOfBlows(
    Character& monk
);

void clearFlurryOfBlows(
    Character& monk
);

bool hasFlurryReady(
    const Character& monk
);

//==================================================
// Patient Defense
//==================================================

void activatePatientDefense(
    Character& monk
);

void clearPatientDefense(
    Character& monk
);

bool isUsingPatientDefense(
    const Character& monk
);

//==================================================
// Uncanny Metabolism
//==================================================

bool canUseUncannyMetabolism(
    const Character& monk
);

void useUncannyMetabolism(
    Character& monk
);

#endif