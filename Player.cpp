#include "player.h"
#include "Screen.h"
#include "items.h"
#include <cstdlib>
#include <cctype>
#include "Point.h"
#include <iostream>


void Player::keyPressed(char ch)
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

bool Player::move_player_(Screen& screen, bool canMove, char nextStepChar)
{
	if (!canMove)
	{
		point.draw();
		return false;
	}

	point.draw(this->stepchar);

	point.move();



	this->stepchar = nextStepChar;

	point.draw();

	return true;
}


char Player::getItem()
{
	return (inventory);
}
void Player::setPoint(int x, int y, Direction dir)
{
	point.setX(x);
	point.setY(y);
	point.changeDir(dir);
}
void Player::drop_item(Point drop_location, Screen& screen)
{
	if (inventory == 'E')
	{
		//screen.drawMessage("Inventory is empty");
		return;
	}
	screen.setChar(drop_location, inventory);

	drop_location.draw(inventory);

	inventory = 'E';
}


void Player::pick_item(Screen& screen, char itemToPick)
{
	if (isFullInventory()) return;

	inventory = itemToPick;

	screen.clearItem(point);
}

void Player::draw_player()
{
	point.draw();
}
void Player::resetBoost() //after boost ends
{
	boostFramesLeft = 0;
	boostSpeed = 0;
	power = 1;
}

void Player::startLaunch(int speed, int duration, const Direction& dir) //when spring is activated
{
	this->boostSpeed = speed;
	this->boostFramesLeft = duration;
	this->Boost_dir = dir;

}

bool Player::isPlayerKey(char ch) const
{
	for (char key : movekeys)
	{
		if (std::tolower(key) == std::tolower(ch))
		{
			return true;
		}
	}
	return false;
}

void Player::reduceBoost()
{
	if (boostFramesLeft > 0)
	{
		boostFramesLeft--;
	}
}