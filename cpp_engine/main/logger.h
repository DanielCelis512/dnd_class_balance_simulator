#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>

extern bool showCombatLog;

template<typename T>
void combatLog(const T& value)
{
    if(showCombatLog)
        std::cout << value;
}

#endif