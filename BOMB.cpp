#include "BOMB.h"



bool BOMB::update()
{
    internalCycles++;
    if (internalCycles >= 1)
    {
        timer--;
        internalCycles = 0;
        return true;
    }
    return false;
}