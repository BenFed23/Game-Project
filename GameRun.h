#pragma once
#include "Game.h"
#include <fstream>


class GameRun:public Game
{
	std::ofstream stepsFile;
public:
	GameRun(); // constructor to open the steps file
	~GameRun(); // destructor to close the steps file
	char handleinput() override;
};

