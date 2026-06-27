# Abilities
All classes have six abilities that measures physical and mental characteristics.
Strength/Str: Physical Might.
Dexterity/Dex: Agility, Reflexes and Balance.
Constitution/Con: Health and Stamina.
Intelligence/Int: Reasoning and Memory.
Wisdom/Wis: Perceptiveness and Mental Fortitude.
Charisma/Cha: Confidence, Pride and Charm.

# Ability Scores
The scores represent the magnitude of an ability.
2-9 | Represents a weak capability.
10-11 | Represents the human average.
12-19 | Represents a strong capability.

# Modifiers
Each ability has a modifier that will be applied to the d20 tests, they are derived from its score, the fuction for it is (stat - 10) / 2. For the purposes of simplificating the simulations, the modifiers that will be used will be the ones bellow.
8 | -1
10 | +0
12-13 | +1
14-15 | +2
16 | +3

# Combat
The game organizes combat into a cycle of rounds and turns, in the case of the simulation the combat will have three parts: Roll for Initiative to see who goes first, the Turns in wich each class will take an Action, most classes will have multiple Ofensive and Support Actions that they can use, and Rounds one round will be the turns of both classes.

# HP
Even though the level of the classes will be set to 2, the health of the classes will have three times the amount at level 1, the simulations will have more options for each battle with more broad results, the health is set by the fuction HP = 3 × (Base HP + Con).

# Advantage and Disadvantage
Used to represent favorable or hindering circumstances. With advantage, the class will roll 2d20 and take the highest number; with disadvantage, you roll 2d20 and take the lowest.

# Initiative
Determines the order of turns within the combats, the classes will roll for Initiative. It is set with 1d20 + Dex

# Attack Action
Is the action used for ofensive damage for some classes, for the simulations most of the attacks of the classes will be made with 1d20 + ofensive ablity.

# Difficulty Class - DC
It is the target number the class needs to roll equal to or higher than on a d20 to succeed at an ability check or a saving throw.

# Magic Action
Is the action used for ofensive damage for some classes, for the simulations some magic will need a Sving throw against the DC of the class, if the roll is equal or higher than the DC will take half of the damage, if it is lower the class will receive the full damage of the attack and the extra effects of the magic used.

# Critical Hits
When a critical hit is made, roll the attack’s damage dice twice, and with a critical failure the attack automatically misses, when a critical failure is made when making a saving throw the damage the class receives will be rolled twice, and when a critial hit is made when making a saving throw the damage will be nullified. When disadvange is
Critial Hit: Natural 20
Critical Miss: Natural 1

# Armor Class - AC
It represents how hard it is to hit the class; an attacker must roll equal to or higher than the AC to successfully land a hit.

# Shield
When using a shield the class will benefit with a +2 to the AC, but will not be able to do Magic or to do more damage with some weapons, the class can choose to equip or to unequip the shield but that will be the turn made. So usually the class will stay with the composition wich it has started with, so either it begins with shield or it begins without shield, but with the shield the classes will be able to use cantrips.

# Extra Abilities
A class broadly describes a character’s vocation, special talents, and favored tactics. To be able to show the uniqueness of each class, each of them will have extra abilities that will play into their unique kit, doing it with precision so that it is fair.

# Instant Actions
This actions can be made at any time if the conditions for it are available.

# Temporary HP
They function exactly like an extra health bar, absorbing damage first, when a class gains Temporary HP, an extra HP will be added and will receive the damage instead of the class HP, all the additional damage that takes the Temporary HP to 0, the HP of the class will receive it.

# Classes

## Barbarian
Scores. Str = 16, Dex = 13, Con = 14, Int = 8, Wis = 12, Cha = 10
Modifiers. Str = +3, Dex = +1, Con = +2, Int = -1, Wis = +1, Cha = +0
HP = 3 × (12 HP + Con) = 42
AC = 10 + Dex + Con = 13
Atack Roll = 1d20 + Str + 2 
Weapon Damage = 1d12 + Str
Special Ability | Rage: Uses = 2, Effects - +2 damage, 50% damage reduction and all attacks will be made with advantage, Instant, Duration next 2 Rounds.

## Bard
Scores. Str = 8, Dex = 14, Con = 12, Int = 10, Wis = 13, Cha = 16
Modifiers. Str = -1, Dex = +2, Con = +1, Int = +0, Wis = +1, Cha = +3
HP = 3 × (8 HP + Con) = 27
AC = 11 + Dex = 13
Magic Action = Target must succeed a Int saving throw against the DC or take damage
Magic Damage = 3d6
Magic Healing = 2d4 + Cha
Magic Uses = 3
Cantrip Action = Target must succeed a Wis saving throw against the DC or take damage and have Disadvantage on the next attack.
Cantrip Damage = 1d6 
DC = 8 + Cha + 2 = 13
Special Ability | Bardic Inspiration: Uses = Cha, Effects - Can reduce the d20 rolls of the enemy or increase the rolls made by the class, Instant.

## Cleric

Scores. Str = 13, Dex = 8, Con = 14, Int = 10, Wis = 16, Cha = 12
Modifiers. Str = +1, Dex = -1, Con = +2, Int = +0, Wis = +3, Cha = +1
HP = 3 × (8 HP + Con) = 30
AC = 13 + Dex = 12 | CA + Shield = 14
Atack Roll = 1d20 + Str + 2 
Weapon Damage = 1d6 + Str
Magic Action = Target must succeed a Con saving throw or take damage
Magic Damage = 2d10
Magic Healing = 2d8 + Wis
Magic Uses = 2
DC = 8 + Wis + 2 = 13
Special Ability | Divine Spark: Uses = 2, Effects - Can either heal the class for 1d8 or Target must succeed a Con saving throw or take 1d8 damage, Magic Action.

## Druid

Scores. Str = 10, Dex = 14, Con = 12, Int = 13, Wis = 16, Cha = 8
Modifiers. Str = +0, Dex = +2, Con = +1, Int = +2, Wis = +3, Cha = -1
HP = 3 × (8 HP + Con) = 27
AC = 11 + Dex = 13 | AC + Shield = 15
Magic Action = 1d20 + Wis + 2, Hit or Miss, Target must succeed a Dex saving throw or take damage
Magic Damage = 1d10, + 2d6
Magic Healing = 2d4 + Wis
Magic Uses = 2
Cantrip Action = 1d20 + Wis + 2
Cantrip Damage = 1d10 
DC = 8 + Wis + 2 = 13
Special Ability | Wild Shape: Uses = 2, Effects - The class shape-shifts into a Beast form, when in the new form will receive new stats and cannot use magic or anything different from the stats received, when the Temporary HP gets to 0 will return to the original form, with two options for the wild shape:
Wolf | Gain 2d10 + 2 Temporary HP | Scores. Str = 14, Dex = 15, Con = 12, Int = 3, Wis = 12, Cha = 6 | Modifiers. Str = +2, Dex = +2, Con = +1, Int = -4, Wis = +1, Cha = -2 | Atack Roll = 1d20 + Str + 2 | Damage = 1d6 + Str | AC = 12
Constrictor Snake | Gain 2d8 + 2 Temporary HP | Scores. Str = 15, Dex = 14, Con = 12, Int = 1, Wis = 10, Cha = 3 | Modifiers. Str = +2, Dex = +2, Con = +1, Int = -5, Wis = +0, Cha = -4 | Atack Action = Target must succeed a Str saving throw or take damage | Damage = 3d4 | DC = 12 | AC = 13

## Fighter
Scores. Str = 16, Dex = 13, Con = 14, Int = 12, Wis = 8, Cha = 10
Modifiers. Str = +3, Dex = +1, Con = +2, Int = -1, Wis = +1, Cha = +0
HP = 3 × (10 HP + Con) = 36
AC = 16 | AC + Shield = 18
Atack Roll = 1d20 + Str + 2 
Weapon Damage = 1d10 + Str
Weapon Damage Shield = 1d8 + Str
Special Ability | Action Surge: Uses = 2, Effects - Do an extra attack, Instant. | Second Wind: Uses = 2, Effects - Regain HP equal to 1d10 + 3

## Monk
Scores. Str = 12, Dex = 16, Con = 13, Int = 10, Wis = 14, Cha = 8
Modifiers. Str = +1, Dex = +3, Con = +1, Int = +0, Wis = +2, Cha = -1
HP = 3 × (8 HP + Con) = 27
AC = 10 + Dex + Wis = 15
Atack Roll = 1d20 + Dex + 2 
Weapon Damage = 1d6 + Dex + 1d6 + Dex
Special Ability | Flurry of Blows: Uses = 3, Effects - Do two extra attacks (1d6 + Dex + 1d6 + Dex), Instant.

## Paladin
Scores. Str = 16, Dex = 8, Con = 13, Int = 10, Wis = 12, Cha = 14
Modifiers. Str = +3, Dex = -1, Con = +1, Int = +0, Wis = +1, Cha = +2
HP = 3 × (10 HP + Con) = 33
AC = 16 | AC + Shield = 18
Atack Roll = 1d20 + Str + 2 
Weapon Damage = 1d10 + Str
Weapon Damage Shield = 1d8 + Str
Magic Action = 1d20 + Str + 2
Magic Damage = 3d8 + Str
Magic AC = +2 AC, Duration 3 rounds
Magic Uses = 2
DC = 8 + Cha + 2 = 12
Special Ability | Lay On Hands: Uses = 1, Effects - Heal 10 HP, Action. 

## Ranger
Scores. Str = 13, Dex = 16, Con = 12, Int = 10, Wis = 14, Cha = 8
Modifiers. Str = +1, Dex = +3, Con = +1, Int = +0, Wis = +2, Cha = -1
HP = 3 × (10 HP + Con) = 33
AC = 12 + Dex = 15
Atack Roll = 1d20 + Dex + 2 
Weapon Damage = 1d8 + Dex
Magic Action = 1d20 + Dex + 2
Magic Damage = 2d8 + Dex
Magic healing = 2d8 + Wis
Magic Uses = 2
DC = 8 + Cha + 2 = 12
Special Ability | Favored Enemy: Uses = 2, Effects - Deal an extra 1d6 damage when an attack hits and all attacks will be made with advantage, Instant, Duration 3 rounds.

## Rogue
Scores. Str = 8, Dex = 16, Con = 12, Int = 14, Wis = 13, Cha = 10
Modifiers. Str = -1, Dex = +3, Con = +1, Int = +2, Wis = +1, Cha = +0
HP = 3 × (8 HP + Con) = 27
AC = 11 + Dex = 14
Atack Roll = 1d20 + Dex + 4 
Weapon Damage = 2d4 + Dex + 1d6 + Dex
Special Ability | Sneak Attack: Uses = 3, Effects - Deal an extra 2d6 when an attack hits, Instant. | Expertise: Effects - Saving Throws and attacks will have an extra +2

## Sorcerer
Scores. Str = 8, Dex = 14, Con = 12, Int = 13, Wis = 10, Cha = 16
Modifiers. Str = -1, Dex = +2, Con = +1, Int = +1, Wis = +0 Cha = +3
HP = 3 × (6 HP + Con) = 21
AC = 10 + Dex = 12
Magic Action = 1d20 + Cha + 2 (Once)
Magic Damage = 3d8
Magic Action = 1d20 + Cha + 2
Magic Damage = 2d8 + 1d6
Magic Action = 1d20 + Cha + 2, Hit or Miss, Target must succeed a Dex saving throw or take damage
Magic Damage = 1d10, + 2d6
Magic Uses = 3
Cantrip Action = 1d20 + Cha + 2
Cantrip Damage = 1d10 
DC = 8 + Cha + 3 = 14
Special Ability | Innate Sorcery: Effects - Advantage on the Magic Rolls done, Always | Empowered Spell: Uses 2, The damage rolls can be reroll for a better damage, Instant.

## Warlock
Scores. Str = 10, Dex = 14, Con = 13, Int = 12, Wis = 8, Cha = 16
Modifiers. Str = +0, Dex = +2, Con = +1, Int = +1, Wis = -1 Cha = +3
HP = 3 × (8 HP + Con) = 27
AC = 13 + Dex = 15
Magic Action = 1d20 + Cha + 2
Magic Damage = 2d12
Magic Action = Target will receive extra damage for each attack made
Magic Damage = 1d6
Magic Uses = 2
Cantrip Action = 1d20 + Cha + 2 
Cantrip Damage = 1d10 + Cha 
DC = 8 + Cha + 3 = 14
Special Ability | Armor of Shadows: Effects - Starts with a shadow armor that gets the base AC to 13. 

## Wizard
Scores. Str = 8, Dex = 13, Con = 14, Int = 16, Wis = 10, Cha = 12
Modifiers. Str = -1, Dex = +1, Con = +2, Int = +3, Wis = +0 Cha = +1
HP = 3 × (6 HP + Con) = 24
AC = 10 + Dex = 11
Magic Action = Impacts automatically
Magic Damage = 3d4 + 3
Magic Action = 1d20 + Int + 2 (Once)
Magic Damage = 3d8
Magic Action = Target must succeed a Cha saving throw or take damage
Magic Damage = 2d12
Magic Uses = 3
Cantrip Action = 1d20 + Cha 
Cantrip Damage = 1d10 
DC = 8 + Int + 3 = 14
Special Ability | Arcane Recovery: Uses = 1, Effects - Recover 2 Magic uses, Instant.
