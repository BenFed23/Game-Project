#pragma once
#include "items.h"
#include <iostream>
class Key :public Items
{
	char door;
public:
	Key( char d) : Items('K'), door(d) {}
};