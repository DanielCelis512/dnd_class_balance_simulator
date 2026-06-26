#include "class_factory.h"

// Function to create a Barbarian character
Character createBarbarian()
{
    Character barbarian{};

    barbarian.name = "Barbarian";
    barbarian.classType = ClassType::Barbarian;

    barbarian.str = 3;
    barbarian.dex = 1;
    barbarian.con = 2;
    barbarian.intel = -1;
    barbarian.wis = 1;
    barbarian.cha = 0;

    barbarian.strSave = 5;
    barbarian.dexSave = 1;
    barbarian.conSave = 4;
    barbarian.intSave = -1;
    barbarian.wisSave = 1;
    barbarian.chaSave = 0;

    barbarian.hp = 42;
    barbarian.maxHp = 42;

    barbarian.tempHp = 0;

    barbarian.ac = 13;

    barbarian.attackBonus = 5;

    barbarian.damageDiceNumber = 1;
    barbarian.damageDiceSides = 12;
    barbarian.damageModifier = 3;

    barbarian.magicUses = 0;
    barbarian.maxMagicUses = 0;

    barbarian.healingUses = 0;
    barbarian.maxHealingUses = 0;

    barbarian.specialUses = 2;
    barbarian.maxSpecialUses = 2;

    barbarian.raging = false;
    barbarian.rageRounds = 0;
    barbarian.damageReduction = 0;

    barbarian.bonusAc = 0;

    barbarian.preferredAction = ActionType::Attack;
    barbarian.currentAction = ActionType::Attack;

    barbarian.extraAttacks = 0;

    barbarian.hasAdvantage = false;
    barbarian.hasDisadvantage = false;

    barbarian.favoredEnemy = false;
    barbarian.wildShapeActive = false;

    barbarian.sneakAttackReady = false;

    barbarian.cursed = false;
    barbarian.curseDamageDiceNumber = 0;
    barbarian.curseDamageDiceSides = 0;

    barbarian.wildShapeForm = WildShapeForm::None;

    barbarian.isCaster = false;
    barbarian.canHeal = false;
    barbarian.canUseCantrips = false;

    barbarian.wins = 0;
    barbarian.losses = 0;
    
    barbarian.alive = true;

    return barbarian;
}

// Function to create a Wizard character
Character createBard()
{
    Character bard{};

    bard.name = "Bard";
    bard.classType = ClassType::Bard;

    bard.str = -1;
    bard.dex = 2;
    bard.con = 1;
    bard.intel = 0;
    bard.wis = 1;
    bard.cha = 3;

    bard.strSave = -1;
    bard.dexSave = 4;
    bard.conSave = 1;
    bard.intSave = 0;
    bard.wisSave = 1;
    bard.chaSave = 5;

    bard.hp = 27;
    bard.maxHp = 27;

    bard.ac = 13;

    bard.attackBonus = 0;

    bard.spellDc = 13;
    
    bard.magicType = MagicType::SavingThrow;
    bard.spellSaveType = SaveType::Intelligence;

    bard.cantripType = MagicType::AttackRoll;
    bard.cantripSaveType = SaveType::Wisdom;

    bard.magicUses = 3;
    bard.maxMagicUses = 3;

    bard.magicDiceNumber = 3;
    bard.magicDiceSides = 6;
    bard.magicModifier = 0;

    bard.cantripDiceNumber = 1;
    bard.cantripDiceSides = 6;
    bard.cantripModifier = 0;

    bard.healingUses = 3;
    bard.maxHealingUses = 3;

    bard.healingDiceNumber = 2;
    bard.healingDiceSides = 4;
    bard.healingModifier = 3;

    bard.specialUses = 3;
    bard.maxSpecialUses = 3;

    bard.bardicInspirationActive = false;
    bard.bardicInspirationRounds = 0;

    bard.isCaster = true;
    bard.canHeal = true;
    bard.canUseCantrips = true;

    bard.preferredAction = ActionType::Magic;
    bard.currentAction = ActionType::Magic;

    bard.damageReduction = 0;

    bard.extraAttacks = 0;

    bard.hasAdvantage = false;
    bard.hasDisadvantage = false;

    bard.raging = false;
    bard.favoredEnemy = false;

    bard.sneakAttackReady = false;

    bard.cursed = false;

    bard.wildShapeForm = WildShapeForm::None;

    bard.bonusAc = 0;
    bard.bonusAcRounds = 0;

    bard.wins = 0;
    bard.losses = 0;

    bard.alive = true;

    return bard;
}

Character createCleric()
{
    Character cleric{};

    cleric.name = "Cleric";
    cleric.classType = ClassType::Cleric;

    cleric.str = 1;
    cleric.dex = -1;
    cleric.con = 2;
    cleric.intel = 0;
    cleric.wis = 3;
    cleric.cha = 1;

    cleric.strSave = 1;
    cleric.dexSave = -1;
    cleric.conSave = 2;
    cleric.intSave = 0;
    cleric.wisSave = 5;
    cleric.chaSave = 3;

    cleric.hp = 30;
    cleric.maxHp = 30;

    cleric.ac = 14;

    cleric.attackBonus = 3;

    cleric.damageDiceNumber = 1;
    cleric.damageDiceSides = 6;
    cleric.damageModifier = 1;

    cleric.spellDc = 13;
    
    cleric.magicType = MagicType::SavingThrow;
    cleric.spellSaveType = SaveType::Constitution;

    cleric.magicUses = 2;
    cleric.maxMagicUses = 2;

    cleric.magicDiceNumber = 2;
    cleric.magicDiceSides = 10;
    cleric.magicModifier = 0;

    cleric.healingUses = 2;
    cleric.maxHealingUses = 2;

    cleric.healingDiceNumber = 2;
    cleric.healingDiceSides = 8;
    cleric.healingModifier = 3;

    cleric.specialUses = 2;
    cleric.maxSpecialUses = 2;

    cleric.isCaster = true;
    cleric.canHeal = true;

    cleric.shieldEquipped = true;

    cleric.preferredAction = ActionType::Magic;
    cleric.currentAction = ActionType::Magic;

    cleric.damageReduction = 0;

    cleric.extraAttacks = 0;

    cleric.hasAdvantage = false;
    cleric.hasDisadvantage = false;

    cleric.raging = false;
    cleric.favoredEnemy = false;

    cleric.sneakAttackReady = false;

    cleric.cursed = false;

    cleric.wildShapeForm = WildShapeForm::None;

    cleric.bonusAc = 0;
    cleric.bonusAcRounds = 0;

    cleric.wins = 0;
    cleric.losses = 0;

    cleric.alive = true;

    return cleric;
}

Character createDruid()
{
    Character druid{};

    druid.name = "Druid";
    druid.classType = ClassType::Druid;

    druid.str = 0;
    druid.dex = 2;
    druid.con = 1;
    druid.intel = 2;
    druid.wis = 3;
    druid.cha = -1;

    druid.strSave = 0;
    druid.dexSave = 2;
    druid.conSave = 1;
    druid.intSave = 4;
    druid.wisSave = 5;
    druid.chaSave = -1;

    druid.hp = 27;
    druid.maxHp = 27;

    druid.tempHp = 0;

    druid.ac = 15;

    druid.spellDc = 13;
    
    druid.magicType = MagicType::SavingThrow;
    druid.spellSaveType = SaveType::Strength;
    druid.magicType = MagicType::AttackRoll;
    druid.spellSaveType = SaveType::Dexterity;

    druid.cantripType = MagicType::AttackRoll;

    druid.magicUses = 2;
    druid.maxMagicUses = 2;

    druid.magicDiceNumber = 2;
    druid.magicDiceSides = 6;
    druid.magicModifier = 0;

    druid.cantripDiceNumber = 1;
    druid.cantripDiceSides = 10;
    druid.cantripModifier = 0;

    druid.healingUses = 2;
    druid.maxHealingUses = 2;

    druid.healingDiceNumber = 2;
    druid.healingDiceSides = 4;
    druid.healingModifier = 3;

    druid.specialUses = 2;
    druid.maxSpecialUses = 2;

    druid.isCaster = true;
    druid.canHeal = true;
    druid.canUseCantrips = true;

    druid.shieldEquipped = true;

    druid.preferredAction = ActionType::Magic;
    druid.currentAction = ActionType::Magic;

    druid.damageReduction = 0;

    druid.extraAttacks = 0;

    druid.hasAdvantage = false;
    druid.hasDisadvantage = false;

    druid.raging = false;
    druid.favoredEnemy = false;

    druid.sneakAttackReady = false;

    druid.cursed = false;

    druid.wildShapeActive = false;
    druid.wildShapeForm = WildShapeForm::None;

    druid.bonusAc = 0;
    druid.bonusAcRounds = 0;

    druid.wins = 0;
    druid.losses = 0;

    druid.alive = true;

    return druid;
}

Character createFighter()
{
    Character fighter{};

    fighter.name = "Fighter";
    fighter.classType = ClassType::Fighter;

    fighter.str = 3;
    fighter.dex = 1;
    fighter.con = 2;
    fighter.intel = -1;
    fighter.wis = 1;
    fighter.cha = 0;

    fighter.strSave = 5;
    fighter.dexSave = 1;
    fighter.conSave = 4;
    fighter.intSave = -1;
    fighter.wisSave = 1;
    fighter.chaSave = 0;

    fighter.hp = 36;
    fighter.maxHp = 36;

    fighter.ac = 18;

    fighter.attackBonus = 5;

    fighter.damageDiceNumber = 1;
    fighter.damageDiceSides = 8;
    fighter.damageModifier = 3;

    fighter.specialUses = 2;
    fighter.maxSpecialUses = 2;

    fighter.actionSurgeActive = false;

    fighter.healingUses = 2;
    fighter.maxHealingUses = 2;

    fighter.alive = true;
    fighter.shieldEquipped = true;

    fighter.preferredAction = ActionType::Attack;
    fighter.currentAction = ActionType::Attack;

    fighter.damageReduction = 0;

    fighter.extraAttacks = 0;

    fighter.hasAdvantage = false;
    fighter.hasDisadvantage = false;

    fighter.raging = false;
    fighter.favoredEnemy = false;

    fighter.sneakAttackReady = false;

    fighter.cursed = false;

    fighter.wildShapeForm = WildShapeForm::None;

    fighter.isCaster = false;
    fighter.canHeal = true;
    fighter.canUseCantrips = false;

    fighter.wins = 0;
    fighter.losses = 0;

    return fighter;
}

Character createMonk()
{
    Character monk{};

    monk.name = "Monk";
    monk.classType = ClassType::Monk;

    monk.str = 1;
    monk.dex = 3;
    monk.con = 1;
    monk.intel = 0;
    monk.wis = 2;
    monk.cha = -1;

    monk.strSave = 3;
    monk.dexSave = 5;
    monk.conSave = 1;
    monk.intSave = 0;
    monk.wisSave = 2;
    monk.chaSave = -1;

    monk.hp = 27;
    monk.maxHp = 27;

    monk.ac = 15;

    monk.attackBonus = 5;

    monk.damageDiceNumber = 2;
    monk.damageDiceSides = 6;
    monk.damageModifier = 3;

    monk.specialUses = 3;
    monk.maxSpecialUses = 3;

    monk.flurryReady = false;

    monk.preferredAction = ActionType::Attack;
    monk.currentAction = ActionType::Attack;

    monk.damageReduction = 0;

    monk.extraAttacks = 0;

    monk.hasAdvantage = false;
    monk.hasDisadvantage = false;

    monk.raging = false;
    monk.favoredEnemy = false;

    monk.sneakAttackReady = false;

    monk.cursed = false;

    monk.wildShapeForm = WildShapeForm::None;

    monk.isCaster = false;

    monk.wins = 0;
    monk.losses = 0;

    monk.alive = true;

    return monk;
}

Character createPaladin()
{
    Character paladin{};

    paladin.name = "Paladin";
    paladin.classType = ClassType::Paladin;

    paladin.str = 3;
    paladin.dex = -1;
    paladin.con = 1;
    paladin.intel = 0;
    paladin.wis = 1;
    paladin.cha = 2;

    paladin.strSave = 3;
    paladin.dexSave = -1;
    paladin.conSave = 1;
    paladin.intSave = 0;
    paladin.wisSave = 3;
    paladin.chaSave = 4;

    paladin.hp = 33;
    paladin.maxHp = 33;

    paladin.ac = 18;

    paladin.attackBonus = 5;

    paladin.damageDiceNumber = 1;
    paladin.damageDiceSides = 8;
    paladin.damageModifier = 3;

    paladin.spellDc = 12;

    paladin.magicType = MagicType::AttackRoll;

    paladin.magicUses = 2;
    paladin.maxMagicUses = 2;

    paladin.magicDiceNumber = 3;
    paladin.magicDiceSides = 8;
    paladin.magicModifier = 3;

    paladin.healingUses = 1;
    paladin.maxHealingUses = 1;

    paladin.specialUses = 1;
    paladin.maxSpecialUses = 1;

    paladin.canHeal = true;

    paladin.shieldEquipped = true;

    paladin.preferredAction = ActionType::Attack;
    paladin.currentAction = ActionType::Attack;

    paladin.damageReduction = 0;

    paladin.extraAttacks = 0;

    paladin.hasAdvantage = false;
    paladin.hasDisadvantage = false;

    paladin.raging = false;
    paladin.favoredEnemy = false;

    paladin.sneakAttackReady = false;

    paladin.cursed = false;

    paladin.wildShapeForm = WildShapeForm::None;

    paladin.bonusAc = 0;
    paladin.bonusAcRounds = 0;

    paladin.wins = 0;
    paladin.losses = 0; 

    paladin.alive = true;

    return paladin;
}

Character createRanger()
{
    Character ranger{};

    ranger.name = "Ranger";
    ranger.classType = ClassType::Ranger;

    ranger.str = 1;
    ranger.dex = 3;
    ranger.con = 1;
    ranger.intel = 0;
    ranger.wis = 2;
    ranger.cha = -1;

    ranger.strSave = 3;
    ranger.dexSave = 5;
    ranger.conSave = 1;
    ranger.intSave = 0;
    ranger.wisSave = 2;
    ranger.chaSave = -1;

    ranger.hp = 33;
    ranger.maxHp = 33;

    ranger.ac = 15;

    ranger.attackBonus = 5;

    ranger.damageDiceNumber = 1;
    ranger.damageDiceSides = 8;
    ranger.damageModifier = 3;

    ranger.spellDc = 12;

    ranger.magicType = MagicType::AttackRoll;

    ranger.magicUses = 2;
    ranger.maxMagicUses = 2;

    ranger.magicDiceNumber = 2;
    ranger.magicDiceSides = 8;
    ranger.magicModifier = 3;

    ranger.healingUses = 2;
    ranger.maxHealingUses = 2;

    ranger.healingDiceNumber = 2;
    ranger.healingDiceSides = 8;
    ranger.healingModifier = 2;

    ranger.specialUses = 2;
    ranger.maxSpecialUses = 2;

    ranger.canHeal = true;

    ranger.preferredAction = ActionType::Attack;
    ranger.currentAction = ActionType::Attack;

    ranger.damageReduction = 0;

    ranger.extraAttacks = 0;

    ranger.hasAdvantage = false;
    ranger.hasDisadvantage = false;

    ranger.favoredEnemy = false;
    ranger.favoredEnemyRounds = 0;

    ranger.sneakAttackReady = false;

    ranger.cursed = false;

    ranger.wildShapeForm = WildShapeForm::None;

    ranger.wins = 0;
    ranger.losses = 0;

    ranger.alive = true;

    return ranger;
}

Character createRogue()
{
    Character rogue{};

    rogue.name = "Rogue";
    rogue.classType = ClassType::Rogue;

    rogue.str = -1;
    rogue.dex = 3;
    rogue.con = 1;
    rogue.intel = 2;
    rogue.wis = 1;
    rogue.cha = 0;

    rogue.strSave = -1;
    rogue.dexSave = 5;
    rogue.conSave = 1;
    rogue.intSave = 4;
    rogue.wisSave = 1;
    rogue.chaSave = 0;

    rogue.hp = 27;
    rogue.maxHp = 27;

    rogue.ac = 14;

    rogue.attackBonus = 7;

    rogue.damageDiceNumber = 2;
    rogue.damageDiceSides = 4;
    rogue.damageModifier = 3;

    rogue.extraDamageDiceNumber = 2;
    rogue.extraDamageDiceSides = 6;

    rogue.specialUses = 3;
    rogue.maxSpecialUses = 3;

    rogue.preferredAction = ActionType::Attack;
    rogue.currentAction = ActionType::Attack;

    rogue.damageReduction = 0;

    rogue.extraAttacks = 0;

    rogue.hasAdvantage = false;
    rogue.hasDisadvantage = false;

    rogue.raging = false;
    rogue.favoredEnemy = false;

    rogue.sneakAttackReady = true;
    rogue.sneakAttackRounds = 0;

    rogue.cursed = false;

    rogue.wildShapeForm = WildShapeForm::None;

    rogue.wins = 0;
    rogue.losses = 0;

    rogue.alive = true;

    return rogue;
}

Character createSorcerer()
{
    Character sorcerer{};

    sorcerer.name = "Sorcerer";
    sorcerer.classType = ClassType::Sorcerer;

    sorcerer.str = -1;
    sorcerer.dex = 2;
    sorcerer.con = 1;
    sorcerer.intel = 1;
    sorcerer.wis = 0;
    sorcerer.cha = 3;

    sorcerer.strSave = -1;
    sorcerer.dexSave = 2;
    sorcerer.conSave = 3;
    sorcerer.intSave = 1;
    sorcerer.wisSave = 0;
    sorcerer.chaSave = 5;

    sorcerer.hp = 21;
    sorcerer.maxHp = 21;

    sorcerer.ac = 12;

    sorcerer.spellDc = 14;

    sorcerer.magicType = MagicType::AttackRoll;
    sorcerer.magicType = MagicType::SavingThrow;
    sorcerer.spellSaveType = SaveType::Dexterity;

    sorcerer.cantripType = MagicType::AttackRoll;

    sorcerer.magicUses = 3;
    sorcerer.maxMagicUses = 3;

    sorcerer.magicDiceNumber = 2;
    sorcerer.magicDiceSides = 8;
    sorcerer.magicModifier = 0;

    sorcerer.cantripDiceNumber = 1;
    sorcerer.cantripDiceSides = 10;
    sorcerer.cantripModifier = 0;

    sorcerer.specialUses = 2;
    sorcerer.maxSpecialUses = 2;

    sorcerer.empoweredSpellRounds = 0;

    sorcerer.hasAdvantage = true;

    sorcerer.isCaster = true;
    sorcerer.canUseCantrips = true;

    sorcerer.preferredAction = ActionType::Magic;
    sorcerer.currentAction = ActionType::Magic;

    sorcerer.damageReduction = 0;

    sorcerer.extraAttacks = 0;

    sorcerer.hasAdvantage = true;
    sorcerer.hasDisadvantage = false;

    sorcerer.raging = false;
    sorcerer.favoredEnemy = false;

    sorcerer.sneakAttackReady = false;

    sorcerer.cursed = false;

    sorcerer.wildShapeForm = WildShapeForm::None;

    sorcerer.wins = 0;
    sorcerer.losses = 0;

    sorcerer.alive = true;

    return sorcerer;
}

Character createWarlock()
{
    Character warlock{};

    warlock.name = "Warlock";
    warlock.classType = ClassType::Warlock;

    warlock.str = 0;
    warlock.dex = 2;
    warlock.con = 1;
    warlock.intel = 1;
    warlock.wis = -1;
    warlock.cha = 3;

    warlock.strSave = 0;
    warlock.dexSave = 2;
    warlock.conSave = 1;
    warlock.intSave = 1;
    warlock.wisSave = 1;
    warlock.chaSave = 5;

    warlock.hp = 27;
    warlock.maxHp = 27;

    warlock.ac = 15;

    warlock.spellDc = 14;
    
    warlock.magicType = MagicType::AttackRoll;
    warlock.cantripType = MagicType::AttackRoll;

    warlock.magicUses = 2;
    warlock.maxMagicUses = 2;

    warlock.curseRounds = 0; 

    warlock.magicDiceNumber = 2;
    warlock.magicDiceSides = 12;
    warlock.magicModifier = 0;

    warlock.cantripDiceNumber = 1;
    warlock.cantripDiceSides = 10;
    warlock.cantripModifier = 3;

    warlock.specialUses = 1;
    warlock.maxSpecialUses = 1;

    warlock.isCaster = true;
    warlock.canUseCantrips = true;

    warlock.preferredAction = ActionType::Cantrip;
    warlock.currentAction = ActionType::Cantrip;

    warlock.damageReduction = 0;

    warlock.extraAttacks = 0;

    warlock.hasAdvantage = false;
    warlock.hasDisadvantage = false;

    warlock.raging = false;
    warlock.favoredEnemy = false;

    warlock.sneakAttackReady = false;

    warlock.cursed = false;
    warlock.curseDamageDiceNumber = 1;
    warlock.curseDamageDiceSides = 6;

    warlock.wildShapeForm = WildShapeForm::None;

    warlock.wins = 0;
    warlock.losses = 0;

    warlock.alive = true;

    return warlock;
}

Character createWizard()
{
    Character wizard{};

    wizard.name = "Wizard";
    wizard.classType = ClassType::Wizard;

    wizard.str = -1;
    wizard.dex = 1;
    wizard.con = 2;
    wizard.intel = 3;
    wizard.wis = 0;
    wizard.cha = 1;

    wizard.strSave = -1;
    wizard.dexSave = 1;
    wizard.conSave = 2;
    wizard.intSave = 5;
    wizard.wisSave = 2;
    wizard.chaSave = 1;

    wizard.hp = 24;
    wizard.maxHp = 24;

    wizard.ac = 11;

    wizard.spellDc = 14;
    
    wizard.magicType = MagicType::SavingThrow;
    wizard.magicType = MagicType::AttackRoll;
    wizard.spellSaveType = SaveType::Charisma;

    wizard.cantripType = MagicType::AttackRoll;

    wizard.magicUses = 3;
    wizard.maxMagicUses = 3;

    wizard.magicDiceNumber = 3;
    wizard.magicDiceSides = 4;
    wizard.magicModifier = 3;

    wizard.cantripDiceNumber = 1;
    wizard.cantripDiceSides = 10;
    wizard.cantripModifier = 0;

    wizard.specialUses = 1;
    wizard.maxSpecialUses = 1;

    wizard.isCaster = true;
    wizard.canUseCantrips = true;

    wizard.preferredAction = ActionType::Magic;
    wizard.currentAction = ActionType::Magic;

    wizard.damageReduction = 0;

    wizard.extraAttacks = 0;

    wizard.hasAdvantage = false;
    wizard.hasDisadvantage = false;

    wizard.raging = false;
    wizard.favoredEnemy = false;

    wizard.sneakAttackReady = false;

    wizard.cursed = false;

    wizard.wildShapeForm = WildShapeForm::None;

    wizard.bonusAc = 0;
    wizard.bonusAcRounds = 0;

    wizard.wins = 0;
    wizard.losses = 0;

    wizard.alive = true;

    return wizard;
}
