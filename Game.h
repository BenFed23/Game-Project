#pragma once
#include"Screen.h"
#include"Player.h"
#include "Riddle.h"
#include <vector>
#include "Circle.h"
#include<string>
#include "Spring.h"
#include <list>

class Game
{
public:
	static constexpr int TORCH_RADIUS = 8;
	static constexpr int Bomb_RADIUS = 3;
private:
	bool isDark = false;
	static const int NUMLEVELS = 3;
	Screen screen;
	Screen current_riddle;
	Screen gameMenu;
	Screen instructions;
	Screen pauseScreen;
	Player p1;
	Player p2;
	std::vector<Screen> savedlevels;
	std::vector<Screen> originalLevels;
	char riddles_chars[NUMLEVELS][Screen::MAX_Y][Screen::MAX_X];
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
	std::vector<int> pressSwitches;
	std::vector<bool> levelUnlocked;
	bool p1_activated_bomb = false;
	bool p2_activated_bomb = false;
	Circle bomb_explosion_p1 = Circle(Bomb_RADIUS, Point(0,0));
	Circle bomb_explosion_p2 = Circle(Bomb_RADIUS, Point(0, 1));
	int explode_at_p1 = -1;
	int explode_at_p2 = -1;
	bool initFailed = false;
	std::string initErrorMsg;
protected:
	int game_Cycles = 0;
	std::list<std::pair<size_t, char>> steps; // pair: iteration, step

	
	

public:
	
	
	Game() ;

	struct StartPositions
	{
		int p1_x, p1_y;
		int p2_x, p2_y;
	};

	StartPositions levelStarts[NUMLEVELS] =
	{
		{2, 13, 2, 2},   //level1
		{5, 5, 20, 5},  //level2
		{2, 2, 70, 18} //level3
	};
	void run();
	virtual char handleinput() = 0;
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
	void boom(Circle c, Screen& screen);
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
	void Bomb_explosion_logic(Circle& c, bool& activated_bomb, int& explode_at);
	void drawDarkRoom(Screen& s, Circle& light);
	void drawCurrentRoom();
	bool check_validity_of_L(Screen& screen);
	void showFatalInitErrorAndExit();
	virtual void record(std::string fileName) = 0;

	void add_line(int game_cycle, char key)
	{
		steps.push_back({ game_cycle, key });
	}

};