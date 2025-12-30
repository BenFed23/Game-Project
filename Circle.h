#pragma once
#include "Point.h"
class Circle
{
	Point center;
	double radius;
public:
	Circle(){}
	Circle(double r, Point c): center(c),radius(r) {}
	bool inRange( Point& p);
	const Point getCenter()
	{
		return this->center;
	}
	const int getRadius()
	{
		return this->radius;
	}
};