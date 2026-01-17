#pragma once
#include "Point.h"
class Items
{
	char symbol;
public:
	enum class symbols { 
	torch='!',
	bomb='@',
	key='K'
	};

	Items(char new_symbol) : symbol(new_symbol){}
	char getSymbol()
	{
		return symbol;
	}

};