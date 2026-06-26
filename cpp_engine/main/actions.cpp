#include "actions.h"
#include "dice.h"

#include <iostream>
#include <algorithm>

// Rolls a d20 for the given character, taking into account advantage and disadvantage
int rollD20(
    Character& character
)
{
    int roll1 =
        rollDice(1,20);

    if(character.hasAdvantage)
    {
        int roll2 =
            rollDice(1,20);

        return std::max(
            roll1,
            roll2
        );
    }

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

    if(damage > 0)
    {
        target.hp -= damage;
    }

    // Handle damage reduction due to Rage
    if(target.raging)
    {
        damage /= 2;

        std::cout
            << target.name
            << " reduces "
            << damage
            << " damage due to Rage.\n";
    }

    if(target.hp <= 0)
    {
        target.hp = 0;
        target.alive = false;
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
    std::cout
        << attacker.name
        << " rolls "
        << attackRoll
        << " vs AC "
        << defender.ac
        << "\n";

    // Check for Bardic Inspiration on the defender, which can reduce the attack roll by 1d6
    if(attacker.bardicInspirationActive == false &&
    defender.bardicInspirationActive)
    {
        std::cout
            << defender.name
            << " has Bardic Inspiration active, reducing the attack roll by 1d6.\n";
        attackRoll -= rollDice(1,6);
    }

    // If the defender has a shield equipped, increase their AC by 2 for this attack
    if(defender.shieldEquipped)
    {
        std::cout
            << defender.name
            << " has a shield equipped, increasing AC by 2.\n";

        defender.ac += 2;
    }

    // Critical Miss
    if(d20 == 1)
    {
        std::cout
            << attacker.name
            << " critically misses "
            << defender.name
            << ".\n";

        return false;
    }

    // Critical Hit
    bool critical =
        (d20 == 20);

    if(critical)
    {
        std::cout
            << attacker.name
            << " critically hits "
            << defender.name
            << "!\n";
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
            damage += rollDice(1,6);
        }

    applyDamage(defender, damage);

    if(!defender.alive)
    {
        std::cout
            << defender.name
            << " has been defeated!\n";
    }

    std::cout
        << attacker.name
        << " critically hits "
        << defender.name
        << " for "
        << damage
        << " damage.\n";

    return true;

}

    // Normal Hit
    if(attackRoll > defender.ac)
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

    applyDamage(defender, damage);

    if(!defender.alive)
    {
        std::cout
            << defender.name
            << " has been defeated!\n";
    }

    std::cout
        << attacker.name
        << " hits "
        << defender.name
        << " for "
        << damage
        << " damage.\n";

    return true;
}

    std::cout
        << attacker.name
        << " misses "
        << defender.name
        << ".\n";

    return false;
}

// Defines the logic for a magic attack, which involves rolling a d20 and comparing it to the target's AC, taking into account the caster's magic uses and modifiers
bool magicAttack(
    Character& caster,
    Character& target
)
{
    // If the target has a shield equipped, increase their AC by 2 for this attack
    if(target.shieldEquipped)
    {
        std::cout
            << target.name
            << " has a shield equipped, increasing AC by 2.\n";

        target.ac += 2;
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

    std::cout
        << caster.name
        << " casts a spell. Roll "
        << attackRoll
        << " vs AC "
        << target.ac
        << "\n";

    if(caster.bardicInspirationActive == false &&
    target.bardicInspirationActive)
    {
        std::cout
            << target.name
            << " has Bardic Inspiration active, reducing the attack roll by 1d6.\n";
        attackRoll -= rollDice(1,6);
    }

    if(d20 == 1)
    {
        std::cout
            << "Critical miss!\n";

        return false;
    }

    bool critical =
        (d20 == 20);

    if(critical)
    {
        std::cout
            << caster.name
            << " critically hits with magic!\n";
    }

    if(critical ||
       attackRoll >= target.ac)
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

        applyDamage(
            target,
            damage
        );

        std::cout
            << target.name
            << " takes "
            << damage
            << " magic damage.\n";

        return true;

        if(caster.favoredEnemy)
        {
            damage +=
                rollDice(1,6);
        }

        if(caster.cursed)
        {
            damage += rollDice(1,6);
        }
    }

    std::cout
        << caster.name
        << " misses.\n";

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
            std::cout
                << target.name
                << " critically succeeds the save!\n";

            return false;
        }

        case SaveResult::Success:
        {
            damage /= 2;

            std::cout
                << target.name
                << " succeeds the save.\n";

            break;
        }

        case SaveResult::Failure:
        {
            std::cout
                << target.name
                << " fails the save.\n";

            break;
        }

        case SaveResult::CriticalFailure:
        {
            damage *= 2;

            std::cout
                << target.name
                << " critically fails the save!\n";

            break;
        }
    }

    applyDamage(
        target,
        damage
    );

    std::cout
        << target.name
        << " takes "
        << damage
        << " spell damage.\n";

    return true;
}

// Defines the logic for a cantrip attack, which involves rolling a d20 and comparing it to the target's AC, taking into account the caster's cantrip uses and modifiers
bool cantripAttack(
    Character& caster,
    Character& target
)
{
    // If the target has a shield equipped, increase their AC by 2 for this attack
    if(target.shieldEquipped)
    {
        std::cout
            << target.name
            << " has a shield equipped, increasing AC by 2.\n";

        target.ac += 2;
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

    if(caster.bardicInspirationActive == false &&
    target.bardicInspirationActive)
    {
        std::cout
            << target.name
            << " has Bardic Inspiration active, reducing the attack roll by 1d6.\n";
        attackRoll -= rollDice(1,6);
    }

    if(critical ||
       attackRoll >= target.ac)
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

        applyDamage(
            target,
            damage
        );

        if(caster.cursed)
        {
            damage += rollDice(1,6);
        }

        return true;
    }

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

    switch(result)
    {
        case SaveResult::CriticalSuccess:
            return false;

        case SaveResult::Success:
            damage /= 2;
            break;

        case SaveResult::Failure:
            break;

        case SaveResult::CriticalFailure:
            damage *= 2;
            break;
    }

    applyDamage(
        target,
        damage
    );

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

    std::cout
        << healer.name
        << " heals "
        << target.name
        << " for "
        << amount
        << " HP.\n";

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

            user.damageReduction = 50;

            std::cout
                << user.name
            << " enters Rage!\n";

            break;
        }

        case ClassType::Bard:
        {
            user.bardicInspirationActive = true;
            user.bardicInspirationRounds = 2;

            std::cout
                << user.name
                << " uses Bardic Inspiration.\n";

            break;
        }

        case ClassType::Cleric:
        {
            int damage =
                rollDice(2,8);

            applyDamage(
                target,
                damage
            );

            std::cout
                << user.name
                << " uses Divine Spark for "
                << damage
                << " damage.\n";

            break;
        }
        case ClassType::Druid:
        {
            user.wildShapeActive = true;

            user.tempHp =
                rollDice(2,10)
                + 2;

            user.attackBonus = 4;

            user.damageDiceNumber = 1;
            user.damageDiceSides = 6;
            user.damageModifier = 2;

            if(user.wildShapeForm ==
            WildShapeForm::Wolf)
            {
                user.wildShapeForm =
                    WildShapeForm::Wolf;

                user.tempHp = 13;

                std::cout
                    << user.name
                    << " transforms into a Wolf!\n";
            }
            else if(user.wildShapeForm ==
            WildShapeForm::Snake)
            {
                user.wildShapeForm =
                    WildShapeForm::Snake;

                user.tempHp = 9;

                user.hasAdvantage = true;

                std::cout
                    << user.name
                    << " transforms into a Snake!\n";
            }
            else 
                user.wildShapeForm = WildShapeForm::None;
            break;
        }

        case ClassType::Fighter:
        {
            restoreHealth(
                user,
                rollDice(1,10)
            );

            attack(user,target);
            attack(user,target);

            std::cout
                << user.name
                << " uses Action Surge!\n";

            break;
        }

        case ClassType::Monk:
        {
            int damage =
                rollDice(2,6);

            applyDamage(
                target,
                damage
            );

            std::cout
                << user.name
                << " uses Flurry of Blows for "
                << damage
                << " damage!\n";

            break;
        }

        case ClassType::Paladin:
        {
            restoreHealth(
                user,
                10
            );

            std::cout
                << user.name
                << " uses Lay On Hands.\n";

            break;
        }

        case ClassType::Ranger:
        {
            user.favoredEnemy = true;
            user.favoredEnemyRounds = 3;

            std::cout
                << user.name
                << " marks Favored Enemy.\n";

            break;
        }

        case ClassType::Rogue:
        {
            user.hasAdvantage = true;

            user.sneakAttackReady = true;
            user.sneakAttackRounds = 2;

            std::cout
                << user.name
                << " prepares Sneak Attack.\n";

            break;
        }

        case ClassType::Sorcerer:
        {
            user.empoweredSpellRounds = 2;

            user.bonusDamage += 4;

            std::cout
                << user.name
                << " empowers the next spell.\n";

            break;
        }

        case ClassType::Warlock:
        {
            user.cursed = true;
            user.curseRounds = 2;

            std::cout
                << user.name
                << " casts Hex.\n";

            break;
        }

        case ClassType::Wizard:
        {
            user.magicUses =
                user.maxMagicUses;

            std::cout
                << user.name
                << " uses Arcane Recovery.\n";

            break;
        }
        }
        
    return true;
}   