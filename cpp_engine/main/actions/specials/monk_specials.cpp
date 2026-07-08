#include "monk_specials.h"

#include "../../combat_actions.h"
#include "../../combat_utils.h"
#include "../../combat/combat_statistics.h"

#include "../../dice.h"

/////////////////////////////////////////////////////
// Focus
/////////////////////////////////////////////////////

bool hasFocus(
    const Character& monk
)
{
    const SpecialAction* focus =
        findSpecial(
            monk,
            SpecialType::Focus
        );

    return
        focus &&
        focus->currentUses > 0;
}

int getFocus(
    const Character& monk
)
{
    const SpecialAction* focus =
        findSpecial(
            monk,
            SpecialType::Focus
        );

    if(focus == nullptr)
        return 0;

    return focus->currentUses;
}

void restoreFocus(
    Character& monk
)
{
    SpecialAction* focus =
        findSpecial(
            monk,
            SpecialType::Focus
        );

    if(focus == nullptr)
        return;

    focus->currentUses =
        focus->maxUses;
}

bool spendFocus(
    Character& monk,
    int amount
)
{
    SpecialAction* focus =
        findSpecial(
            monk,
            SpecialType::Focus
        );

    if(focus == nullptr)
        return false;

    if(focus->currentUses < amount)
        return false;

    focus->currentUses -= amount;

    return true;
}

/////////////////////////////////////////////////////
// Martial Arts
/////////////////////////////////////////////////////

void prepareMartialArts(
    Character& monk
)
{
    monk.status.martialArtsReady = true;
}

void clearMartialArts(
    Character& monk
)
{
    monk.status.martialArtsReady = false;
}

bool hasMartialArtsReady(
    const Character& monk
)
{
    return monk.status.martialArtsReady;
}

/////////////////////////////////////////////////////
// Flurry of Blows
/////////////////////////////////////////////////////

bool canUseFlurryOfBlows(
    const Character& monk
)
{
    return hasFocus(monk);
}

void prepareFlurryOfBlows(
    Character& monk
)
{
    if(!spendFocus(monk,1))
        return;

    monk.status.flurryReady = true;

    registerFlurryOfBlows(
        monk.statistics
    );
}

void clearFlurryOfBlows(
    Character& monk
)
{
    monk.status.flurryReady = false;
}

bool hasFlurryReady(
    const Character& monk
)
{
    return monk.status.flurryReady;
}

/////////////////////////////////////////////////////
// Patient Defense
/////////////////////////////////////////////////////

void activatePatientDefense(
    Character& monk
)
{
    monk.status.patientDefense = true;

    monk.status.attackersHaveDisadvantage = true;

    monk.status.dexteritySaveAdvantage = true;

    registerPatientDefense(
        monk.statistics
    );
}

void clearPatientDefense(
    Character& monk
)
{
    monk.status.patientDefense = false;

    monk.status.attackersHaveDisadvantage = false;

    monk.status.dexteritySaveAdvantage = false;
}

bool isUsingPatientDefense(
    const Character& monk
)
{
    return monk.status.patientDefense;
}

/////////////////////////////////////////////////////
// Uncanny Metabolism
/////////////////////////////////////////////////////

bool canUseUncannyMetabolism(
    const Character& monk
)
{
    if(!monk.health.alive)
        return false;

    return
        getFocus(monk) <
        findSpecial(
            monk,
            SpecialType::Focus
        )->maxUses;
}

void useUncannyMetabolism(
    Character& monk
)
{
    if(!canUseUncannyMetabolism(monk))
        return;

    restoreFocus(
        monk
    );

    int healing =
        rollDice(1,6) + 2;

    healCharacter(
        monk,
        healing
    );

    registerHealing(
        monk.statistics,
        monk.statistics,
        healing
    );

    registerUncannyMetabolism(
        monk.statistics
    );
}