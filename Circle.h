#pragma once
#include "Point.h"
class Circle
{
	Point center;
	double radius;
public:
	Circle() {}
	Circle(double r, Point c) : center(c), radius(r) {}
	bool inRange(Point& p);
	Point getCenter() const
	{
		return this->center;
	}
	const double getRadius()
	{
		return this->radius;
	}
	void circle_setPoint(Point point)
	{
		center = point;
	}
};