#include "GameFiles.h"


GameFiles:: GameFiles()
{
    steps.open("adv-world.steps");
    if (!steps)
        throw std::string("Failed to open adv-world.steps");

	readNextStep();
   
}


void GameFiles::readNextStep() // Reads the next step from the steps file
{
    if (!(steps >> nextStepCycle >> nextStepKey))
    {
        nextStepCycle = -1;
        nextStepKey = 0;
    }
}



/*char GameFiles::handleinput()
{
    std::string line;
    if (!std::getline(steps, line))
        return 0; 

    if (!line.empty() && line.back() == '\r')
        line.pop_back();

    if (line.empty())
        return 0;

    char k = line[0];
    if (k == '.') return 0;   
    return k;
}
*/

char GameFiles::handleinput()
{
    if (nextStepCycle != -1 && game_Cycles == nextStepCycle)
    {
        char keyToReturn = nextStepKey;

        readNextStep();

        return keyToReturn;
    }

    return 0;
}
