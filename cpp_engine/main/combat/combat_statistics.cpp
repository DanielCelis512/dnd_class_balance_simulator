#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <limits>

#include "battle.h"
#include "class_factory.h"
#include "simulation.h"

namespace
{

//==================================================
// Class Menu
//==================================================

void printClassMenu()
{
    std::cout
        << "\n=====================================\n"
        << "SELECT A CLASS\n"
        << "=====================================\n"
        << " 1. Barbarian\n"
        << " 2. Bard\n"
        << " 3. Cleric\n"
        << " 4. Druid\n"
        << " 5. Fighter\n"
        << " 6. Monk\n"
        << " 7. Paladin\n"
        << " 8. Ranger\n"
        << " 9. Rogue\n"
        << "10. Sorcerer\n"
        << "11. Warlock\n"
        << "12. Wizard\n"
        << "=====================================\n";
}

//==================================================
// Main Menu
//==================================================

void printMainMenu()
{
    std::cout
        << "\n=====================================\n"
        << "      D&D COMBAT SIMULATOR\n"
        << "=====================================\n"
        << "1. Individual Battle (1 vs 1)\n"
        << "2. Class Gauntlet (1 vs 11)\n"
        << "3. Tournament (Round Robin)\n"
        << "4. 100 Simulations\n"
        << "5. 1000 Simulations\n"
        << "0. Exit\n"
        << "=====================================\n"
        << "Option: ";
}

//==================================================
// Create Character
//==================================================

Character createCharacterFromChoice(
    int option
)
{
    switch(option)
    {
        case 1:
            return createBarbarian("Barbarian");

        case 2:
            return createBard("Bard");

        case 3:
            return createCleric("Cleric");

        case 4:
            return createDruid("Druid");

        case 5:
            return createFighter("Fighter");

        case 6:
            return createMonk("Monk");

        case 7:
            return createPaladin("Paladin");

        case 8:
            return createRanger("Ranger");

        case 9:
            return createRogue("Rogue");

        case 10:
            return createSorcerer("Sorcerer");

        case 11:
            return createWarlock("Warlock");

        case 12:
            return createWizard("Wizard");

        default:
            return createFighter("Fighter");
    }
}

//==================================================
// Choose Character
//==================================================

Character chooseCharacter()
{
    int option = 0;

    while(true)
    {
        printClassMenu();

        std::cout
            << "Choice: ";

        std::cin
            >> option;

        if(
            option >= 1 &&
            option <= 12
        )
        {
            return
                createCharacterFromChoice(
                    option
                );
        }

        std::cout
            << "\nInvalid option.\n";
    }
}

//==================================================
// Tournament List
//==================================================

std::vector<Character>
createTournamentCharacters()
{
    std::vector<Character> characters;

    characters.push_back(
        createBarbarian("Barbarian")
    );

    characters.push_back(
        createBard("Bard")
    );

    characters.push_back(
        createCleric("Cleric")
    );

    characters.push_back(
        createDruid("Druid")
    );

    characters.push_back(
        createFighter("Fighter")
    );

    characters.push_back(
        createMonk("Monk")
    );

    characters.push_back(
        createPaladin("Paladin")
    );

    characters.push_back(
        createRanger("Ranger")
    );

    characters.push_back(
        createRogue("Rogue")
    );

    characters.push_back(
        createSorcerer("Sorcerer")
    );

    characters.push_back(
        createWarlock("Warlock")
    );

    characters.push_back(
        createWizard("Wizard")
    );

    return characters;
}

}

namespace
{

//==================================================
// Individual Battle
//==================================================

void runSingleBattle()
{
    std::cout
        << "\nPLAYER 1\n";

    Character player1 =
        chooseCharacter();

    std::cout
        << "\nPLAYER 2\n";

    Character player2 =
        chooseCharacter();

    CombatStatistics player1Stats;
    CombatStatistics player2Stats;

    battle(
        player1,
        player2,
        player1Stats,
        player2Stats,
        true
    );
}

//==================================================
// Class Gauntlet
//==================================================

void runGauntlet()
{
    std::cout
        << "\nSELECT THE CHALLENGER\n";

    Character challenger =
        chooseCharacter();

    std::vector<Character> opponents =
        createTournamentCharacters();

    for(const Character& opponent : opponents)
    {
        if(
            opponent.identity.classType ==
            challenger.identity.classType
        )
        {
            continue;
        }

        Character player1 =
            challenger;

        Character player2 =
            opponent;

        CombatStatistics stats1;
        CombatStatistics stats2;

        std::cout
            << "\n=====================================\n";

        std::cout
            << player1.identity.name
            << " VS "
            << player2.identity.name
            << "\n";

        std::cout
            << "=====================================\n";

        battle(
            player1,
            player2,
            stats1,
            stats2,
            true
        );
    }
}

//==================================================
// Tournament
//==================================================

struct TournamentResult
{
    std::string name;

    int wins = 0;
    int losses = 0;
    int draws = 0;
};

void runTournament()
{
    std::vector<Character> contestants =
        createTournamentCharacters();

    //------------------------------------------
    // Random Order
    //------------------------------------------

    std::random_device rd;

    std::mt19937 rng(rd());

    std::shuffle(
        contestants.begin(),
        contestants.end(),
        rng
    );

    //------------------------------------------
    // Scoreboard
    //------------------------------------------

    std::vector<int> wins(
        contestants.size(),
        0
    );

    std::vector<int> losses(
        contestants.size(),
        0
    );

    std::vector<int> draws(
        contestants.size(),
        0
    );

    //------------------------------------------
    // Round Robin
    //------------------------------------------

    for(
        size_t i = 0;
        i < contestants.size();
        ++i
    )
    {
        for(
            size_t j = i + 1;
            j < contestants.size();
            ++j
        )
        {
            Character player1 =
                contestants[i];

            Character player2 =
                contestants[j];

            CombatStatistics stats1;
            CombatStatistics stats2;

            std::cout
                << "\n=====================================\n";

            std::cout
                << player1.identity.name
                << " VS "
                << player2.identity.name
                << "\n";

            std::cout
                << "=====================================\n";

            BattleResult result =
                battle(
                    player1,
                    player2,
                    stats1,
                    stats2,
                    true
                );

            switch(result)
            {
                case BattleResult::Player1Win:

                    wins[i]++;
                    losses[j]++;

                    break;

                case BattleResult::Player2Win:

                    wins[j]++;
                    losses[i]++;

                    break;

                case BattleResult::Draw:

                    draws[i]++;
                    draws[j]++;

                    break;
            }
        }
    }

    //------------------------------------------
    // Ranking
    //------------------------------------------

        std::vector<TournamentResult> ranking;

    for(size_t i = 0; i < contestants.size(); ++i)
    {
        TournamentResult result;

        result.name =
            contestants[i].identity.name;

        result.wins =
            wins[i];

        result.losses =
            losses[i];

        result.draws =
            draws[i];

        ranking.push_back(result);
    }

    std::sort(
        ranking.begin(),
        ranking.end(),
        [](
            const TournamentResult& a,
            const TournamentResult& b
        )
        {
            //----------------------------------
            // More wins
            //----------------------------------

            if(a.wins != b.wins)
            {
                return
                    a.wins > b.wins;
            }

            //----------------------------------
            // Fewer losses
            //----------------------------------

            if(a.losses != b.losses)
            {
                return
                    a.losses < b.losses;
            }

            //----------------------------------
            // More draws
            //----------------------------------

            return
                a.draws > b.draws;
        }
    );

    std::cout
        << "\n=====================================\n";

    std::cout
        << "FINAL STANDINGS\n";

    std::cout
        << "=====================================\n";

    for(size_t i = 0; i < ranking.size(); ++i)
    {
        std::cout
            << i + 1
            << ". "
            << ranking[i].name
            << "\n";

        std::cout
            << "Wins: "
            << ranking[i].wins
            << "\n";

        std::cout
            << "Losses: "
            << ranking[i].losses
            << "\n";

        std::cout
            << "Draws: "
            << ranking[i].draws
            << "\n\n";
    }

    std::cout
        << "=====================================\n";

    std::cout
        << "TOURNAMENT CHAMPION\n";

    std::cout
        << "=====================================\n";

    std::cout
        << ranking.front().name
        << "\n";

    std::cout
        << "Record: "
        << ranking.front().wins
        << "-"
        << ranking.front().losses;

    if(ranking.front().draws > 0)
    {
        std::cout
            << "-"
            << ranking.front().draws;
    }

    std::cout
        << "\n=====================================\n";

}

}

namespace
{

//==================================================
// 100 Simulations
//==================================================

void runSimulation100()
{
    std::cout
        << "\nPLAYER 1\n";

    Character player1 =
        chooseCharacter();

    std::cout
        << "\nPLAYER 2\n";

    Character player2 =
        chooseCharacter();

    simulateBattles(
        player1,
        player2,
        100,
        false
    );
}

//==================================================
// 1000 Simulations
//==================================================

void runSimulation1000()
{
    std::cout
        << "\nPLAYER 1\n";

    Character player1 =
        chooseCharacter();

    std::cout
        << "\nPLAYER 2\n";

    Character player2 =
        chooseCharacter();

    simulateBattles(
        player1,
        player2,
        1000,
        false
    );
}

} // namespace

//==================================================
// Read Integer
//==================================================

int readInteger(
    int minimum,
    int maximum
)
{
    int value;

    while(true)
    {
        std::cin >> value;

        if(
            !std::cin.fail() &&
            value >= minimum &&
            value <= maximum
        )
        {
            return value;
        }

        std::cin.clear();

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n'
        );

        std::cout
            << "Invalid option. Try again: ";
    }
}

//==================================================
// Main
//==================================================

int main()
{
    int option = -1;

    while(option != 0)
    {
        printMainMenu();

        option =
            readInteger(
                0,
                5
            );

        switch(option)
        {
            //--------------------------------------------------
            // Individual Battle
            //--------------------------------------------------

            case 1:

                runSingleBattle();

                break;

            //--------------------------------------------------
            // Gauntlet
            //--------------------------------------------------

            case 2:

                runGauntlet();

                break;

            //--------------------------------------------------
            // Tournament
            //--------------------------------------------------

            case 3:

                runTournament();

                break;

            //--------------------------------------------------
            // 100 Simulations
            //--------------------------------------------------

            case 4:

                runSimulation100();

                break;

            //--------------------------------------------------
            // 1000 Simulations
            //--------------------------------------------------

            case 5:

                runSimulation1000();

                break;

            //--------------------------------------------------
            // Exit
            //--------------------------------------------------

            case 0:

                std::cout
                    << "\nGoodbye.\n";

                break;
        }
    }

    return 0;
}