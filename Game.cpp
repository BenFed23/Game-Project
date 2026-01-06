#include "Game.h"
#include <conio.h>
#include "Screen.h"
#include <Windows.h>
#include "utils.h"
#include <iostream>
#include "Riddle.h"
#include "Circle.h"
using namespace std;


Game::Game() : currentLevel(0), p1('$', 1, 1, "wdxas", 'e'), p2('&', 2, 2, "ilmjk", 'o')
{
  

    
    fileToLevel("adv-world_menu.screen", gameMenu);
    fileToLevel("adv-world_pause.screen", pauseScreen);
    fileToLevel("adv-world_indructions.screen", instructions);
    std::vector<std::string> levelFiles = 
    {
    "adv-world_01.screen",
    "adv-world_02.screen",
    "adv-world_03.screen"
    };

    std::vector<std::string> riddleFiles = 
    {
        "adv-world_01.riddle",
        "adv-world_02.riddle"
    };
    for (size_t i = 0; i < levelFiles.size(); ++i)
    {
        savedlevels.push_back(Screen(levelFiles[i]));
        if(i==1)
        {
            savedlevels[i].changeDarkMode(true);
        }
        pressSwitches.push_back(0);
        levelUnlocked.push_back(false);
    }
    for (size_t i = 0; i < riddleFiles.size(); ++i)
        fileToArray(riddleFiles[i], riddles_chars[i]);
    screen = savedlevels[0];
    levelUnlocked[0] = true;
    current_riddle = Screen(riddles_chars[currentLevel]);
    riddles[0] = Riddle('D');
    riddles[1] = Riddle('C');
}

void Game::run()
{
	game_Cycles = 0;
    constexpr char ESC = 27;
    char key = 0;
    bool running = true;
    bool clearPass;
    p1canpass = false;
    p2canpass = false;
    solved_Riddle = false;
    bool wrong;
    isGameOver = false;
    hideCursor();
    cls();
    Player* lastPlayerToExit = nullptr; // Track the last player who exited the room
	moveLevel(0);
    screen.drawRoom();
    //screen.debugShowAllSprings();
    Player* lastPlayerToExit = nullptr;
    drawCurrentRoom();


    while (running && !isGameOver)
    
    while ((running)&&(!isGameOver))
    {
        

        if (p1.getRoom() != currentLevel && p2.getRoom() != currentLevel && lastPlayerToExit != nullptr)
        {
            moveLevel(lastPlayerToExit->getRoom());
            if (isGameOver) break;
            current_riddle = Screen(riddles_chars[currentLevel], false, true);
            solved_Riddle = false;
            lastPlayerToExit = nullptr;
        }
        if (_kbhit())
        {
            key = _getch();
            if (key == ESC)
            {
                bool result = pauseMenu();
                if (result) return; 
                else 
                {
                    cls();
                    drawCurrentRoom();
                    key = 0;
                    continue;
                }
            }
            if (p1.getRoom() == currentLevel) //if player1 is in the room, the keys are available
                p1.keyPressed(key);
            if (p2.getRoom() == currentLevel) //if player2 is in the room, the keys are available
                p2.keyPressed(key);
        }

        bool envReady = solved_Riddle && switchesOn(screen);
        bool hasKey= (p1.getinventory() == 'K') || (p2.getinventory() == 'K');
       

        p1canpass = envReady&&hasKey;
        p2canpass = envReady && hasKey;

        Point prev_p1 = p1.getPoint();
        Point prev_p2 = p2.getPoint();

		
        if (p1.getRoom() == currentLevel)
        {
            if (p1.isInBoost())
            {
                handle_flying_movement(p1, p2, p1canpass, key);
            }
            else
            {
                handleInteraction(p1, prev_p1, key);
                if (isGameOver)
                    break;
                handle_pre_spring_movement(p1, p2, p1canpass);


                /*if (enterRoom(p1))
                {
                    lastPlayerToExit = &p1;
                    gotoxy(prev_p1.getX(), prev_p1.getY()); std::cout << ' ';
                    p1.setInventory('E');
                }*/
               

                bool movedP1 = enterRoom(p1);

               

                if (movedP1)
                {
                    lastPlayerToExit = &p1;
                    gotoxy(prev_p1.getX(), prev_p1.getY());
                    std::cout << ' ';
                    if(p1.getinventory()=='K')
                    {
                        p1.setInventory('E');
                    }
                   
                }

            }
        }
        if (p2.getRoom() == currentLevel)
        {
            if (p2.isInBoost())
            {
                handle_flying_movement(p2, p1, p2canpass, key);
            }
            else
            {
                handleInteraction(p2, prev_p2, key);
                if (isGameOver)
                    break;
                handle_pre_spring_movement(p2, p1, p2canpass);


                bool movedP2 = enterRoom(p2);



                if (movedP2)
                {
                    lastPlayerToExit = &p2;
                    gotoxy(prev_p2.getX(), prev_p2.getY()); std::cout << ' ';
                    if (p2.getinventory() == 'K')
                    {
                        p2.setInventory('E');
                    }
                }
            }
        }
        Bomb_explosion_logic(p1_activeBomb);
        Bomb_explosion_logic(p2_activeBomb);


                    gotoxy(prev_p2.getX(), prev_p2.getY());
                    std::cout << ' ';
                    if (p2.getinventory() == 'K')
                    {
                        p2.setInventory('E');
                    }
                }
            }
        }
      
        //cls();
        drawCurrentRoom();

        if (p1.getRoom() == currentLevel && !screen.isDoor(p1.getPoint()))
        {
            p1.draw_player();
        }

        if (p2.getRoom() == currentLevel && !screen.isDoor(p2.getPoint()))
        {
            p2.draw_player();
        }

        screen.drawStatus(p1, p2);

		game_Cycles++;
        key = 0;
        Sleep(100);
    }
}

void Game::moveLevel(int new_level)
{
  
    savedlevels[currentLevel] = screen;
    pressSwitches[currentLevel] = press_switches;

  
    currentLevel = new_level;

  
    screen = savedlevels[currentLevel];
    std::cout << "copied: saved=" << savedlevels[currentLevel].isDarkRoom()
        << " screen=" << screen.isDarkRoom() << "\n";

    press_switches = pressSwitches[currentLevel];

  
void Game::moveLevel(int index)
{
    currentLevel = index;
    try
    {
        screen = Screen(levels[index]);
        Point legendPos = screen.getLegendPos();
        int legendPos_Y = legendPos.getY(); 

        if (legendPos_Y > 1 && legendPos_Y <= 20)
        {
            cls();
            gotoxy(20, 8);
            cerr << "Warning: Legend in center! Objects in this area were removed." << endl;
			gotoxy(20, 10);
            cerr << "This might make the level unplayable due to deleted items." << endl;
			gotoxy(20, 13); 
            cout << "Press 1 to continue with Legend in center." << endl;
			gotoxy(20, 15);
			cout << "Press 2 to move Legend automatically to bottom." << endl;
            char choice = _getch();
            if (choice == '2') 
            {
                screen = Screen(levels[index], false);

                screen.setLegendPos(Point(0, 21)); //moving the legend to the bottom


            }
            else  if (choice == '1')//then we adjust players position
            {
                adjust_player_positions_acc_to_L(legendPos_Y);
            }
        }
        else if(legendPos_Y > 21) //legend is already at the bottom
        {
            gotoxy(20, 12);
            cerr << "Warning: Legend is too low! unable to play the game." << endl;
            gotoxy(20, 15);
            cout << "\npress 2 to Move Legend automatically to bottom. else - you must change the location of the legend to play." << endl;
            char choice = _getch();
            if (choice == '2')
            {
                screen = Screen(levels[index], false);

                screen.setLegendPos(Point(0, 21)); //moving the legend to the bottom


            }
			else //then we end the game and go to main menu
            {
				this->isGameOver = true;
				return;
            }
        }
        else if (legendPos_Y == 1) //legend is at the top
        {
            gotoxy(20, 9);
            cerr << "Warning: Legend is at the top. items might be deleted." << endl;
            gotoxy(20, 12);
            cout << "press 1 to keep the legend at the top." << endl;
            gotoxy(20, 13);
            cout << "press 2 to Move Legend automatically to bottom." << endl;
            char choice = _getch();
            if (choice == '2')
            {
                screen = Screen(levels[index], false);
            }
            else if (choice == '1')
            {
                adjust_player_positions_acc_to_L(legendPos_Y);
			}
		}
        else if (legendPos_Y == 0)
        {
            gotoxy(20, 9);
            cerr << "Warning: Legend is outside game borders." << endl;
            gotoxy(20, 12);
            cout << "press 1 to return to main menu and then change the L location." << endl;
            gotoxy(20, 13);
            cout << "press 2 to Move Legend automatically to bottom." << endl;
            char choice = _getch();
            if (choice == '2')
            {
                screen = Screen(levels[index], false);
            }
            else if (choice == '1')
            {
                this->isGameOver = true;
                return;
            }
        }
        else 
        {
            adjust_player_positions_acc_to_L(legendPos_Y);
		}
    }
    catch (...)
    {
        cerr << "Problem loading level " << index << endl;
    }
    if(isGameOver)
		return;
       
    cls();
    p1.setPoint(2, 2, Direction::directions[Direction::STAY]);
    p2.setPoint(3, 3, Direction::directions[Direction::STAY]);
    drawCurrentRoom();
    screen.drawRoom();
    press_switches = 0;
    solved_Riddle = false;

    p1_activeSpring = nullptr;
    p2_activeSpring = nullptr;
    p1.setPower(1);
    p2.setPower(1);
}

void Game::Menu()
{
    bool gameOver = false;
    while (!gameOver)
    {
        cls();
        gameMenu.drawRoom();
        char choice = _getch();
        switch (choice) {
        case '1':
            hideCursor();
            resetGame();
            run();
            break;
        case '8':
            cls();
            instructions.drawRoom();
            _getch();
            break;
        case '9':
            cls();
            gameOver = true;
            break;
        }
    }
}

bool Game::pauseMenu()
{
    pauseScreen.drawRoom();
    char choice = _getch();
    switch (choice)
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
    char currentContext = s.charAt(p);
    if (currentContext == '/') {
        pressSwitches[currentLevel]++;
        s.setChar(p, '\\');
    }
    else if (currentContext == '\\') {
        pressSwitches[currentLevel]--;
        s.setChar(p, '/');
    }
}

bool Game::switchesOn(Screen& screen) {
    return   pressSwitches[currentLevel] == screen.get_switch_counters();
}

bool Game::enterRoom(Player& p)
{
    Point pos = p.getPoint();
    char target = screen.charAt(pos);

    if (screen.isDoor(pos))
    {
        gotoxy(pos.getX(), pos.getY());
        std::cout << target;


        int nextRoomIndex = target - '0';
        p.setRoom(nextRoomIndex);

        if (&p == &p1)
        {
            p.setPoint(levelStarts[nextRoomIndex].p1_x, levelStarts[nextRoomIndex].p1_y, Direction::directions[Direction::STAY]);
        }
        else
        {
            p.setPoint(levelStarts[nextRoomIndex].p2_x, levelStarts[nextRoomIndex].p2_y, Direction::directions[Direction::STAY]);
        }
        levelUnlocked[currentLevel] = true;
        p.setPower(1);
        return true;

    }
    return false;
}

bool Game::riddle_answers(Riddle r, Player& p)
{
    char answer = _getch();
    answer = toupper(answer);
    if (answer == r.getAnswer())
    {
        gotoxy(18, 18);
        std::cout << "RIGHT ANSWER! GOOD JOB";
		solved_Riddle = true;
        Sleep(1500);

        return false;
    }
    else
    {
        p.setLifePoints(p.getlifePoint() - 1);
        if (p.getlifePoint() != 0) 
        {
            gotoxy(17, 18);
            std::cout << "Wrong answer! Life points left: " << p.getlifePoint();
            Sleep(1500);
            return true;
        }
        else
        {
            gotoxy(17, 18);
            std::cout << "WRONG ANSWER, GAME OVER!!!!!!!!";
			Sleep(1500);
			return true;
        }
    
    }
}

void Game::resetGame()
{
    currentLevel = 0;
    //screen = Screen(levels[currentLevel]);
    //current_riddle = Screen(riddles_chars[currentLevel]);
    press_switches = 0;
    p1.setPoint(1, 1, Direction::directions[Direction::STAY]);
    p1.setInventory('E');
    p1.setLifePoints(3);
    p1.setRoom(0);
    p1.setPower(1);
	p1.setStepChar(' ');
    p2.setPoint(2, 2, Direction::directions[Direction::STAY]);
    p2.setInventory('E');
    p2.setLifePoints(3);
    p2.setRoom(0);
    p2.setPower(1);
    p2.setStepChar(' ');


}

bool Game::Push(Screen& screen, Player& p, int bonus_power)
{
    Point next_point = p.getPoint().next();
    std::vector<Point> obstacle = screen.getObstacleVector(next_point);

    if (obstacle.empty()) return false;
    if (p.getPower() + bonus_power < (int)obstacle.size()) return false;

    Direction dir = p.getdirection();
    int dx = dir.getdirx();
    int dy = dir.getdiry();

    for (const auto& part : obstacle) {
        int nx = part.getX() + dx;
        int ny = part.getY() + dy;
        if (nx < 0 || nx >= Screen::MAX_X || ny < 0 || ny >= Screen::MAX_Y) return false;
        Point check_point(nx, ny, Direction::directions[Direction::STAY], ' ');
        char target = screen.charAt(check_point);
        if (target != ' ' && target != '*') return false;
        if (target == 'W') return false;
    }

    for (const auto& part : obstacle) screen.setChar(part, ' ');
    for (const auto& part : obstacle) {
        Point dest(part.getX() + dx, part.getY() + dy, dir, '*');
        screen.setChar(dest, '*');
    }
    return true;
}

bool Game::pushing_together(Player& p1, Player& p2, Screen& screen) {
    if (p1.getdirection() != p2.getdirection()) return false;
    std::vector<Point> obstacle = screen.getObstacleVector(p1.getPoint().next());
    if (obstacle.empty()) return false;
    Point nextP2 = p2.getPoint().next();
    if (screen.isPointPartOfObstacle(obstacle, nextP2)) {
        return Push(screen, p1, p2.getPower());
    }
    return false;
}

void Game::stopPower(Player& p1, Player& p2) {
    p1.setPower(1);
    p2.setPower(1);
}

void Game::handleMovement(Player& p, Player& other, bool clearPass) //handling the movement of player p, considering other player and if can pass doors
{
    Point nextPos = p.getPoint().next();
    char target = screen.charAt(nextPos);
    bool canMove = true;
    char charToStepOn = ' ';
    char ch = p.getStepChar();


    if (screen.isWall(nextPos))
    {
        canMove = false;
    }
  
    else if (screen.isDoor(nextPos))
    {
        int targetRoom = screen.charAt(nextPos) - '0';

       
        if (targetRoom < 0 || targetRoom >= (int)levelUnlocked.size())
        {
            canMove = false;
        }
        else if (targetRoom > currentLevel)
        {
            
            if (!levelUnlocked[targetRoom] && !clearPass)
                canMove = false;
        }
        
    }


    else if (target == '*')
    {
        Point otherNext = other.getPoint().next();
        if (nextPos == otherNext)
        {
            int dxP = p.getdirection().getdirx();
            int dyP = p.getdirection().getdiry();
            int dxO = other.getdirection().getdirx();
            int dyO = other.getdirection().getdiry();
            if ((dxP == -dxO && dxP != 0) || (dyP == -dyO && dyP != 0)) canMove = false;
        }
        if (canMove)
        {
            if (pushing_together(p, other, screen) || Push(screen, p)) charToStepOn = ' ';
            else canMove = false;
        }
    }


    else
    {
        canMove = true;
        charToStepOn = target;
    }

    if (p.move_player_(screen, canMove, charToStepOn))
    {
        char step_char = p.getStepChar();
        if (step_char == 'K' || step_char == '@' || step_char == '!')
        {
            bool is_player2_has_key = false;
            if (!p.isFullInventory())
            {
                if (p == p2 && step_char == 'K')
                {
                    is_player2_has_key = true;
                }

                p.pick_item(screen, charToStepOn);
                p.setStepChar(' ');


                p.set_justpicked(true);
               
            }
        }
    }
}
/*void Game::boom(Circle c, Screen& screen)
{
    int startX = max(0, c.getCenter().getX() - c.getRadius());
    int endX = min(Screen::MAX_X - 4, c.getCenter().getX() + c.getRadius());

    int startY = max(0, c.getCenter().getY() - c.getRadius());
    int endY = min(Screen::MAX_Y - 4, c.getCenter().getY() + c.getRadius());


    Point pc = c.getCenter();
    for (int i=startY;i<=endY;i++)
    {
        for (int j = startX; j <=endX; j++)
        {
            Point p(j, i);
           
            if(pc.distance(p)<=c.getRadius())
            {
                if(!screen.antiBoom(p))
                {
                    if (c.inRange(p) && p == p1.getPoint())
                    {
                    
                            p1.setLifePoints(p1.getlifePoint() - 1);
                    }
                    else if(c.inRange(p) && p == p2.getPoint())
                    {
                            p2.setLifePoints(p2.getlifePoint() - 1);
                    }
                    
                    else
                    {
                        screen.setChar(p, ' ');

                    }
                 
                }
               
            }
        }
    }
}*/
void Game::boom(Circle c, Screen& screen)
{
    int startX = max(0, c.getCenter().getX() - (int)c.getRadius());
    int endX = min(Screen::MAX_X - 1, c.getCenter().getX() + (int)c.getRadius());
    int startY = max(0, c.getCenter().getY() - (int)c.getRadius());
    int endY = min(Screen::MAX_Y - 1, c.getCenter().getY() + (int)c.getRadius());

    for (int i = startY; i <= endY; i++)
    {
        for (int j = startX; j <= endX; j++)
        {
            Point p(j, i);

            if (c.inRange(p))
            {
                if (p == p1.getPoint())
                {
                    p1.setLifePoints(p1.getlifePoint() - 1);
                }
                if (p == p2.getPoint())
                {
                    p2.setLifePoints(p2.getlifePoint() - 1);
                }

                if (!screen.antiBoom(p))
                {
                    screen.setChar(p, ' ');

                    gotoxy(p.getX(), p.getY());
                    std::cout << ' ';
                }
            }
        }
    }
    p1.draw_player();
    p2.draw_player();
}
bool Game::fileToArray(const std::string& filename, char dest[Screen::MAX_Y][Screen::MAX_X])
{
    Screen temp(filename);
    const char (*p)[Screen::MAX_X] = temp.getScreen();

    for (int y = 0; y < Screen::MAX_Y; ++y)
    {
        for (int x = 0; x < Screen::MAX_X; ++x)
        {
            dest[y][x] = p[y][x];
            
        }
    }

    return true;
}

bool Game::fileToLevel(const std::string& filename, Screen& target)
{
    target = Screen(filename);
    return true;
}
void Game::handleInteraction(Player& p, Point point, char drop_key_press) //handleing interactions after movement
{
    char currentTile = p.getStepChar();


    if (screen.isPlatform_on(point) || screen.isPlatform_off(point))
    {
        on_or_off_switch(point, screen);
    }

    if (currentTile == '?')
    {
        if (!executeRiddle(p))
        {
            this->isGameOver = true;
            return;
        }
    }
    if (drop_key_press != 0 && (&p == &p1 && drop_key_press == 'e') || (&p == &p2 && drop_key_press == 'o'))
    {
        char itemInHand = p.getinventory();
        if (p.isFullInventory())
        {
            if (p.getinventory() == '@')
            {
                if(p.getdirection()==Direction::directions[Direction::STAY])
                {
                    Point bombCenter = p.getPoint();
                    Direction d = p.getdirection();
                    bombCenter.changeDir(d);
                    for (int i = 0; i < 4; i++)
                    {
                        Point next = bombCenter;
                        next.move();

                        if (screen.isWall(next) || (screen.isObstacle(next)) || screen.isSpring(next))
                            break;
                        gotoxy(bombCenter.getX(), bombCenter.getY());
                        std::cout << '@';
                        p1.draw_player();
                        p2.draw_player();


                        gotoxy(bombCenter.getX(), bombCenter.getY());
                        std::cout << ' ';

                        bombCenter = next;
                    }
                    bombCenter.setChar(' ');
                    bombCenter.draw();
                    Circle c = { 4, bombCenter };
                    //p.drop_item(bombCenter, screen);

                    if (&p == &p1)
                    {
						p1.setInventory('E');
                        p1_activeBomb = new BOMB(bombCenter);
                    }
                    else
                    {
                        p2.setInventory('E');
						p2_activeBomb = new BOMB(bombCenter);
                    }
                    /*Circle c = {4, bombCenter};
                    boom(c, screen);
                    bombCenter.draw(' ');
                    p.setInventory('E');
                    */
                   
                

            }
            else
            {
                p.drop_item(p.getPoint(), screen);
                p.setStepChar(itemInHand);
            }
        }
    }
    p.set_justpicked(false);
}
Spring* Game::getSpringAt(const Point& p) //find the spring at point p
{
    std::vector<Spring>& levelSprings = screen.getSprings();
    for (auto& spring : levelSprings) //moving through all springs in the level
    {
        if (spring.isPointOnSpring(p))
        {
            return &spring; //return the right spring
        }
    }
    return nullptr;
}
Direction Game::check_Spring_direction(Spring* spring)
{

    const std::vector<Point>& locations = spring->getLocations();

    for (const auto& pt : locations)
    {
        if (pt.getX() == 1)  return Direction::directions[Direction::RIGHT];
        if (pt.getX() == 77) return Direction::directions[Direction::LEFT];
        if (pt.getY() == 1)  return Direction::directions[Direction::DOWN];
        if (pt.getY() == 19) return Direction::directions[Direction::UP];
    }
    return Direction::directions[Direction::STAY];

}
bool Game::match_directions(Spring* spring, Player& p) //checking if player direction matches spring release direction
{
    spring->setReleaseDir(check_Spring_direction(spring));//setting the spring release direction according to its position in the level
    return spring->opposite(p.getdirection());//checking if the player is moving against the spring direction
}

bool Game::compressed(Player& p, Spring* spring)
{
    if (spring->compress())
    {
        p.getPoint().draw(' ');

        p.setStepChar(' ');

        return true;
    }
    return false;
}
bool Game::executeRiddle(Player& p)
{
	Point original_legendPos = screen.getLegendPos();
    
	current_riddle.setLegendPos(Point(0,22));
	screen.setLegendPos(Point(0, 21));
    bool wrong = true;
    p1.freeze();
    p2.freeze();

    while (p.getlifePoint() > 0 && wrong)
    {
        current_riddle.drawRoom();
        screen.drawStatus(p1, p2);
        wrong = riddle_answers(riddles[currentLevel], p);
    }

    if (p.getlifePoint() > 0)
    {
        solved_Riddle = true;
        screen.setChar(p.getPoint(), ' ');
        p.setStepChar(' ');
        screen.setLegendPos(original_legendPos);
        cls();
        screen.drawRoom();
        p1.draw_player();
        p2.draw_player();
        return true; //the riddle is solved

    }

    return false; // the player is dead and the game is over
}
void Game::handle_flying_movement(Player& p, Player& other, bool canPass, char key)//the situation after spring release 
{
    p.setDirection(p.getBoostDir());

    for (int j = 0; j < p.get_boostSpeed(); j++)
    {
        Point nextPosP = p.getPoint().next();
        Point prev_pos = p.getPoint();
        handleMovement(p, other, canPass);

        if (nextPosP == other.getPoint())
        {
            other.setDirection(p.getdirection());

            handleMovement(other, p, true);
        }
        handleInteraction(p, prev_pos, key);
    }

    p.reduceBoost();

    if (!p.isInBoost())
    {
        p.resetBoost();
    }
}
void Game::release_spring(Player& p, Spring* spring, Screen& screen)//setting the ground for the player boost after spring release, and creating the spring release
{
    int speed, game_cycles;
    spring->releaseSpring(speed, game_cycles);

    Direction boostDir = spring->getReleaseDir();

    p.startLaunch(speed, game_cycles, boostDir);
    p.setPower(1 + speed);
    p.setDirection(boostDir);

    for (int j = 0; j < speed; j++)
    {
        if (&p == &p1)
        {
            handleMovement(p1, p2, p1canpass);
        }
        else
        {
            handleMovement(p2, p1, p2canpass);
        }
    }

    for (const auto& pt : spring->getLocations())
    {
        screen.setChar(pt, '#');
        gotoxy(pt.getX(), pt.getY());
        std::cout << '#';
    }
    p.draw_player();
    spring->setcurrentCompressed(0);

}
void Game::handle_pre_spring_movement(Player& p, Player& other, bool canPass) //regular movement handling before spring interaction
{


    Point currentPos = p.getPoint();
    Point nextPos = currentPos.next();

    Spring* s = getSpringAt(nextPos);
    if (s == nullptr) s = getSpringAt(currentPos);

    if (s != nullptr)
    {
        bool isCompressingKey = match_directions(s, p);

        if (isCompressingKey)
        {
            if (!s->isFullyCompressed())
            {
                if (compressed(p, s))
                {
                    p.draw_player();
                    Sleep(20);

                    handleMovement(p, other, canPass);
                }
            }
            else
            {
                release_spring(p, s, screen);
            }
        }
        else
        {
            int current_charge = s->getcurrentCompressed();
            if (current_charge > 0)
            {
                if (!(s->opposite(p.getdirection())))
                {
                    release_spring(p, s, screen);
                }
                else
                {
                    handleMovement(p, other, canPass);
                }
            }
            else
            {
                handleMovement(p, other, canPass);
            }
        }
    }
    else
    {
        handleMovement(p, other, canPass);
    }
}
void Game::drawDarkRoom( Screen& s,  Circle& light)
{
    for (int y = 0; y < Screen::MAX_Y; y++)
    {
        gotoxy(0, y);

        for (int x = 0; x < Screen::MAX_X; x++)
        {

            Point p(x, y);

            if (light.inRange(p) ||(s.isDoor(p)))
                std::cout << s.charAt(p);
            else
                p.draw();
        }
    }
}
void Game::drawCurrentRoom()
{
    if (screen.isDarkRoom())
    {
        
        if (p1.getinventory() == '!')
        {
            Circle light(TORCH_RADIUS, p1.getPoint());
            drawDarkRoom(screen, light);
        }
        else if (p2.getinventory() == '!')
        {
            Circle light(TORCH_RADIUS, p2.getPoint());
            drawDarkRoom(screen, light);
        }
        else
        {
           
        }
    }
    else
    {
        screen.drawRoom();
    }
}



}

void Game::adjust_player_positions_acc_to_L(int legendPos_Y)
{
    if (p1.getPoint().getY() >= legendPos_Y - 1 && p1.getPoint().getY() <= legendPos_Y + 3)
    {
        p1.setPoint(p1.getPoint().getX(), legendPos_Y + 4, Direction::directions[Direction::STAY]);
        p1.setStepChar(' ');
    }

    if (p2.getPoint().getY() >= legendPos_Y - 1 && p2.getPoint().getY() <= legendPos_Y + 3)
    {
        p2.setPoint(p2.getPoint().getX(), legendPos_Y + 4, Direction::directions[Direction::STAY]);
        p2.setStepChar(' ');
    }
}


void Game::Bomb_explosion_logic(BOMB*& activeBomb) //handling the bomb logic for player p
{
    if (activeBomb == nullptr) return; 

	if (activeBomb->update()) //the function that reduces the timer and returns true if the bomb is still active
    {
        int timeLeft = activeBomb->getTimer();
        Point pos = activeBomb->getPos();

        if (timeLeft > 0) 
        {
            gotoxy(pos.getX(), pos.getY());
            std::cout << timeLeft;
        }
        else 
        {

            boom(activeBomb->getCircle(), screen); //BANGGGGGGGGGG

            gotoxy(pos.getX(), pos.getY());
            std::cout << ' ';

			delete activeBomb; // Free the memory
            activeBomb = nullptr;
        }
    }
}