#pragma once
#include "Point.h"
#include "Player.h"
#include <string>
#include <vector>
#include <iostream>
#include "Spring.h"

class Screen
{
public:
	static constexpr int MAX_X = 80;
	static constexpr int MAX_Y = 25;



private:

	char level[MAX_Y][MAX_X];
	int SwitchCounters = 0;
	std::vector<Spring>springs;
	bool darkmode=false;
	Point legendPos; //position of the legend in the screen
	bool isPointInVector(const std::vector<Point>& vec, int x, int y) const;


public:
	Screen();
	Screen(const char input[MAX_Y][MAX_X], bool createBottom = true);
	Screen(const std::string& filename)
	{
		memset(level, ' ', sizeof(level));
		SwitchCounters = 0;
		loadefile(filename); 
		buildSprings();
	}
	Screen(const std::string& filename, bool Bottom)
	{
		
		memset(level, ' ', sizeof(level));
		SwitchCounters = 0;
		loadefile(filename, Bottom);
		buildSprings();
	}

	char charAt(const Point& p) const
	{
		return level[p.getY()][p.getX()];
	}
	bool isPlayer(const Point& p);

	bool isBomb(const Point& p) const
	{
		return charAt(p) == '@';
	}
	bool isTorch(const Point& p) const
	{
		return charAt(p) == '!';
	}
	bool isSpring(const Point& p) const
	{
		return charAt(p) == '#';
	}
	bool isKey(const Point& p) const
	{
		return charAt(p) == 'K';
	}
	bool isRiddle(const Point& p) const
	{
		return charAt(p) == '?';

	}
	
	char (*getScreen())[MAX_X] //TODO: check if this works
	{
		return level;
	}
	bool isObstacle(const Point& p) const
	{
		return charAt(p) == '*';
	}
	bool isPlatform_off(const Point& p)
	{
		return charAt(p) == '\\';
	}
	bool isPlatform_on(const Point& p)
	{
		return charAt(p) == '/';
	}
	bool isDoor(const Point& p) const;

	bool isWall(const Point& p) const
	{
		return charAt(p) == 'W';
	}

	void setChar(const Point& p, char ch);

	int get_switch_counters()
	{
		return SwitchCounters;
	}
	bool antiBoom(const Point& p);
	
	void clearItem(const Point& p);
	void drawRoom() const;
	void drawStatus(const Player& p1, const Player& p2) const;
	std::vector<Point> getObstacleVector(Point startPoint);
	bool isPointPartOfObstacle(const std::vector<Point>& obstacle, const Point& p) const;
	bool loadefile(const std::string& filename,bool createBottom);
	bool loadefile(const std::string& filename);
	void buildSprings();
	std::vector<Point> getSpringVector(Point startPoint);
	
	



	std::vector<Spring>& getSprings()
	{
		return springs;
	}
	bool isDarkRoom()
	{
		return darkmode;
	}
	void changeDarkMode(bool new_mode)
	{
		darkmode = new_mode;
	}
	const Point& getLegendPos() const
	{ 
		return legendPos; 
	}
	
	void setLegendPos(Point newlegend_pos) 
	{
		legendPos = newlegend_pos;
	}
};