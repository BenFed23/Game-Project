#include "player.h"
#include "Screen.h"
#include "items.h"
#include <cstdlib>
#include <cctype>
#include "Point.h"
void Player:: keyPressed(char ch)
{
	size_t index = 0;
	for (char key : keys) {
		if (std::tolower(key) == std::tolower(ch)) {
			point.changeDir(Direction::directions[index]);
			break;
		}
		++index;
	}
}
void Player::move_player_( Screen& screen)
{
	
	Point old_location = point;
	old_location.draw(' ');
	
	point.move();
	if (screen.isWall(point))
	{
		point = old_location;
		point.changeDir(Direction::directions[Direction::STAY]);

	}

	point.draw();

}