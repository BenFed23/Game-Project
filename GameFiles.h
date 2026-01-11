#pragma once
#include "Game.h"
#include <fstream>

class GameFiles: public Game
{
    std::string MoveFile="adv-world.steps";
    std::ifstream steps;
   
public:
    GameFiles();
    char handleinput() override;
};

