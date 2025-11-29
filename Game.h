#pragma once
#include"Screen.h"
#include"Player.h"


class Game
{
	Screen screen;
	Player p1;
	Player p2;
public:
	Game();
	void run();
	
};