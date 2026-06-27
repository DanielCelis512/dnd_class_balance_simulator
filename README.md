D&D Class Balance Simulator
Overview

D&D Class Balance Simulator is a game analytics and data science project designed to evaluate class balance across the twelve core Dungeons & Dragons classes using Monte Carlo simulations.

The project combines:

C++ Gameplay Simulation
Data Analysis with Python
SQL Data Storage
Interactive Dashboards with Streamlit
Statistical Evaluation of Game Balance

The simulator recreates thousands of automated battles between level 1 characters and analyzes the results to identify balance patterns, class strengths, and potential design issues.

Project Goals

The purpose of this project is to answer questions such as:

Which class has the highest win rate?
How important are armor and survivability?
Are spellcasters balanced against martial classes?
Which abilities contribute most to victory?
How impactful are healing abilities?
What balance changes could improve fairness?
Features
Combat Engine
Turn-based combat system
Initiative rolls
Armor Class calculations
Critical hits and critical failures
Weapons and spell attacks
Healing mechanics
Special class abilities
AI-driven combat decisions
Classes Included
Barbarian
Bard
Cleric
Druid
Fighter
Monk
Paladin
Ranger
Rogue
Sorcerer
Warlock
Wizard
Class Mechanics

Examples:

Barbarian Rage
Rogue Sneak Attack
Paladin Divine Smite
Bard Healing and Inspiration
Cleric Healing
Druid Wild Shape
Ranger Hunter's Mark
Wizard Magic Missile
Sorcerer Empowered Spell
Warlock Eldritch Blast
Technologies
C++

Used to build the combat engine and simulation framework.

Python

Used for:

Data cleaning
Statistical analysis
Visualization
Balance evaluation

Libraries:

Pandas
NumPy
Matplotlib
Seaborn
SciPy
SQL

Used to store battle results and run analytical queries.

Streamlit

Used to create an interactive dashboard for exploring combat data.

Project Structure
dnd-class-balance-simulator/

├── cpp_engine/
│   ├── Character.h
│   ├── Battle.cpp
│   ├── Dice.cpp
│   ├── Simulation.cpp
│
├── data/
│   ├── battles.csv
│   ├── battles.db
│
├── analysis/
│   ├── analysis.ipynb
│
├── dashboard/
│   ├── app.py
│
├── docs/
│   ├── combat_rules.md
│
├── README.md
│
└── requirements.txt
Combat System
Hit Points

To reduce randomness and create longer, more meaningful encounters:

HP = 3 × (Base HP + Constitution Modifier)
Initiative
1d20 + Dexterity Modifier
Attack Roll
1d20 + Offensive Modifier
Critical Hits
Natural 20
Automatic hit
Double damage dice
Critical Failures
Natural 1
Automatic miss
Simulation Process

Each battle follows these steps:

Generate two characters.
Roll initiative.
Determine actions using class-specific AI.
Resolve attacks, spells, healing and special abilities.
Continue until one character reaches 0 HP.
Store battle data.
Repeat thousands of times.
Data Collected

Each simulation records:

battle_id
class1
class2
winner
rounds

damage_dealt
damage_taken

healing_done

critical_hits

spells_used

special_abilities_used
Analytics

The project calculates:

Win Rate

Percentage of victories per class.

Average Damage

Average damage dealt per battle.

Survivability

Relationship between HP, AC and victory rate.

Ability Efficiency

Impact of special abilities on combat outcomes.

Matchup Analysis

Performance of each class against every other class.

Future Features
Multi-class characters
Level progression
Equipment system
Advanced spellcasting
Party-based combat
Reinforcement Learning AI
Automated balance recommendations
ELO rating system
Example Research Questions
Does higher Armor Class correlate with higher win rates?
How valuable is healing compared to damage?
Which class scales best with survivability?
Are spellcasters underpowered or overpowered?
Which abilities provide the greatest competitive advantage?
Author

José Daniel Celis Lozano

Data Science Student | Game Analytics Enthusiast | Aspiring Data Scientist

GitHub:

DanielCelis512 GitHub

License

This project is intended for educational, analytical, and portfolio purposes. It is not affiliated with Wizards of the Coast or Dungeons & Dragons.
