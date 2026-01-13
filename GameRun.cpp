#include "GameRun.h" 
#include <conio.h>
#include "utils.h"


char GameRun:: handleinput()
{
    char key = 0;
    if (_kbhit())
    {
        key = _getch();
    }
    
    return key;
}




