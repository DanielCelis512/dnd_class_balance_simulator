#include <cstdlib>
#include <ctime>
#include <iostream>

#include "battle.h"
#include "class_factory.h"
#include "simulation.h"

void showClasses()
{
    std::cout
        << "\nChoose a class:\n\n"
        << "1. Barbarian\n"
        << "2. Bard\n"
        << "3. Cleric\n"
        << "4. Druid\n"
        << "5. Fighter\n"
        << "6. Monk\n"
        << "7. Paladin\n"
        << "8. Ranger\n"
        << "9. Rogue\n"
        << "10. Sorcerer\n"
        << "11. Warlock\n"
        << "12. Wizard\n"
        << "\n> ";
}

ClassType chooseClass()
{
    int option;

    while(true)
    {
        showClasses();

        std::cin >> option;

        if(option >= 1 &&
           option <= 12)
        {
            return static_cast<ClassType>(option - 1);
        }

        std::cout
            << "\nInvalid option. Try again.\n";
    }
}

int main()
{
    std::srand(
        static_cast<unsigned>(
            std::time(nullptr)
        )
    );

    std::cout
        << "========== D&D Battle Simulator ==========\n";

    std::cout
        << "\nChoose Player 1";

    Character player1 =
        createCharacter(
            chooseClass()
        );

    std::cout
        << "\nChoose Player 2";

    Character player2 =
        createCharacter(
            chooseClass()
        );

    int mode;

    std::cout
        << "\nChoose simulation mode\n\n"
        << "1. Single Battle\n"
        << "2. 100 Battles\n"
        << "3. 1000 Battles\n"
        << "4. Custom\n"
        << "\n> ";

    std::cin >> mode;

    switch(mode)
    {
        case 1:
        {
            battle(
                player1,
                player2,
                true
            );

            break;
        }

        case 2:
        {
            simulateBattles(
                player1,
                player2,
                100,
                false
            );

            break;
        }

        case 3:
        {
            simulateBattles(
                player1,
                player2,
                1000,
                false
            );

            break;
        }

        case 4:
        {
            int battles;

            do
            {
                std::cout
                    << "\nNumber of battles (1-10): ";

                std::cin >> battles;

            } while(battles < 1 ||
                    battles > 10);

            char option;

            std::cout
                << "Show battle log? (y/n): ";

            std::cin >> option;

            bool showLog =
                option == 'y' ||
                option == 'Y';

            simulateBattles(
                player1,
                player2,
                battles,
                showLog
            );

            break;
        }

        default:
        {
            std::cout
                << "\nInvalid option.\n";

            break;
        }
    }

    return 0;
}