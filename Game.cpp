#include "Game.h"
#include <conio.h>
#include "Screen.h"
#include<Windows.h>
#include "utils.h"
#include <iostream>
#include "Riddle.h"

Game::Game() : currentLevel(0), p1('$', 1, 1, "wdxas",'e'),p2('&',2,2,"ilmjk",'o') {
	const char level0[Screen::MAX_Y][Screen::MAX_X] = {
		"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 0
		"W                                                                             W",  // 1
		"W                                                                             W",  // 2
		"W                                                                             W",  // 3
		"W                                1                                            W",  // 4
		"W                                                                             W",  // 5
		"W                                                                             W",  // 6
		"W                       ?                                                     W", // 7
		"W                                                                             W",  // 8
		"W                                                               /             W",  // 9
		"W                                                                             W",  // 10
		"W                        K                                                    W",  // 11
		"W                                                                             W",  // 12
		"W                                                                             W",  // 13
		"W                   *                                                         W",  // 17
		"W                                                                             W",  // 14
		"W                                                                             W",  // 15
		"W                                                                             W",  // 16
		"W                                                                             W",  // 18
		"W                                                                             W",  // 19
		"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",  // 20
		"                                                                              ",  // 21
		"                                                                              ",  // 22
		"                                                                              ",  // 23
		"                                                                              "   // 24
	//   01234567890123456789012345678901234567890123456789012345678901234567890123456789                                                                             


	};

	const char level1[Screen::MAX_Y][Screen::MAX_X] = {
		"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 0
		"W                                                                        ?    W",  // 1
		"W                                                                             W",  // 2
		"W                                                                             W",  // 3
		"W                                                             2               W",  // 4
		"W                                                                             W",  // 5
		"W                                                  /                          W",  // 6
		"W                                                                             W",  // 7
		"W                                                                             W",  // 8
		"W                                K                                            W",  // 9
		"W                                                                             W",  // 10
		"W                                                                             W",  // 11
		"W                                                                             W",  // 12
		"W                                                                             W",  // 13
		"W                                                                             W",  // 14
		"W                                                                             W",  // 15
		"W                                                                             W",  // 16
		"W                                                                             W",  // 17
		"W                                                                             W",  // 18
		"W                                                                             W",  // 19
		"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",  // 20
		"                                                                               ",  // 21
		"                                                                               ",  // 23
		"                                                                               ",  // 22
		"                                                                               "
	};

	const char level2[Screen::MAX_Y][Screen::MAX_X] = {
		"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 0
		"W                                                                             W",  // 1
		"W           WWWWWWWWWW      W          W         WWWWWWWWWWWWWW               W",  // 2
		"W                W          W          W         W                            W",  // 3
		"W                W          W          W         W                            W",  // 4
		"W                W          WWWWWWWWWWWW         WWWWWWWWWWWWWW               W",  // 5
		"W                W          W          W         W                            W",  // 6
		"W                W          W          W         W                            W",  // 7
		"W                W          W          W         WWWWWWWWWWWWWWW              W",  // 8
		"W                                                                             W",  // 9
		"W                                                                             W",  // 10
		"W                                                                             W",  // 11
		"W             WWWWWWWWWWWWWWW    W           W     WWWWWW                     W",  // 12
		"W             W                  WW          W     W     W                    W",  // 13
		"W             W                  W  W        W     W      W                   W",  // 14
		"W             WWWWWWWWWWWWWWW    W    W      W     W     W                    W",  // 15
		"W             W                  W      W    W     W    W                     W",  // 16
		"W             W                  W        W  W     W   W                      W",  // 17
		"W             WWWWWWWWWWWWWWW    W          WW     WWWW                       W",  // 18
		"W                                                                             W",  // 19
		"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",  // 20
		"                                                                               ",  // 21
		"                                                                               ",  // 22
		"                                                                               ",  // 23
		
	};
	const char opening[Screen::MAX_Y][Screen::MAX_X] = {
		"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 0
		"W                                                                             W",  // 1
		"W                            MENU:                                            W",  // 2
		"W          --------------------------------------------                       W",  // 3
		"W                                                                             W",  // 4
		"W                  TO PLAY THE GAME PRESS [1]                                 W",  // 5
		"W                                                                             W",  // 6
		"W                  FOR INSTRUCTIONS PRESS [8]                                 W",  // 7
		"W                                                                             W",  // 8
		"W                  TO EXIT PRESS [9]                                          W",  // 9
		"W                                                                             W",  // 10
		"W                                                                             W",  // 11
		"W                                                                             W",  // 12
		"W                                                                             W",  // 13
		"W                                                                             W",  // 14
		"W                                                                             W",  // 15
		"W                                                                             W",  // 16
		"W                                                                             W",  // 17
		"W                                                                             W",  // 18
		"W                                                                             W",  // 19
		"W                                                                             W",  // 20
		"W                                                                             W",  // 21
		"W                                                                             W",  // 22
		"W                                                                             W",  // 23
		"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
	};
	
	
	
	const char instructionsScreen[Screen::MAX_Y][Screen::MAX_X] = {
		"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 0
		"W                                                                             W",  // 1
		"W                                                                             W",  // 2
		"W                             INTRUCTIONS                                     W",  // 3
		"W                 ----------------------------------                          W",  // 4
		"W                     PLAYER 1 KEYS:                                          W",  // 5
		"W              W - UP                                                         W",  // 6
		"W              A - LEFT                                                       W",  // 7
		"W              D - RIGHT                                                      W",  // 8
		"W              X - DOWN                                                       W",  // 9
		"W              S - STAY                                                       W",  // 10
		"W              E - DROP ITEM                                                  W",  // 11
		"W                                                                             W",  // 12
		"W                                                                             W",  // 13
		"W                       PLAYER 1 KEYS:                                        W",  // 14
		"W              I - UP                                                         W",  // 15
		"W              J - LEFT                                                       W",  // 16
		"W              L - RIGHT                                                      W",  // 17
		"W              M - DOWN                                                       W",  // 18
		"W              K - STAY                                                       W",  // 19
		"W              O - DROP ITEM                                                  W",  // 20
		"W                                                                             W",  // 21
		"W                                                                             W",  // 22
		"W                                                                             W",  // 23
		"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
	};
	const char pauseMenu[Screen::MAX_Y][Screen::MAX_X] = { 
		"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 0
		"W                                                                             W",  // 1
		"W                                                                             W",  // 2
		"W                          GAME PAUSED                                        W",  // 3
		"W                                                                             W",  // 4
		"W                                                                             W",  // 5
		"W                                                                             W",  // 6
		"W             PRESS ESC TO CONTINUE, OR H TO EXIT THE GAME                    W",  // 7
		"W                                                                             W",  // 8
		"W                                                                             W",  // 9
		"W                                                                             W",  // 10
		"W                                                                             W",  // 11
		"W                                                                             W",  // 12
		"W                                                                             W",  // 13
		"W                                                                             W",  // 14
		"W                                                                             W",  // 15
		"W                                                                             W",  // 16
		"W                                                                             W",  // 17
		"W                                                                             W",  // 18
		"W                                                                             W",  // 19
		"W                                                                             W",  // 20
		"W                                                                             W",  // 21
		"W                                                                             W",  // 22
		"W                                                                             W",  // 23
		"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
	};
	

	const char riddle1[Screen::MAX_Y][Screen::MAX_X] = {
		"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 0
		"W                                                                             W",  // 1
		"W                            RIDDLE NUMBER 1:                                 W",  // 2
		"W                ----------------------------------------                     W",  // 3
		"W                                                                             W",  // 4
		"W          in which battle the normans conquered england?                     W",  // 5
		"W                                                                             W",  // 6
		"W            1. the battle of cannae  - press A                               W",  // 7
		"W                                                                             W",  // 8
		"W            2. the battle of pavia - press B                                 W",  // 9
		"W                                                                             W",  // 10
		"W            3. the battle of the somme - press C                             W",  // 11
		"W                                                                             W",  // 12
		"W            4. the battle of hastings - press D                              W",  // 13
		"W                                                                             W",  // 14
		"W                                                                             W",  // 15
		"W                                                                             W",  // 16
		"W                                                                             W",  // 17
		"W                                                                             W",  // 18
		"W                                                                             W",  // 19
		"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",  // 20
		"                                                                               ",  // 21
		"                                                                               ",  // 23
		"                                                                               ",  // 22
		"                                                                               "
	};

	const char riddle2[Screen::MAX_Y][Screen::MAX_X] = {
		"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 0
		"W                                                                             W",  // 1
		"W                            RIDDLE NUMBER 2:                                 W",  // 2
		"W                ----------------------------------------                     W",  // 3
		"W                                                                             W",  // 4
		"W             what is the name of the sword of king arthur                    W",  // 5
		"W                                                                             W",  // 6
		"W            1. Joseph Shlomi  - press A                                      W",  // 7
		"W                                                                             W",  // 8
		"W            2. the dwarf's slayer - press B                                  W",  // 9
		"W                                                                             W",  // 10
		"W            3. excalibur - press C                                           W",  // 11
		"W                                                                             W",  // 12
		"W            4. amir hetsroni  - press D                                      W",  // 13
		"W                                                                             W",  // 14
		"W                                                                             W",  // 15
		"W                                                                             W",  // 16
		"W                                                                             W",  // 17
		"W                                                                             W",  // 18
		"W                                                                             W",  // 19
		"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",  // 20
		"                                                                               ",  // 21
		"                                                                               ",  // 22
		"                                                                               ",  // 23

	};
	for (int y = 0; y < Screen::MAX_Y; y++) {
		for (int x = 0; x < Screen::MAX_X; x++) {
			levels[0][y][x] = level0[y][x];
			levels[1][y][x] = level1[y][x];
			levels[2][y][x] = level2[y][x];
		}
	}
	for (int y = 0; y < Screen::MAX_Y; y++) {
		for (int x = 0; x < Screen::MAX_X; x++) {
			riddles_chars[0][y][x] = riddle1[y][x];
			riddles_chars[1][y][x] = riddle2[y][x];
		}
	}

	current_riddle = Screen(riddles_chars[currentLevel]);
	screen = Screen(levels[currentLevel]); 
	gameMenu = Screen(opening);
	instructions = Screen(instructionsScreen);
	pauseScreen = Screen(pauseMenu);
	press_switches = 0;
	riddles[0] = Riddle('D');
	riddles[1]= Riddle('C') ;
}

void Game::run()
{
	constexpr char ESC = 27;
	char key = 0;
	bool running = true;
	bool clearPass;
	bool solved_Riddele = false;
	hideCursor();
	cls();
	char next1 = ' ';
	char next2 = ' ';
	screen.drawRoom();
	Point old_place = { 1,1,Direction::directions[Direction::STAY], ' ' };
	bool wrong;


	while (running)
	{


		while (_kbhit())
		{
			key = _getch();


			if (key == ESC)
			{

				bool result = pauseMenu();
				if (result)
				{
					running = false;
					return;
				}
				else if (!result)
				{
					cls();
					screen.drawRoom();

					key = 0;
					continue;
				}
			}
			if (tolower(key) == 'e' && p1.isFullInventory())  
			{
				p1.drop_item(p1.getPoint(), screen);
				continue;    
			}

			
			if (tolower(key) == 'o' && p2.isFullInventory())
			{
				p2.drop_item(p2.getPoint(), screen);
				continue;
			}

			p1.keyPressed(key);
			p2.keyPressed(key);
		}

		clearPass = switchesOn(screen) && ((p1.getinventory() == 'K') || (p2.getinventory() == 'K'))&&solved_Riddele;
		Point prev_p1 = p1.getPoint();
		Point prev_p2 = p2.getPoint();
		Point next_p1 = prev_p1;
		next_p1.move();

		if(screen.isObstacle(next_p1)||(screen.isObstacle(p2.getPoint())))
		{
			Point arr[80];
			Push(screen, arr, p1);
		

		}
		bool move_p1 = p1.move_player_(screen, clearPass, next1);
		bool move_p2 = p2.move_player_(screen, clearPass, next2);

		if ((move_p1) && ((screen.isPlatform_on(prev_p1)) || (screen.isPlatform_off(prev_p1))))
		{
			char c = screen.charAt(prev_p1);
			Point switch_point(prev_p1.getX(), prev_p1.getY(), Direction::directions[Direction::STAY], c);
			on_or_off_switch(switch_point, screen);
		}


		if ((move_p2) && ((screen.isPlatform_on(prev_p2)) || (screen.isPlatform_off(prev_p2))))
		{
			char c = screen.charAt(prev_p2);
			Point switch_point(prev_p2.getX(), prev_p2.getY(),
				Direction::directions[Direction::STAY], c);
			on_or_off_switch(switch_point, screen);
		}
		if (next1 == '?')
		{
			
			wrong = true;
			while (p1.getlifePoint() > 0 && (wrong))
			{
				
				p1.freeze();
				p2.freeze();
				cls();
				current_riddle.drawRoom();
				screen.drawStatus(p1, p2);
				wrong = riddle_answers(riddles[currentLevel], p1);
			}
			if(p1.getlifePoint() == 0)
			{
				
				return;
			}
			solved_Riddele = true;
			screen.setChar(p1.getPoint(), ' ');
			next1 = ' ';
			cls();
			screen.drawRoom();
			p1.draw_player();
			p2.draw_player();
		}
		if (next2 == '?')
		{	

			wrong = true;
			while (p2.getlifePoint() > 0 && (wrong))
			{

				p1.freeze();
				p2.freeze();
				cls();
				current_riddle.drawRoom();
				screen.drawStatus(p1, p2);
				wrong = riddle_answers(riddles[currentLevel], p2);
			}
			if (p2.getlifePoint() == 0)
			{

				return;
			}
			solved_Riddele = true;
			screen.setChar(p2.getPoint(), ' ');
			next2 = ' ';
			cls();
			screen.drawRoom();
			p1.draw_player();
			p2.draw_player();
		}
		
		screen.drawStatus(p1, p2);
		clearPass = switchesOn(screen) && ((p1.getinventory() == 'K') || (p2.getinventory() == 'K'))&&solved_Riddele;
		if ((screen.isDoor(p1.getPoint()) && clearPass) || ((screen.isDoor(p2.getPoint()) && clearPass)))
		{

			if (currentLevel + 1 < NUMLEVELS)
			{

				enterRoom();
			}
			else
			{
				running = false;
				break;
			}
		}
		Sleep(200);
	}

}
	
void Game::moveLevel(int index)
{
	currentLevel = index;
	screen = Screen(levels[index]);
	cls();
	screen.drawRoom();
	p1.setPoint(2, 2, Direction::directions[Direction::STAY]);
	p2.setPoint(3, 3, Direction::directions[Direction::STAY]);
}


void Game::Menu()
{
	bool gameOver = false;
	while(!gameOver)
	{
		cls();
		gameMenu.drawRoom();
		char choice = _getch();
		switch (choice)
		{
		case '1':
			hideCursor();
			resetGame();
			run();
			//pausescreen
			break;
		case '8':
			cls();
			instructions.drawRoom();
			_getch();
			break;


		case '9':
			cls();
			return;

		}
	}
	
		
}
bool Game::pauseMenu()
{
	
	pauseScreen.drawRoom();
	char choice = _getch();
	switch(choice)
	{
	case 'h':
	case 'H':
		return true;
	case 27:
		return false;
	default:
		return false;
	}

	

}


void Game::on_or_off_switch(Point& p, Screen& s)
{
	
	char c = p.getChar();

	if (c == '/')
	{
		press_switches++;
		screen.setChar(p, '\\');
		p.draw('\\');
		
	}
	else if (c == '\\')
	{
		press_switches--;
		screen.setChar(p, '/');
	    p.draw('/');
		
	}

}
bool Game:: switchesOn(Screen& screen)
{
	if(press_switches==screen.get_switch_counters())
	{
		return true;
	}
	return false;

}
void Game:: enterRoom()
{
	if(switchesOn(screen))
	{
		if ((p1.getItem() == 'K') || (p2.getItem() == 'K'))
		{
			p1.drop_item(p1.getPoint(), screen);
			cls();
			moveLevel(currentLevel + 1);
			current_riddle = Screen(riddles_chars[currentLevel ]);
			screen.drawRoom();
		}
	}
	
}


bool Game::riddle_answers(Riddle r,Player& p)
{
	
	
	char answer = _getch();
	answer = toupper(answer);


	if (answer == r.getAnswer())
	{
		return false;
	}
	else
	{
		int new_points = p.getlifePoint()-1;
		p.setLifePoints(new_points);
		//printmesege("Worng answer!")
		return true;

	}
}
void Game::resetGame()
{
	currentLevel = 0;
	screen = Screen(levels[currentLevel]);
	current_riddle = Screen(riddles_chars[currentLevel]);
	press_switches = 0;

	p1.setPoint(1, 1, Direction::directions[Direction::STAY]);
	p2.setPoint(2, 2, Direction::directions[Direction::STAY]);

	p1.setLifePoints(3);  
	p2.setLifePoints(3);
}
bool Game::Push(Screen& screen, Point arr[],Player& p)
{
	Point obs = p.getPoint();
	obs.move();
	int obs_size = screen.obstacle(obs, arr);

	if (p.getPower() < obs_size)
		return false;

	
	Direction dir = obs.getDirection(); 
	int dx = dir.getdirx(); 
	int dy = dir.getdiry();

	
	for (int i = 0; i < obs_size; i++)
	{
		int new_x = arr[i].getX() + dx;
		int new_y = arr[i].getY() + dy;


		if (new_x < 0 || new_x >= Screen::MAX_X ||
			new_y < 0 || new_y >= Screen::MAX_Y)
			return false;

		
		Point dest(new_x, new_y,
			Direction::directions[Direction::STAY], ' ');

		char c = screen.charAt(dest);

		
		if (c == 'W' || (c >= '1' && c <= '4'))
			return false;
	
	}

	
	for (int i = 0; i < obs_size; i++)
	{
		screen.setChar(arr[i], ' ');
	}

	
	for (int i = 0; i < obs_size; i++)
	{
		int new_x = arr[i].getX() + dx;
		int new_y = arr[i].getY() + dy;

		arr[i].setX(new_x);
		arr[i].setY(new_y);

		Point dest(new_x, new_y,
			Direction::directions[Direction::RIGHT], '*');
		screen.setChar(dest, '*');
	}

	return true;
}

bool Game::pushing_together(Player& p1,Player& p2, Point arr1[],Point arr2[])
{
	Point obs1 = p1.getPoint();
	obs1.move();
	Point obs2 = p2.getPoint();
	obs2.move();
	if (p1.getPoint().getDirection() != p2.getPoint().getDirection()) return false;
	if (screen.isObstacle(obs1) && screen.isObstacle(obs2))
	{
		int size1 = screen.obstacle(p1.getPoint(), arr1);
		int size2 = screen.obstacle(p2.getPoint(), arr2);
		Point check = p1.getPoint();

		for (int i = 0; i < size1; i++)
		{
			if (check == arr2[i])
			{
				int combine = p1.getPower() + p2.getPower();
				p1.setPower(combine);
				p2.setPower(combine);
				return true;
			}
		
		}
		stopPower(p1, p2);
		return false;
	}
	return false;
}
void Game::stopPower(Player& p1,Player& p2)
{
	p1.setPower(1);
	p2.setPower(1);
}