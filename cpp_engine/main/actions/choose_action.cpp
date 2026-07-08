#include "choose_action.h"

#include "ai_dispatcher.h"

ActionType chooseAction(
    Character& attacker,
    Character& defender
)
{
    return dispatchAI(
        attacker,
        defender
    );
}