#include "bard_specials.h"

#include "../../combat_actions.h"
#include "../../combat_utils.h"
#include "../../combat/combat_statistics.h"

#include "../../dice.h"

#include "../spell_utils.h"
#include "../saving_throw.h"

/////////////////////////////////////////////////////
// Bardic Inspiration
/////////////////////////////////////////////////////

bool canUseBardicInspiration(
    const Character& bard
)
{
    if(!bard.health.alive)
        return false;

    if(bard.status.wildShapeActive)
        return false;

    const SpecialAction* inspiration =
        findSpecial(
            bard,
            SpecialType::BardicInspiration
        );

    if(inspiration == nullptr)
        return false;

    return inspiration->currentUses > 0;
}

void castBardicInspiration(
    Character& bard,
    Character& ally
)
{
    if(!canUseBardicInspiration(bard))
        return;

    SpecialAction* inspiration =
        findSpecial(
            bard,
            SpecialType::BardicInspiration
        );

    if(inspiration == nullptr)
        return;

    inspiration->currentUses--;

    ally.status.bardicInspirationActive = true;

    ally.timers.bardicInspirationRounds = 10;
}

void consumeBardicInspiration(
    Character& character
)
{
    character.status.bardicInspirationActive = false;

    character.timers.bardicInspirationRounds = 0;
}

bool hasBardicInspiration(
    const Character& character
)
{
    return
        character.status.bardicInspirationActive;
}

int consumeBardicInspirationBonus(
    Character& character
)
{
    if(!hasBardicInspiration(character))
        return 0;

    int bonus =
        rollDice(1,6);

    consumeBardicInspiration(
        character
    );

    return bonus;
}

void updateBardicInspiration(
    Character& character
)
{
    if(
        !character.status.bardicInspirationActive
    )
    {
        return;
    }

    character.timers.bardicInspirationRounds--;

    if(
        character.timers.bardicInspirationRounds <= 0
    )
    {
        consumeBardicInspiration(
            character
        );
    }
}

/////////////////////////////////////////////////////
// Cutting Words
/////////////////////////////////////////////////////

bool canUseCuttingWords(
    const Character& bard
)
{
    if(!bard.health.alive)
        return false;

    const SpecialAction* inspiration =
        findSpecial(
            bard,
            SpecialType::BardicInspiration
        );

    if(inspiration == nullptr)
        return false;

    return inspiration->currentUses > 0;
}

int applyCuttingWordsToAttack(
    Character& bard,
    int attackTotal
)
{
    if(!canUseCuttingWords(bard))
        return attackTotal;

    SpecialAction* inspiration =
        findSpecial(
            bard,
            SpecialType::BardicInspiration
        );

    if(inspiration == nullptr)
        return attackTotal;

    inspiration->currentUses--;

    attackTotal -= rollDice(1,6);

    return attackTotal;
}

int applyCuttingWordsToDamage(
    Character& bard,
    int damage
)
{
    if(!canUseCuttingWords(bard))
        return damage;

    SpecialAction* inspiration =
        findSpecial(
            bard,
            SpecialType::BardicInspiration
        );

    if(inspiration == nullptr)
        return damage;

    inspiration->currentUses--;

    damage -= rollDice(1,6);

    if(damage < 0)
        damage = 0;

    return damage;
}

int applyCuttingWordsToSavingThrow(
    Character& bard,
    int saveTotal
)
{
    if(!canUseCuttingWords(bard))
        return saveTotal;

    SpecialAction* inspiration =
        findSpecial(
            bard,
            SpecialType::BardicInspiration
        );

    if(inspiration == nullptr)
        return saveTotal;

    inspiration->currentUses--;

    saveTotal -= rollDice(1,6);

    return saveTotal;
}