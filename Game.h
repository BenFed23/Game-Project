#pragma once
#include"Screen.h"
#include"Player.h"
#include "Riddle.h"
#include <vector>
#include "Circle.h"
#include<string>

class Game
{
	bool isDark = false;
	static const int NUMLEVELS = 3;
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
	Riddle riddles[NUMLEVELS - 1];
	int visible_level = 1;
	std::vector<std::string> worldFiles;
	std::vector<std::string> riddleFiles;
public:
	Game();
	void run();
	void moveLevel(int index);
	void Menu();
	bool pauseMenu();
	void on_or_off_switch(Point& p, Screen& s);
	bool switchesOn(Screen& screen);
	void enterRoom();
	bool riddle_answers(Riddle r, Player& p);
	void resetGame();
	bool Push(Screen& screen, Player& p, int bonus_power = 0);
	bool pushing_together(Player& p, Player& k, Screen& screen);
	void stopPower(Player& p1, Player& p2);
	void handleMovement(Player& p, Player& other, bool clearPass);
	void boom(Circle c,Screen& screen);
	bool fileToArray(const std::string& filename, char dest[Screen::MAX_Y][Screen::MAX_X]);
	bool fileToLevel(const std::string& filename, Screen& target);
};