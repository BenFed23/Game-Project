#pragma once
#include "Circle.h"
class Tourch
{
	Circle area;
public:
	Tourch(){}
	Tourch(Circle& c)
	{
		area = c;
	}
};

