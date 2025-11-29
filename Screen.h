#pragma once

#include "Point.h"
class Screen {
public:
	static constexpr int MAX_X = 80;
	static constexpr int MAX_Y = 25;
private:
	
	char maps[3][MAX_Y + 1][MAX_X + 1] =
	{ 
		{
			//   01234567890123456789012345678901234567890123456789012345678901234567890123456789
			"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 0
			"1                           W           W            W                         W",  // 1
			"W                           W           W            W                         W",  // 2
			"W                           W           W            W                         W",  // 3
			"W                           W           W            W                         W",  // 4
			"W                           W           W            W                         W",  // 5
			"W                           W           W            W                         W",  // 6
			"W                                       W            W                         W",  // 7
			"W                                       W            W                 %       W",  // 8
			"W                           W           W            W                         W",  // 9
			"W                           W           W            W                         W",  // 10
			"W                           W           W            W                         W",  // 11
			"W                           W           W      WWWWWWWWWWWWWWWWWWWWWWWWWW      W",  // 12
			"W                           W           W                                      W",  // 13
			"W                           W           W                                      W",  // 14
			"W                           W           W                                      W",  // 15
			"W                           W                                                  W",  // 16
			"W                           W                                                  W",  // 17
			"W                           W                                                  W",  // 18
			"W                           W           W                                      W",  // 19
			"W                           W           W                                      W",  // 20
			"W                           W           W                                      W",  // 21
			"W                           W           W                                      W",  // 22
			"W                           W           W                                      W",  // 23
			"WWWWWWWWWWWWWWWWW2WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"   // 24
		
	},
{
	//   01234567890123456789012345678901234567890123456789012345678901234567890123456789
			"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 0
			"W                          W           W            W                         W",  // 1
			"2                           W           W            W                         W",  // 2
			"W                           W           W            W                         W",  // 3
			"W                           W           W            W                         W",  // 4
			"W                           W           W            W                         W",  // 5
			"W                           W           W            W                         W",  // 6
			"W                                       W            W                         W",  // 7
			"W                                       W            W                 %       W",  // 8
			"W                           W           W            W                         W",  // 9
			"W                           W           W            W                         W",  // 10
			"W                           W           W            W                         W",  // 11
			"W                           W           W            WWWWWWWWWWWWWWWWWWWW      W",  // 12
			"W                           W           W                                      W",  // 13
			"W                           W           W                                      W",  // 14
			"W                           W           W                                      W",  // 15
			"W                           W                                                  W",  // 16
			"W                           W                                                  W",  // 17
			"W                           W                                                  W",  // 18
			"W             W             W           W                                      W",  // 19
			"W             W             W           W                                      W",  // 20
			"W             W             W           W                                      W",  // 21
			"W             W             W           W                                      W",  // 22
			"W             W             W           W                                      W",  // 23
			"WWWWWWWWWWWWWWWW 3 WWWWWWWWWWWW   WWWWWWWWWWWW  WWWWWWWWWWWW  WWWWWWWWWWWWWWWW W"   // 24

	},
{

	//   01234567890123456789012345678901234567890123456789012345678901234567890123456789
			"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 0
			"W                           W           W            W                         W",  // 1
			"W                           W           W            W                         W",  // 2
			"W                           W           W            W                         W",  // 3
			"W                           W           W            W                         W",  // 4
			"W                           W           W            W                         W",  // 5
			"W                           W           W            W                         W",  // 6
			"W                                       W            W                         W",  // 7
			"W                                       W            W                 %       W",  // 8
			"W                           W           W            W                         W",  // 9
			"W                           W           W            W                         W",  // 10
			"W                           W           W            W                         W",  // 11
			"W                           W           W      WWWWWWWWWWWWWWWWWWWWWWWWWW      W",  // 12
			"W                           W           W                                      W",  // 13
			"W                           W           W                                      W",  // 14
			"W                           W           W                                      W",  // 15
			"W                           W                                                  W",  // 16
			"W                           W                                                  W",  // 17
			"W                           W                                                  W",  // 18
			"W                           W           W                                      W",  // 19
			"W                           W           W                                      W",  // 20
			"W                           W           W                                      W",  // 21
			"W                           W           W                                      W",  // 22
			"W                           W           W                                      W",  // 23
			"WWWWWWWWWWWWWWWW   WWWWWWWWWWWW   WWWWWWWWWWWW  WWWWWWWWWWWW  WWWWWWWWWWWWWWWW W"   // 24
	} };
	char charAt(const Point& p,int i=0) const {
		return maps[i][p.getY()][p.getX()];
	}
public:
	bool isWall(const Point& p) const {
		return charAt(p) == 'W';
	}
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
	bool isObstacle(const Point& p) const
	{
		return charAt(p) == '*';
	}
	bool isDoor(const Point& p) const
	{
		int num = p.getChar() - '0';
		
		return(num > 1 && num < 3);
	}
	bool isWon(const Point& p) const
	{
		
		return charAt(p) == '4';
	}

	void draw(int num) const;
	void moveLevel(const Point& p);
	

	
};