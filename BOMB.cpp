#include "BOMB.h"



bool BOMB::update()
{
    internalCycles++;
    if (internalCycles >= 2)
    {
        timer--;
        internalCycles = 0;
        return true;
    }
    return false;
}