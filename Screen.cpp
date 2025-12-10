#include <iostream>
#include "Player.h"
#include "Screen.h"
#include "utils.h"
#include <string.h>
#include<Windows.h>

Screen::Screen()
{
    memset(level, ' ', sizeof(level));
}
Screen::Screen(const char input[MAX_Y][MAX_X]) 
{
    for (int y = 0; y < MAX_Y; y++) {
        for (int x = 0; x < MAX_X; x++) {
            level[y][x] = input[y][x];
            if (level[y][x]=='/')
            {
                SwitchCounters++;
            }
        }
       
    }
   
}

void Screen::drawRoom() const {
    for (int y = 0; y < MAX_Y; y++) {
        gotoxy(0, y);
        for (int x = 0; x < MAX_X; x++) {
            char c = level[y][x];
            if (c == '\0') c = ' '; // אם חסר תו, תחליף ברווח
            std::cout << c;
        }
    }
    std::cout << std::flush;
}



void Screen::clearItem(const Point& p)
{
    level[p.getY()][p.getX()] = ' ';
    gotoxy(p.getX(), p.getY());
    std::cout << ' ';
}

void Screen::drawStatus(const Player& p1, const Player& p2) const {
    int baseRow = Screen::MAX_Y - 4;

   
    gotoxy(0, baseRow);
    std::cout << "Player1 Life: " << p1.getlifePoint();
    gotoxy(0, baseRow + 1);
    std::cout << "Inventory: " << p1.getinventory();
    gotoxy(0, baseRow + 2);
    std::cout << "Power: " << p1.getPower();

  
    std::string p2Life = "Player2 Life: " + std::to_string(p2.getlifePoint());
    std::string p2Inv = "Inventory: " + std::string(1, p2.getinventory());
    std::string p2Pw = "Power: " + std::to_string(p2.getPower());

    int colRightLife = Screen::MAX_X - p2Life.length();
    int colRightInv = Screen::MAX_X - p2Inv.length();
    int colRightPw = Screen::MAX_X - p2Pw.length();

    gotoxy(colRightLife, baseRow);
    std::cout << p2Life;
    gotoxy(colRightInv, baseRow + 1);
    std::cout << p2Inv;
    gotoxy(colRightPw, baseRow + 2);
    std::cout << p2Pw;

    std::cout << std::flush;
}

int Screen:: obstacle(const Point& p, Point obstacle_array[])
{
	const int MAX_OBS = 80;

	int size = 0;
	int x0 = p.getX();
	int y0 = p.getY();


	if (level[y0][x0] != '*')
		return 0;


	obstacle_array[size++] = Point(x0, y0, Direction::directions[Direction::STAY], '*');


	for (int x = x0 + 1; x < Screen::MAX_X && size < MAX_OBS; ++x)
	{
		if (level[y0][x] != '*')
			break;

		obstacle_array[size++] =
			Point(x, y0, Direction::directions[Direction::STAY], '*');
	}


	for (int x = x0 - 1; x >= 0 && size < MAX_OBS; --x)
	{
		if (level[y0][x] != '*')
			break;

		obstacle_array[size++] =
			Point(x, y0, Direction::directions[Direction::STAY], '*');
	}


	for (int y = y0 - 1; y >= 0 && size < MAX_OBS; --y)
	{
		if (level[y][x0] != '*')
			break;

		obstacle_array[size++] =
			Point(x0, y, Direction::directions[Direction::STAY], '*');
	}


	for (int y = y0 + 1; y < Screen::MAX_Y && size < MAX_OBS; ++y)
	{
		if (level[y][x0] != '*')
			break;

		obstacle_array[size++] =
			Point(x0, y, Direction::directions[Direction::STAY], '*');
	}

	return size;
}

