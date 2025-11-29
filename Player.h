#pragma once
#include "Point.h"
#include "items.h"
#include "Screen.h"
#include "Direction.h"
#include "Player.h"
class Player
{
	static constexpr size_t NUM_KEYS = 5;
	Point point;
	Items* inventory;
	char keys[NUM_KEYS];
	int life_points;


public:
	void keyPressed(char ch);
	Player(char s, int x, int y,const char arr_keys[NUM_KEYS])
	{
		
		point = { x,y,Direction::directions[Direction::RIGHT],s };
		memcpy(keys, arr_keys, sizeof(keys[0]) * NUM_KEYS);
		inventory = NULL;
		life_points = 5;

	}
	Player() : point(), inventory(nullptr), life_points(5) {}

	bool isFullInventory()
	{
		return this->inventory != NULL;
	}
	
	void move_player_( Screen& screen);


};