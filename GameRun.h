#pragma once
#include "Game.h"
#include <fstream>
#include <list>


class GameRun:public Game
{
	std::ofstream stepsFile;
public:
	
	char handleinput() override;
	void record(std::string fileName);

	
};

