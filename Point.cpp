#include <iostream>
#include "Point.h"
#include "utils.h"
#include "Screen.h"
#include <cmath>


void Point::draw(char c) {
	gotoxy(x, y);
	std::cout << c << std::flush;
}

void Point::move()
{
	if (x + dir.dirx < 0 || x + dir.dirx > Screen::MAX_X) {
		dir.dirx = -dir.dirx;
	}
	if (y + dir.diry < 0 || y + dir.diry > Screen::MAX_Y) {
		dir.diry = -dir.diry;
	}
	x += dir.dirx;
	y += dir.diry;
}
Point Point::next() const
{
	int nx = x + dir.dirx;
	int ny = y + dir.diry;
	return Point(nx, ny, dir, ch);
}
double Point::distance(Point p)//returns the distance of two points
{
	int y = this->getY() - p.getY();
	int x = this->getX() - p.getX();
	return sqrt((x * x) + (y * y));
}