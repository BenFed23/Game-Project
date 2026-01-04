#pragma once
#include"Screen.h"
#include"Player.h"
#include "Riddle.h"
#include <vector>
#include "Circle.h"
#include<string>
#include "Spring.h"

class Game
{
	int game_Cycles = 0;
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
	bool solved_Riddle = false;
	Spring* p1_activeSpring = nullptr;
	Spring* p2_activeSpring = nullptr;
	bool p1canpass = false;
	bool p2canpass = false;
	bool isGameOver = false;
public:
	
	Game();

	struct StartPositions 
	{
		int p1_x, p1_y;
		int p2_x, p2_y;
	};

	StartPositions levelStarts[NUMLEVELS] =
	{
		{2, 13, 2, 2},   //level1
		{5, 5, 20, 5},  //level2
		{2, 18, 70, 18} //level3
	};
	void run();
	void moveLevel(int index);
	void Menu();
	bool pauseMenu();
	void on_or_off_switch(Point& p, Screen& s);
	bool switchesOn(Screen& screen);
	bool enterRoom(Player& p);
	bool riddle_answers(Riddle r, Player& p);
	void resetGame();
	bool Push(Screen& screen, Player& p, int bonus_power = 0);
	bool pushing_together(Player& p, Player& k, Screen& screen);
	void stopPower(Player& p1, Player& p2);
	void handleMovement(Player& p, Player& other, bool clearPass);
	void boom(Circle c,Screen& screen);
	bool fileToArray(const std::string& filename, char dest[Screen::MAX_Y][Screen::MAX_X]);
	bool fileToLevel(const std::string& filename, Screen& target);
	Spring* getSpringAt(const Point& p);
	Direction check_Spring_direction(Spring* spring);
	bool match_directions(Spring* spring, Player& p);
	bool compressed(Player& p, Spring* spring);
	void release_spring(Player& p, Spring* spring, Screen& screen);
	void handleInteraction(Player& p, Point point, char drop_key_press);
	bool executeRiddle(Player& p);
	void handle_flying_movement(Player& p, Player& other, bool canPass, char key);
	void handle_pre_spring_movement(Player& p, Player& other, bool canPass);
	void adjust_player_positions_acc_to_L(int legendPos_Y);
};