#include <cstdlib>
#include <ctime>

#include "class_factory.h"
#include "battle.h"

int main()
{
    std::srand(
        static_cast<unsigned int>(
            std::time(nullptr)
        )
    );

    Character barbarian =
        createBarbarian();

    Character wizard =
        createWizard();

    battle(barbarian, wizard);

    return 0;
}
