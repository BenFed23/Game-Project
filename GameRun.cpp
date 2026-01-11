#include "GameRun.h"
#include <conio.h>
char GameRun:: handleinput()
{
    char key = 0;
    if (_kbhit())
    {
        key = _getch();

    }
    return key;
}