#include "paladin_specials.h"

#include "combat/combat_statistics.h"
#include "spell_effects.h"
#include "spell_utils.h"

#include "../../combat_actions.h"
#include "../../combat_utils.h"

/////////////////////////////////////////////////////
// Divine Smite
/////////////////////////////////////////////////////

bool canPrepareDivineSmite(
    const Character& paladin
)
{
    if(!paladin.health.alive)
        return false;

    if(paladin.status.bonusActionUsed)
        return false;

    if(paladin.status.divineSmiteReady)
        return false;

    const MagicalAction* smite =
        findSpell(
            paladin,
            "Divine Smite"
        );

    if(smite == nullptr)
        return false;

    const SpecialAction* freeUse =
        findSpecial(
            paladin,
            SpecialType::DivineSmite
        );

    if(
        freeUse &&
        freeUse->currentUses > 0
    )
    {
        return true;
    }

    return hasSpellSlot(
        paladin,
        SpellLevel::Level1
    );
}

void prepareDivineSmite(
    Character& paladin
)
{
    if(
        !canPrepareDivineSmite(
            paladin
        )
    )
    {
        return;
    }

    paladin.status.divineSmiteReady = true;

    paladin.status.bonusActionUsed = true;
}

bool shouldTriggerDivineSmite(
    const Character& paladin
)
{
    return
        paladin.status.divineSmiteReady;
}

void consumeDivineSmite(
    Character& paladin
)
{
    if(
        !paladin.status.divineSmiteReady
    )
    {
        return;
    }

    SpecialAction* freeUse =
        findSpecial(
            paladin,
            SpecialType::DivineSmite
        );

    if(
        freeUse &&
        freeUse->currentUses > 0
    )
    {
        freeUse->currentUses--;
    }

    registerDivineSmite(
        paladin.statistics
    );

    clearDivineSmite(
        paladin
    );
}

void clearDivineSmite(
    Character& paladin
)
{
    paladin.status.divineSmiteReady =
        false;
}

/////////////////////////////////////////////////////
// Lay on Hands
/////////////////////////////////////////////////////

bool canUseLayOnHands(
    const Character& paladin
)
{
    if(!paladin.health.alive)
        return false;

    if(
        paladin.status.layOnHandsUsed
    )
        return false;

    return
        paladin.health.hp <
        paladin.health.maxHp;
}

void useLayOnHands(
    Character& paladin
)
{
    if(!canUseLayOnHands(paladin))
        return;

    healCharacter(
        paladin,
        10
    );

    paladin.status.bonusActionUsed = true;

    paladin.status.layOnHandsUsed = true;

    registerHealing(
        paladin.statistics,
        paladin.statistics,
        10
    );
}

/////////////////////////////////////////////////////
// Shield of Faith
/////////////////////////////////////////////////////

bool canCastShieldOfFaith(
    const Character& paladin
)
{
    if(!paladin.health.alive)
        return false;

    if(
        paladin.status.shieldEquipped
    )
        return false;

    if(
        paladin.status.concentrating
    )
        return false;

    const MagicalAction* spell =
        findSpell(
            paladin,
            "Shield of Faith"
        );

    if(spell == nullptr)
        return false;

    return
        hasSpellSlot(
            paladin,
            SpellLevel::Level1
        );
}

void castShieldOfFaith(
    Character& paladin
)
{
    if(!canCastShieldOfFaith(paladin))
        return;

    const MagicalAction* spell =
        findSpell(
            paladin,
            "Shield of Faith"
        );

    if(
        spell == nullptr ||
        !castSpell(
            paladin,
            *spell
        )
    )
    {
        return;
    }

    paladin.status.concentrating = true;

    paladin.status.shieldOfFaith = true;

    paladin.bonusAc += 2;

    paladin.timers.shieldOfFaithRounds = 10;

    paladin.status.bonusActionUsed = true;

    registerSpellCast(
        paladin.statistics
    );
}

void updateShieldOfFaith(
    Character& paladin
)
{
    if(
        !paladin.status.shieldOfFaith
    )
        return;

    paladin.timers.shieldOfFaithRounds--;

    if(
        paladin.timers.shieldOfFaithRounds <= 0
    )
    {
        removeShieldOfFaith(
            paladin
        );
    }
}

void removeShieldOfFaith(
    Character& paladin
)
{
    if(
        !paladin.status.shieldOfFaith
    )
        return;

    paladin.status.shieldOfFaith = false;

    paladin.status.concentrating = false;

    paladin.bonusAc -= 2;

    paladin.timers.shieldOfFaithRounds = 0;
}