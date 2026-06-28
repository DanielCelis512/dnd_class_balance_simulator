#include "actions.h"
#include "dice.h"
#include "logger.h"

#include <algorithm>

// Rolls a d20 for the given character, taking into account advantage and disadvantage
int rollD20(
    Character& character
)
{
    int roll1 =
        rollDice(1,20);

    // Defines Advantage
    if(character.hasAdvantage)
    {
        int roll2 =
            rollDice(1,20);

        return std::max(
            roll1,
            roll2
        );
    }

    // Defines Disadvantage
    if(character.hasDisadvantage)
    {
        int roll2 =
            rollDice(1,20);

        return std::min(
            roll1,
            roll2
        );
    }

    return roll1;
}

// Defines the application of damage to a character, taking into account temporary hit points and overall health
void applyDamage(
    Character& target,
    int damage
)
{
    if(target.tempHp > 0)
    {
        if(target.tempHp >= damage)
        {
            target.tempHp -= damage;
            damage = 0;
        }
        else
        {
            damage -= target.tempHp;
            target.tempHp = 0;
        }
    }

    // Handle damage reduction due to Rage
    if(target.raging)
    {
        damage /= 2;

        combatLog(target.name);
        combatLog("'s Rage reduces the damage to ");
        combatLog(damage);
        combatLog(".\n");
    }


    if(damage > 0)
    {
        target.hp -= damage;
    }

    if(target.hp <= 0)
    {
        target.hp = 0;
        target.alive = false;
    }
}

// Retrieves the saving throw modifier for a character based on the specified save type
int getSaveModifier(
    Character& target,
    SaveType type
)
{
    switch(type)
    {
        case SaveType::Strength:
            return target.strSave;
        case SaveType::Dexterity:
            return target.dexSave;
        case SaveType::Constitution:
            return target.conSave;
        case SaveType::Intelligence:
            return target.intSave;
        case SaveType::Wisdom:
            return target.wisSave;
        case SaveType::Charisma:
            return target.chaSave;
        default:
            return 0;
    }
}

// Updates the status effects of a character, decrementing the duration of each effect and disabling it when its duration reaches zero
void updateStatusEffects(Character& character)
{
    if(character.raging && --character.rageRounds <= 0)
    {
        character.raging = false;
    }

    if(character.cuttingWordsActive &&
       --character.cuttingWordsRounds <= 0)
    {
        character.cuttingWordsActive = false;
    }

    if(character.favoredEnemy &&
       --character.favoredEnemyRounds <= 0)
    {
        character.favoredEnemy = false;
    }

    if(character.sneakAttackReady &&
       --character.sneakAttackRounds <= 0)
    {
        character.sneakAttackReady = false;
        character.hasAdvantage = false;
    }

    if(character.cursed &&
       --character.curseRounds <= 0)
    {
        character.cursed = false;
    }

    if(character.empoweredSpellRounds > 0 &&
       --character.empoweredSpellRounds <= 0)
    {
        character.bonusDamage = 0;
    }

    if(character.wildShapeActive &&
       --character.wildShapeRounds <= 0)
    {
        character.wildShapeActive = false;

        character.ac = character.originalAc;
        character.attackBonus = character.originalAttackBonus;
        character.damageDiceNumber = character.originalDamageDiceNumber;
        character.damageDiceSides = character.originalDamageDiceSides;
        character.damageModifier = character.originalDamageModifier;
        character.hasAdvantage = character.originalHasAdvantage;

        character.tempHp = 0;

        character.wildShapeForm = WildShapeForm::None;

        combatLog(character.name);
        combatLog(" reverts from Wild Shape to their original form.\n");
    }
}

// Defines the restoration of health to a character, ensuring that health does not exceed the maximum hit points
void restoreHealth(
    Character& target,
    int amount
)
{
    target.hp += amount;

    if(target.hp > target.maxHp)
    {
        target.hp = target.maxHp;
    }
}

// Defines the logic for a saving throw, which involves rolling a d20 and adding a modifier, then comparing the result to a difficulty class (DC) to determine success or failure
SaveResult savingThrow(
    int modifier,
    int dc
)
{
    int d20 =
        rollDice(1,20);

    int total =
        d20 +
        modifier;

    if(d20 == 1)
    {
        return SaveResult::CriticalFailure;
    }

    if(d20 == 20)
    {
        return SaveResult::CriticalSuccess;
    }

    if(total >= dc)
    {
        return SaveResult::Success;
    }

    return SaveResult::Failure;
}

// Attack function that handles the attack logic between two characters
bool attack(Character& attacker,
            Character& defender)
{
    int d20 = rollD20(attacker);

    int attackRoll =
        d20 +
        attacker.attackBonus;

    // Display the attack roll and the defender's AC
    combatLog(attacker.name);
    combatLog(" rolls "); 
    combatLog(attackRoll);
    combatLog(" vs AC ");
    combatLog(defender.ac);
    combatLog("\n");

    // Check for Cutting Words on the defender, which can reduce the attack roll by 1d6
    if(attacker.cuttingWordsActive == false &&
    defender.cuttingWordsActive)
    {
        combatLog(defender.name); 
        combatLog(" has Cutting Words active, reducing the attack roll by 1d6.\n");

        attackRoll -= rollDice(1,6);
    }

    // Store the original AC of the defender to restore it later
    int defenderAc =
    defender.ac;

    // If the defender has a shield equipped, increase their AC by 2 for this attack
    if(defender.shieldEquipped)
    {
        combatLog(defender.name);
        combatLog(" has a shield equipped, increasing AC by 2.\n");

        defenderAc += 2;
    }

    // Critical Miss
    if(d20 == 1)
    {
        combatLog(attacker.name);
        combatLog(" critically misses ");
        combatLog(defender.name);
        combatLog(".\n");

        return false;
    }

    // Critical Hit
    bool critical =
        (d20 == 20);

    if(critical)
    {
        combatLog(attacker.name);
        combatLog(" critically Hits ");
        combatLog(defender.name);
        combatLog(".\n");
    }

    // Critical Hit
    if(critical)
    {
    int damage =
        rollDice(
            attacker.damageDiceNumber * 2,
            attacker.damageDiceSides
        )
        + attacker.damageModifier;

    if(attacker.raging)
    {
        damage += 4;
    }

    if(attacker.extraDamageDiceNumber > 0)
    {
        damage +=
            rollDice(
                attacker.extraDamageDiceNumber * 2,
                attacker.extraDamageDiceSides
            );
    }

    if(attacker.favoredEnemy)
    {
        damage +=
            rollDice(1,6);
    }

    if(attacker.sneakAttackReady)
        {
            damage += 2*(rollDice(1,6));
            attacker.sneakAttackReady = false;
            attacker.hasAdvantage = false;
        }

    applyDamage(defender, damage);

    if(!defender.alive)
    {
        combatLog(defender.name);
        combatLog(" has been defeated!\n");
    }

    combatLog(attacker.name);
    combatLog(" critically hits ");
    combatLog(defender.name);
    combatLog(" for ");
    combatLog(damage);
    combatLog(" damage.\n");

    return true;

}

    // Normal Hit
    if(attackRoll >= defenderAc)
    {
    int damage =
        rollDice(
            attacker.damageDiceNumber,
            attacker.damageDiceSides
        )
        + attacker.damageModifier;

    if(attacker.raging)
    {
        damage += 2;
    }

    if(attacker.extraDamageDiceNumber > 0)
    {
        damage +=
            rollDice(
                attacker.extraDamageDiceNumber,
                attacker.extraDamageDiceSides
            );
    }

    if(attacker.favoredEnemy)
    {
    damage += rollDice(1,6);
    }

    if(attacker.sneakAttackReady)
    {
    damage += rollDice(1,6);

    attacker.sneakAttackReady = false;
    attacker.hasAdvantage = false;
    attacker.sneakAttackRounds = 0;
    }

    applyDamage(defender, damage);

    if(!defender.alive)
    {
        combatLog(defender.name);
        combatLog(" has been defeated!\n");
    }

    combatLog(attacker.name);
    combatLog(" hits ");
    combatLog(defender.name);
    combatLog(" for ");
    combatLog(damage);
    combatLog(" damage.\n");

    return true;
}

    combatLog(attacker.name);
    combatLog(" misses ");
    combatLog(defender.name);
    combatLog(".\n");

    return false;
}

// Defines the logic for a magic attack, which involves rolling a d20 and comparing it to the target's AC, taking into account the caster's magic uses and modifiers
bool magicAttack(
    Character& caster,
    Character& target
)
{
    // Store the original AC of the target to restore it later
    int targetAc =
    target.ac;

    // If the target has a shield equipped, increase their AC by 2 for this attack
    if(target.shieldEquipped)
    {
        combatLog(target.name);
        combatLog(" has a shield equipped, increasing AC by 2.\n");

        targetAc += 2;
    }

    // Check if the caster has any magic uses left
    if(caster.magicUses <= 0)
    {
        return false;
    }

    caster.magicUses--;

    int d20 =
        rollD20(caster);

    int attackRoll =
        d20 +
        caster.magicModifier;

    // Check for Cutting Words on the defender, which can reduce the attack roll by 1d6
    if(caster.cuttingWordsActive == false &&
    target.cuttingWordsActive)
    {
        combatLog(target.name); 
        combatLog(" has Cutting Words active, reducing the attack roll by 1d6.\n");

        attackRoll -= rollDice(1,6);
    }
    
    combatLog(caster.name);
    combatLog(" casts a spell. Roll ");
    combatLog(attackRoll);
    combatLog(" vs AC ");
    combatLog(targetAc);
    combatLog("\n");

    if(d20 == 1)
    {
        combatLog("Critical miss!\n");

        return false;
    }

    bool critical =
        (d20 == 20);

    if(critical)
    {
        combatLog(caster.name);
        combatLog(" critically hits with magic!\n");
    }

    if(critical ||
       attackRoll >= targetAc)
    {
        int dice =
            caster.magicDiceNumber;

        if(critical)
        {
            dice *= 2;
        }

        int damage =
            rollDice(
                dice,
                caster.magicDiceSides
            )
            + caster.magicModifier;

        if(caster.favoredEnemy)
        {
            damage +=
                rollDice(1,6);
        }

        if(target.cursed)
        {
            damage += rollDice(1,6);
        }

        damage += caster.bonusDamage;

        applyDamage(
            target,
            damage
        );

        combatLog(target.name);
        combatLog(" takes ");
        combatLog(damage);
        combatLog(" magic damage.\n");

        return true;
    }

    combatLog(caster.name);
    combatLog(" misses.\n");

    return false;
}

// Defines the logic for a saving throw attack, which involves rolling a saving throw for the target and applying damage if the target fails the saving throw, taking into account the caster's magic uses and modifiers
bool savingThrowAttack(
    Character& caster,
    Character& target,
    int saveModifier
)
{
    if(caster.magicUses <= 0)
    {
        return false;
    }

    caster.magicUses--;

    SaveResult result =
        savingThrow(
            saveModifier,
            caster.spellDc
        );


    int damage =
        rollDice(
            caster.magicDiceNumber,
            caster.magicDiceSides
        )
        + caster.magicModifier;

    switch(result)
    {
        case SaveResult::CriticalSuccess:
        {
            combatLog(target.name);
            combatLog(" critically succeeds the save!\n");

            return false;
        }

        case SaveResult::Success:
        {
            damage /= 2;

            combatLog(target.name);
            combatLog(" succeeds the save!\n");

            break;
        }

        case SaveResult::Failure:
        {
            combatLog(target.name);
            combatLog(" fails the save!\n");

            break;
        }

        case SaveResult::CriticalFailure:
        {
            damage *= 2;

            combatLog(target.name);
            combatLog(" critically fails the save!\n");

            break;
        }
    }

    damage += caster.bonusDamage;

    applyDamage(
        target,
        damage
    );

    combatLog(target.name);
        combatLog(" takes ");
        combatLog(damage);
        combatLog(" spell damage.\n");

    return true;
}

// Defines the logic for a cantrip attack, which involves rolling a d20 and comparing it to the target's AC, taking into account the caster's cantrip uses and modifiers
bool cantripAttack(
    Character& caster,
    Character& target
)
{
    // Store the original AC of the target to restore it later
    int targetAc =
    target.ac;

    // If the target has a shield equipped, increase their AC by 2 for this attack
    if(target.shieldEquipped)
    {
        combatLog(target.name);
        combatLog(" has a shield equipped, increasing AC by 2.\n");

        targetAc += 2;
    }

    int d20 =
        rollD20(caster);
        

    if(d20 == 1)
    {
        return false;
    }

    bool critical =
        (d20 == 20);

    int attackRoll =
        d20 +
        caster.cantripModifier;


    combatLog(caster.name);
    combatLog(" casts a cantrip. Roll ");
    combatLog(attackRoll);
    combatLog(" vs AC ");
    combatLog(targetAc);
    combatLog("\n");

    // Check for Cutting Words on the defender, which can reduce the attack roll by 1d6
    if(caster.cuttingWordsActive == false &&
    target.cuttingWordsActive)
    {
        combatLog(target.name); 
        combatLog(" has Cutting Words active, reducing the attack roll by 1d6.\n");

        attackRoll -= rollDice(1,6);
    }

    if(critical ||
       attackRoll >= targetAc)
    {
        int dice =
            caster.cantripDiceNumber;

        if(critical)
        {
            dice *= 2;
        }

        int damage =
            rollDice(
                dice,
                caster.cantripDiceSides
            )
            + caster.cantripModifier;

        if(target.cursed)
        {
            damage += rollDice(1,6);
        }

        damage += caster.bonusDamage;

        applyDamage(
            target,
            damage
        );

        combatLog(target.name);
        combatLog(" takes ");
        combatLog(damage);
        combatLog(" cantrip damage.\n");    

        return true;
    }

    combatLog(caster.name);
    combatLog(" misses with the cantrip.\n");

    return false;
}

// Defines the logic for a cantrip saving throw attack, which involves rolling a saving throw for the target and applying damage if the target fails the saving throw, taking into account the caster's cantrip uses and modifiers
bool cantripSavingThrow(
    Character& caster,
    Character& target,
    int saveModifier
)
{
    SaveResult result =
        savingThrow(
            saveModifier,
            caster.spellDc
        );

    int damage =
        rollDice(
            caster.cantripDiceNumber,
            caster.cantripDiceSides
        )
        + caster.cantripModifier;

    damage += caster.bonusDamage;

    switch(result)
    {
        case SaveResult::CriticalSuccess:
        {
            combatLog(target.name);
            combatLog(" critically succeeds the save!\n");

            return false;
        }

        case SaveResult::Success:
        {
            damage /= 2;

            combatLog(target.name);
            combatLog(" succeeds the save!\n");

            break;
        }

        case SaveResult::Failure:
        {
            combatLog(target.name);
            combatLog(" fails the save!\n");

            break;
        }

        case SaveResult::CriticalFailure:
        {
            damage *= 2;

            combatLog(target.name);
            combatLog(" critically fails the save!\n");

            break;
        }
    }

    applyDamage(
        target,
        damage
    );

    combatLog(target.name);
    combatLog(" takes ");
    combatLog(damage);
    combatLog(" cantrip damage.\n");

    return true;
}

// Defines the logic for healing, which involves rolling a healing die and applying the result to the target's health, taking into account the healer's healing uses and modifiers
bool heal(
    Character& healer,
    Character& target
)
{
    if(healer.healingUses <= 0)
    {
        return false;
    }

    healer.healingUses--;

    int amount =
        rollDice(
            healer.healingDiceNumber,
            healer.healingDiceSides
        )
        + healer.healingModifier;

    restoreHealth(
        target,
        amount
    );

    combatLog(healer.name);
    combatLog(" heals ");
    combatLog(target.name);
    combatLog(" for ");
    combatLog(amount);
    combatLog(" HP.\n");

    return true;
}

// Defines the logic for using a special ability, which varies based on the character's class type and the number of special uses remaining
bool useSpecial(
    Character& user,
    Character& target
)
{
    if(user.specialUses <= 0)
    {
        return false;
    }

    user.specialUses--;

    switch(user.classType)
    {
        case ClassType::Barbarian:
        {
            user.raging = true;
            user.rageRounds = 3;

            combatLog(user.name);
            combatLog(" enters Rage!\n");

            break;
        }

        case ClassType::Bard:
        {
            user.cuttingWordsActive = true;
            user.cuttingWordsRounds = 2;

            combatLog(user.name);
            combatLog(" uses Cutting Words.\n");

            break;
        }

        case ClassType::Cleric:
        {
            int damage =
                rollDice(2,8)
                + user.magicModifier;

            applyDamage(
                target,
                damage
            );

            combatLog(user.name);
            combatLog(" uses Divine Spark for ");
            combatLog(damage);
            combatLog(" damage.\n");

            break;
        }

        case ClassType::Druid:
        {
            if(!user.wildShapeActive)
            {
                user.originalAc = user.ac;
                user.originalAttackBonus = user.attackBonus;

                user.originalDamageDiceNumber = user.damageDiceNumber;
                user.originalDamageDiceSides = user.damageDiceSides;
                user.originalDamageModifier = user.damageModifier;

                user.originalHasAdvantage = user.hasAdvantage;
            }

            user.wildShapeActive = true;
            user.wildShapeRounds = 3;

            switch(user.wildShapeForm)
            {
                case WildShapeForm::Wolf:
                {
                    user.ac = 13;

                    user.attackBonus = 4;

                    user.damageDiceNumber = 1;
                    user.damageDiceSides = 6;
                    user.damageModifier = 2;

                    user.tempHp = 13;

                    user.hasAdvantage = false;

                    combatLog(user.name);
                    combatLog(" transforms into a Wolf!\n");
                    break;
                }

                case WildShapeForm::Snake:
                {
                    user.ac = 15;

                    user.attackBonus = 5;

                    user.damageDiceNumber = 1;
                    user.damageDiceSides = 4;
                    user.damageModifier = 3;

                    user.tempHp = 9;

                    user.hasAdvantage = true;

                    combatLog(user.name);
                    combatLog(" transforms into a Snake!\n");
                    break;
                }

                default:
                {
                    combatLog(" No wild shape selected.\n");
                    return false;
                }
            }

            break;
        }

        case ClassType::Fighter:
        {
            restoreHealth(
                user,
                rollDice(1,10)
            );

            attack(user,target);

            if(target.alive)
            {
                attack(user,target);
            }

            combatLog(user.name);
            combatLog(" uses Action Surge!\n");

            break;
        }

        case ClassType::Monk:
        {
            int damage =
                rollDice(2,6)
                + user.damageModifier;

            applyDamage(
                target,
                damage
            );

            combatLog(user.name);
            combatLog(" uses Flurry of Blows for ");
            combatLog(damage);
            combatLog(" damage.\n");

            break;
        }

        case ClassType::Paladin:
        {
            restoreHealth(
                user,
                10
            );

            combatLog(user.name);
            combatLog(" uses Lay on Hands!\n");

            break;
        }

        case ClassType::Ranger:
        {
            user.favoredEnemy = true;
            user.favoredEnemyRounds = 3;

            combatLog(user.name);
            combatLog(" marks Favored Enemy!\n");

            break;
        }

        case ClassType::Rogue:
        {
            user.hasAdvantage = true;

            user.sneakAttackReady = true;
            user.sneakAttackRounds = 2;

            combatLog(user.name);
            combatLog(" prepares Sneak Attack!\n");

            break;
        }

        case ClassType::Sorcerer:
        {
            user.empoweredSpellRounds = 2;

            user.bonusDamage = 4;

            combatLog(user.name);
            combatLog(" uses Empowered Spell!\n");

            break;
        }

        case ClassType::Warlock:
        {
            target.cursed = true;
            target.curseRounds = 2;

            combatLog(user.name);
            combatLog(" casts Hex!\n");

            break;
        }

        case ClassType::Wizard:
        {
            user.magicUses =
                std::min(
                    user.magicUses +2,
                    user.maxMagicUses
            );

            combatLog(user.name);
            combatLog(" uses Arcane Recovery!\n");

            break;
        }
        }
        
    return true;
}   