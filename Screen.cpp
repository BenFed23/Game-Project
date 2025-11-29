#include <iostream>

#include "Screen.h"
#include "utils.h"

void Screen::draw(int mapnum) const {
    for (int y = 0; y <= MAX_Y; y++) {
        gotoxy(0, y);
        for (int x = 0; x <= MAX_X; x++) {
            std::cout << maps[mapnum][y][x];
        }
    }
    std::cout << std::flush;
}
void Screen:: moveLevel(const Point& p)
{
	if (Screen::isDoor(p))
	{
        char c = charAt(p);
		int level = c - '0';
        if (level < 0 || level > 2)
        {
            std::cout << "illegal value" << level << "/n";
            return;
        }
        cls();
        this->draw(level-1);
	}
}