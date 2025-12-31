#pragma once
#include "Circle.h"
bool Circle:: inRange( Point& p)
{
	if (center.distance(p) <= radius)
		return true;
	return false;
}