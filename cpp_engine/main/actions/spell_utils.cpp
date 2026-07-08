#include "spell_utils.h"

/////////////////////////////////////////////////////
// Spell Slots
/////////////////////////////////////////////////////

bool hasSpellSlot(
    const Character& caster,
    SpellLevel level
)
{
    if(level == SpellLevel::Cantrip)
        return true;

    int index =
        static_cast<int>(level) - 1;

    if(index < 0)
        return false;

    if(index >= caster.spellSlots.current.size())
        return false;

    return
        caster.spellSlots.current[index] > 0;
}

bool consumeSpellSlot(
    Character& caster,
    SpellLevel level
)
{
    if(level == SpellLevel::Cantrip)
        return true;

    if(!hasSpellSlot(caster, level))
        return false;

    int index =
        static_cast<int>(level) - 1;

    caster.spellSlots.current[index]--;

    return true;
}

void restoreSpellSlots(
    Character& caster
)
{
    caster.spellSlots.current =
        caster.spellSlots.maximum;
}

/////////////////////////////////////////////////////
// Spell Save DC
/////////////////////////////////////////////////////

int getSpellSaveDC(
    const Character& caster
)
{
    return
        8 +
        caster.proficiencyBonus +
        caster.spellcastingModifier;
}

/////////////////////////////////////////////////////
// Spell Attack Bonus
/////////////////////////////////////////////////////

int getSpellAttackBonus(
    const Character& caster
)
{
    return
        caster.proficiencyBonus +
        caster.spellcastingModifier;
}

/////////////////////////////////////////////////////
// Concentration
/////////////////////////////////////////////////////

bool canConcentrate(
    const Character& caster
)
{
    return
        !caster.status.concentrating;
}

void beginConcentration(
    Character& caster,
    int rounds
)
{
    caster.status.concentrating = true;

    caster.timers.concentrationRounds =
        rounds;
}

void endConcentration(
    Character& caster
)
{
    caster.status.concentrating = false;

    caster.timers.concentrationRounds = 0;
}

void updateConcentration(
    Character& caster
)
{
    if(
        !caster.status.concentrating
    )
    {
        return;
    }

    caster.timers.concentrationRounds--;

    if(
        caster.timers.concentrationRounds <= 0
    )
    {
        endConcentration(
            caster
        );
    }
}

bool canCastSpell(
    const Character& caster,
    const MagicalAction& spell
)
{
    //------------------------------------------
    // Alive
    //------------------------------------------

    if(!caster.health.alive)
        return false;

    //------------------------------------------
    // Spellcaster
    //------------------------------------------

    if(!caster.isCaster)
        return false;

    //------------------------------------------
    // Wild Shape
    //------------------------------------------

    if(caster.status.wildShapeActive)
        return false;

    //------------------------------------------
    // Action economy
    //------------------------------------------

    switch(spell.actionType)
    {
        case MagicalAction::ActionType::Action:

            if(!caster.status.canTakeActions)
                return false;

            break;

        case MagicalAction::ActionType::BonusAction:

            if(!caster.status.canTakeBonusActions)
                return false;

            break;

        case MagicalAction::ActionType::Reaction:

            if(!caster.status.canTakeReactions)
                return false;

            break;
    }

    //------------------------------------------
    // Spell Slot
    //------------------------------------------

    if(
        !hasSpellSlot(
            caster,
            spell.level
        )
    )
    {
        return false;
    }

    //------------------------------------------
    // Concentration
    //------------------------------------------

    if(
        spell.requiresConcentration &&
        caster.status.concentrating
    )
    {
        return false;
    }

    return true;
}

/////////////////////////////////////////////////////
// Cast Spell
/////////////////////////////////////////////////////

bool castSpell(
    Character& caster,
    const MagicalAction& spell
)
{
    //------------------------------------------
    // Can Cast?
    //------------------------------------------

    if(
        !canCastSpell(
            caster,
            spell
        )
    )
    {
        return false;
    }

    //------------------------------------------
    // Consume Spell Slot
    //------------------------------------------

    if(
        !consumeSpellSlot(
            caster,
            spell.level
        )
    )
    {
        return false;
    }

    //------------------------------------------
    // Start Concentration
    //------------------------------------------

    if(
        spell.requiresConcentration
    )
    {
        beginConcentration(
            caster,
            spell.concentrationRounds
        );
    }

    //------------------------------------------
    // Register Statistics
    //------------------------------------------

    registerSpellCast(
        caster.statistics
    );

    //------------------------------------------
    // Spell Successfully Cast
    //------------------------------------------

    return true;
}

/////////////////////////////////////////////////////
// Find Spell
/////////////////////////////////////////////////////

MagicalAction* findSpell(
    Character& caster,
    const std::string& name
)
{
    for(auto& spell : caster.spells)
    {
        if(spell.name == name)
        {
            return &spell;
        }
    }

    return nullptr;
}

const MagicalAction* findSpell(
    const Character& caster,
    const std::string& name
)
{
    for(const auto& spell : caster.spells)
    {
        if(spell.name == name)
        {
            return &spell;
        }
    }

    return nullptr;
}

MagicalAction* findCantrip(
    Character& caster,
    const std::string& name
)
{
    for(auto& cantrip : caster.cantrips)
    {
        if(cantrip.name == name)
        {
            return &cantrip;
        }
    }

    return nullptr;
}

const MagicalAction* findCantrip(
    const Character& caster,
    const std::string& name
)
{
    for(const auto& cantrip : caster.cantrips)
    {
        if(cantrip.name == name)
        {
            return &cantrip;
        }
    }

    return nullptr;
}