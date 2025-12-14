#include "player.h"
#include "Screen.h"
#include "items.h"
#include <cstdlib>
#include <cctype>
#include "Point.h"
#include <iostream>
#include "Screen.h"
void Player:: keyPressed(char ch)
{
	size_t index = 0;
	for (char key : movekeys) {
		if (std::tolower(key) == std::tolower(ch)) {
			point.changeDir(Direction::directions[index]);
			break;
		}
		++index;
	}
}
bool Player::move_player_(Screen& screen, bool clearPass,char& stepchar)
{
	Point old_location = point;
	Point next_location = point;
	next_location.move();
	stepchar = screen.charAt(next_location);
	point.move();

	
	if (screen.isWall(point) || (screen.isDoor(point) && !clearPass))
	{
		point = old_location;
		point.changeDir(Direction::directions[Direction::STAY]);
		point.draw();      
		return false;      
	}
	old_location.draw(screen.charAt(old_location));
	pick_item(screen);
	point.draw();
	return true;         
}
char Player::getItem()
{
	return (inventory);
}
void Player::setPoint(int x,int y,Direction dir)
{
	point.setX(x);
	point.setY(y);
	point.changeDir(dir);
}
void Player:: drop_item(Point drop_location,Screen& screen)
{
	if (inventory == 'E' )
	{
		//screen.drawMessage("Inventory is empty");
		return;
	}
	screen.setChar(drop_location, inventory);

	drop_location.draw(inventory);

	inventory = 'E';
}
void Player:: pick_item(Screen& screen)
{
	if(isFullInventory())
	{
		//screen.drawMessage("Inventory is full");
		return;
	}
	else
	{
		if (screen.isKey(point))
		{
			inventory = 'K';
			screen.clearItem(point);
		}

		else if (screen.isBomb(point))
		{

			inventory = '@';
			screen.clearItem(point);
		}
		else if (screen.isTorch(point))
		{
			inventory = '!';
			screen.clearItem(point);
		}
	}
}

void Player::draw_player()
{
	point.draw();
}

