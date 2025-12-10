#pragma once
#include"Screen.h"
#include"Player.h"
#include "Riddle.h"


class Game
{
	static const int NUMLEVELS=3;
	Screen screen;
	Screen current_riddle;
	Screen gameMenu;
	Screen instructions;
	Screen pauseScreen;
	Player p1;
	Player p2;
	char levels[NUMLEVELS][Screen::MAX_Y][Screen::MAX_X];
	char riddles_chars[NUMLEVELS][Screen::MAX_Y][Screen::MAX_X];
	int press_switches = 0;
	int currentLevel;
	Riddle riddles[NUMLEVELS-1];

public:
	Game();
	void run();
	void moveLevel(int index);
	void Menu();
	bool pauseMenu();
	void on_or_off_switch(Point& p, Screen& s);
	bool switchesOn(Screen& screen);
	void enterRoom();
	bool riddle_answers(Riddle r,Player& p);
	void resetGame();
	bool Push(Screen& screen, Point arr[],Player & p);
	bool pushing_together(Player& p, Player& k, Point arr1[],Point arr2[]);
	void stopPower(Player& p1, Player& p2);
	
};