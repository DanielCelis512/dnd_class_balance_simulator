#include "dice.h"

#include <algorithm>
#include <cstdlib>

int rollDice(int number, int sides)
{
    if(number <= 0 || sides <= 0)
        return 0;

    int total = 0;

    for(int i = 0; i < number; i++)
    {
        total += rand() % sides + 1;
    }

    return total;
}

int rollD20()
{
    return rollDice(1, 20);
}

int rollWithAdvantage()
{
    return std::max(
        rollD20(),
        rollD20()
    );
}

int rollWithDisadvantage()
{
    return std::min(
        rollD20(),
        rollD20()
    );
}