#include "Game.h"
#include <conio.h>
#include "Screen.h"
#include<Windows.h>

Game::Game()
{
	Screen screen;
	Player player_1('$', 2, 2,"wdzas");
	p1 = player_1;


}
void Game:: run()
{
	
	bool iswon = false;
	char key= 0;
	constexpr char ESC = 27;
	screen.draw(0);
	p1.move_player_(screen);
	while(key!='4')
	{
		while(!_kbhit())
		{
			p1.move_player_(screen);
			Sleep(50);
			
		}
		
		char key = _getch();
		if (_kbhit())
		{
			key = _getch();
			
			if (key == ESC) {
				// pause
				key = _getch();
				if (key == 'h' || key == 'H') 
				{
					break;
				}
			}
		}
	
		else
		{
			p1.keyPressed(key);
		}
		p1.move_player_(screen);
	}
		
}