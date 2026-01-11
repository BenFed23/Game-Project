#include "GameRun.h"
#include <conio.h>

GameRun::GameRun()
{
    stepsFile.open("adv-world.steps", std::ios::trunc);
}

GameRun::~GameRun()
{
    if (stepsFile.is_open())
        stepsFile.close();
}
char GameRun:: handleinput()
{
    char key = 0;
    if (_kbhit())
    {
        key = _getch();
        if (key != 0 && stepsFile.is_open())
        {
			stepsFile << game_Cycles << ":" << key << std::endl; //write the step to the file

			stepsFile.flush();// ensure data is written immediately
        }
        

    }
    return key;
}


