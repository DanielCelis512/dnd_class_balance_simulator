#include "battle.h"
#include "actions.h"
#include "dice.h"
#include "turn_manager.h"

#include <iostream>

// Function to print the status of a character
void printStatus(const Character& character)
{
    std::cout
        << character.name
        << " HP: "
        << character.hp
        << "/"
        << character.maxHp
        << "\n";
}

// Function to conduct a battle between two characters
void battle(Character& character1,
            Character& character2)
{
    // Function to roll initiative for two characters
    int initiative1 =
    rollDice(1,20)
    + character1.dex;

    int initiative2 =
    rollDice(1,20)
    + character2.dex;

    // Pointers to track attack order
    Character* first;
    Character* second;

    // Determine the order of attack based on initiative rolls
    if(initiative1 >= initiative2)
    {
        first = &character1;
        second = &character2;
    }
    else
    {
        first = &character2;
        second = &character1;
    }

    // Print which character acts first
    std::cout
    << "\n"
    << first->name
    << " acts first!\n";

    // Print the initiative rolls for both characters
    std::cout
    << character1.name
    << " initiative: "
    << initiative1
    << "\n";

    std::cout
    << character2.name
    << " initiative: "
    << initiative2
    << "\n";

    // Start the battle loop
    std::cout
        << "\n===== BATTLE START =====\n";

    int round = 1;  

    // Continue the battle until one character is defeated
    while(first->alive && second->alive)
    {
    std::cout
        << "\nRound "
        << round
        << "\n";
    
    // Print the status of both characters at the start of the round
    std::cout
    << "\n--- Status ---\n";

    printStatus(*first);
    printStatus(*second);
    
    takeTurn(*first, *second);

    if(!second->alive)
    {
        break;
    }

    takeTurn(*second, *first);

    round++;
    }

    // Print the result of the battle
    std::cout
        << "\n===== BATTLE OVER =====\n";

    if(first->alive)
    {
    std::cout
        << first->name
        << " wins!\n";
    }
    else
    {
    std::cout
        << second->name
        << " wins!\n";
    }
}

