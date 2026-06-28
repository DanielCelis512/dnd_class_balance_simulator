#include "turn_manager.h"

#include "logger.h"
#include "actions.h"
#include "dice.h"

void updateStatusEffects(Character& character);

void executeTurn(
    Character& current,
    Character& enemy
)
{
    if(!current.alive)
    {
        return;
    }

    combatLog("\n----- ");
    combatLog(current.name);
    combatLog("'s Turn -----\n");

    updateStatusEffects(current);

    chooseAction(current, enemy);

    performAction(current, enemy);
}

void chooseAction(
    Character& current,
    Character& enemy
)
{
    if(current.canHeal &&
       current.healingUses > 0 &&
       current.hp <= current.maxHp / 3)
    {
        current.currentAction =
            ActionType::Heal;

        return;
    }

        if(current.specialUses > 0)
    {
        switch(current.classType)
        {
            case ClassType::Barbarian:

            if(!current.raging)
            {
                current.currentAction =
                    ActionType::Special;

                return;
            }

            break;

            case ClassType::Bard:

            if(!current.cuttingWordsActive)
            {
                current.currentAction =
                    ActionType::Special;

                return;
            }

            break;

            case ClassType::Cleric:

            if(enemy.hp < enemy.maxHp/2)
            {
                current.currentAction =
                    ActionType::Special;

                return;
            }

            break;

            case ClassType::Druid:

            if(!current.wildShapeActive &&
               current.hp < current.maxHp/2)
            {
                current.currentAction =
                    ActionType::Special;

                return;
            }

            break;

            case ClassType::Fighter:

            if(enemy.hp < enemy.maxHp/2)
            {
                current.currentAction =
                    ActionType::Special;

                return;
            }

            break;

            case ClassType::Monk:

            if(enemy.hp < enemy.maxHp/2)
            {
                current.currentAction =
                    ActionType::Special;

                return;
            }

            break;

            case ClassType::Paladin:

            if(current.hp < current.maxHp/2)
            {
                current.currentAction =
                    ActionType::Special;

                return;
            }

            break;

            case ClassType::Ranger:

            if(!current.favoredEnemy)
            {
                current.currentAction =
                    ActionType::Special;

                return;
            }

            break;

            case ClassType::Rogue:

            if(!current.sneakAttackReady)
            {
                current.currentAction =
                    ActionType::Special;

                return;
            }

            break;

            case ClassType::Sorcerer:

            if(current.empoweredSpellRounds == 0)
            {
                current.currentAction =
                    ActionType::Special;

                return;
            }

            break;

            case ClassType::Warlock:

            if(!enemy.cursed)
            {
                current.currentAction =
                    ActionType::Special;

                return;
            }

            break;

            case ClassType::Wizard:

            if(current.magicUses == 0)
            {
                current.currentAction =
                    ActionType::Special;

                return;
            }

            break;

        default:
            break;
        }
    }

    if(current.isCaster &&
       current.magicUses > 0)
    {
        current.currentAction =
            current.preferredAction;

        return;
    }

    if(current.canUseCantrips)
    {
        current.currentAction =
            ActionType::Cantrip;

        return;
    }

    current.currentAction =
        ActionType::Attack;
}

bool performAction(
    Character& current,
    Character& enemy
)
{
    switch(current.currentAction)
    {
        case ActionType::Attack:
            return attack(
                current,
                enemy
            );

            case ActionType::Magic:

        if(current.magicType ==
           MagicType::AttackRoll)
        {
            return magicAttack(
                current,
                enemy
            );
        }

        return savingThrowAttack(
            current,
            enemy,
            getSaveModifier(
                enemy,
                current.spellSaveType
            )
        );

            case ActionType::Cantrip:

        if(current.cantripType ==
           MagicType::AttackRoll)
        {
            return cantripAttack(
                current,
                enemy
            );
        }

        return cantripSavingThrow(
            current,
            enemy,
            getSaveModifier(
                enemy,
                current.cantripSaveType
            )
        );

            case ActionType::Heal:

        return heal(
            current,
            current
        );

            case ActionType::Special:

        return useSpecial(
            current,
            enemy
        );

        default:
        return false;
    }
}