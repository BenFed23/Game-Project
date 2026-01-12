#pragma once
#include "Point.h"
#include "items.h"
#include "Direction.h"


class Screen;
class Player
{
	static constexpr size_t NUM_KEYS = 5;
	Point point;
	char inventory;
	char movekeys[NUM_KEYS];
	char dropkey;
	int life_points;
	int power;
	char stepchar = ' ';
	int boostFramesLeft = 0; //time remaining for boost
	int boostSpeed = 0;
	Direction Boost_dir = Direction::directions[Direction::STAY];
	char symbol = 'P';

	int player_room_level = 0;

public:

	void keyPressed(char ch);
	Player(char s, int x, int y, const char arr_keys[NUM_KEYS], char new_dropkey)
	{

		point = { x,y,Direction::directions[Direction::STAY],s };
		memcpy(movekeys, arr_keys, sizeof(movekeys[0]) * NUM_KEYS);
		inventory = 'E';
		dropkey = new_dropkey;
		life_points = 3;
		power = 1;

	}
	Player() : point(), inventory(' '), life_points(3), power(1) {}

	bool isFullInventory()const
	{
		return this->inventory != 'E';
	}
	Point getPoint() const
	{
		return point;
	}
	int getlifePoint()const
	{
		return life_points;
	}
	void setLifePoints(int newPoints)
	{
		life_points = newPoints;
	}
	char getinventory()const
	{
		return inventory;
	}
	void freeze()
	{
		point.changeDir(Direction::directions[Direction::STAY]);
	}
	Direction getdirection()
	{
		return point.getDirection();
	}


	void setInventory(char item)
	{
		inventory = item;
	}

	bool move_player_(Screen& screen, bool canMove, char nextStepChar);
	void setPoint(int x, int y, Direction dir);
	char getItem();
	void drop_item(Point p, Screen& screen);
	void pick_item(Screen& screen, char itemToPick);
	void draw_player();
	bool isPlayerKey(char ch) const;
	void reduceBoost();
	void startLaunch(int speed, int duration, const Direction& dir);
	void resetBoost();

	bool justpicked;

	void set_justpicked(bool is_picked)
	{
		justpicked = is_picked;;
	}
	bool get_justpicked() const
	{
		return justpicked;
	}

	int getPower() const
	{
		return power;
	}

	void setPower(int new_power)
	{
		power = new_power;
	}
	char getStepChar() const
	{
		return stepchar;
	}

	void setStepChar(char c)
	{
		stepchar = c;
	}

	void setRoom(int room)
	{
		player_room_level = room;
	}
	int getRoom() const
	{
		return player_room_level;
	}
	bool isInBoost() const
	{
		return boostFramesLeft > 0;
	}


	bool operator==(const Player& other) const
	{
		return (this->symbol == other.symbol);
	}

	void setDirection(const Direction& dir)
	{
		point.changeDir(dir);
	}

	int get_boostSpeed() const
	{
		return boostSpeed;
	}

	int get_boostFramesLeft() const
	{
		return boostFramesLeft;
	}
	Direction getBoostDir() const
	{
		return Boost_dir;
	}
};