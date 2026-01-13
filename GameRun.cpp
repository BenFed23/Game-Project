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

void GameRun::record(std::string fileName)
{

    std::ofstream steps_file(fileName, std::ios::trunc);
    if (!steps_file.is_open())
    {
        gotoxy(20, 23);
        std::cout << "Error opening file for writing: " << fileName << std::endl;
        return;
    }
    for (const auto& step : steps)
    {
        steps_file << '\n' << step.first << ' ' << step.second;
    }
    steps_file.close();

}



