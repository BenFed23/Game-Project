#pragma once
#include "Game.h"
#include <fstream>

class GameFiles: public Game
{
    std::string MoveFile="adv-world.steps";
    int nextStepCycle = -1; 
    char nextStepKey = 0;  

	void readNextStep(); // Reads the next step from the steps file
    std::ifstream steps;
   
public:
    GameFiles();
    virtual char handleinput() override;
};

