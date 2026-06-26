#include "dice.h"
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