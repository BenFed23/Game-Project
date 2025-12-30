#include "Game.h"
#include <conio.h>
#include "Screen.h"
#include <Windows.h>
#include "utils.h"
#include <iostream>
#include "Riddle.h"
#include "Circle.h"

Game::Game() : currentLevel(0), p1('$', 10, 3, "wdxas", 'e'), p2('&', 10, 4, "ilmjk", 'o')
{
  

    
    fileToLevel("adv-world_menu.screen", gameMenu);
    fileToLevel("pause.screen", pauseScreen);
    fileToLevel("adv-world_indructions.screen", instructions);
    std::vector<std::string> levelFiles = {
    "adv-world_01.screen",
    "adv-world_02.screen",
    "adv-world_03.screen"
    };

    std::vector<std::string> riddleFiles = {
        "adv-world_01.riddle",
        "adv-world_02.riddle"
    };
    for (size_t i = 0; i < levelFiles.size(); ++i)
        fileToArray(levelFiles[i], levels[i]);

    for (size_t i = 0; i < riddleFiles.size(); ++i)
        fileToArray(riddleFiles[i], riddles_chars[i]);
    screen = Screen(levels[currentLevel]);
    current_riddle = Screen(riddles_chars[currentLevel]);
    press_switches = 0;
    riddles[0] = Riddle('D');
    riddles[1] = Riddle('C');
}

void Game::run() {
    constexpr char ESC = 27;
    char key = 0;
    bool running = true;
    bool clearPass;
    bool solved_Riddle = false;
    hideCursor();
    cls();

    screen.drawRoom();
    bool wrong;

    while (running) {
        if (_kbhit()) {
            key = _getch();
            if (key == ESC) {
                bool result = pauseMenu();
                if (result) return; 
                else {
                    cls();
                    screen.drawRoom();
                    key = 0;
                    continue;
                }
            }

            if (tolower(key) == 'e' && p1.getinventory()=='K') {
                char itemInHand1 = p1.getinventory();
                p1.drop_item(p1.getPoint(), screen);
                p1.setStepChar(itemInHand1);
                continue;
            }

            
            if (tolower(key) == 'o' && p2.getinventory()=='K') {
                char itemInHand2 = p2.getinventory();
                p2.drop_item(p2.getPoint(), screen);
                p2.setStepChar(itemInHand2);
                continue;
            }
           

            p1.keyPressed(key);
            p2.keyPressed(key);
        }

        clearPass = switchesOn(screen) && ((p1.getinventory() == 'K') || (p2.getinventory() == 'K')) && solved_Riddle;

        Point prev_p1 = p1.getPoint();
        Point prev_p2 = p2.getPoint();
        if (tolower(key) == 'e' && p1.getinventory() == '@')
        {
            if (p1.getdirection() == Direction::directions[Direction::STAY])
            {
                Point bombCenter = p1.getPoint();
                Direction d = p1.getdirection();
                bombCenter.changeDir(d);
                for (int i = 0; i < 4; i++)
                {
                    Point next = bombCenter;
                    next.move();


                    if (screen.isWall(next))
                        break;

                    bombCenter = next;
                }

                Circle  c = { 2,prev_p1 };
                p1.drop_item(p1.getPoint(), screen);
                boom(c, screen);
            }
               
        }
        if (tolower(key) == 'o' && p2.getinventory() == '@')
        {
            if (p2.getdirection() == Direction::directions[Direction::STAY])
            {
                Point bombCenter = p1.getPoint();
                Direction d = p1.getdirection();
                bombCenter.changeDir(d);
                for (int i = 0; i < 4; i++)   
                {
                    Point next = bombCenter;
                    next.move();

                   
                    if (screen.isWall(next))
                        break;

                    bombCenter = next;
                }

                Circle  c = { 3,prev_p1 };
                p2.drop_item(p2.getPoint(), screen);
                boom(c, screen);
            }

        }
        handleMovement(p1, p2, clearPass);
        handleMovement(p2, p1, clearPass);

       
        if (!(p1.getPoint() == prev_p1)) {
            if (screen.isPlatform_on(prev_p1) || screen.isPlatform_off(prev_p1)) {
                on_or_off_switch(prev_p1, screen);
            }
        }
        if (!(p2.getPoint() == prev_p2)) {
            if (screen.isPlatform_on(prev_p2) || screen.isPlatform_off(prev_p2)) {
                on_or_off_switch(prev_p2, screen);
            }
        }

        
        if (p1.getStepChar() == '?') {
            wrong = true;
            p1.freeze(); p2.freeze();
            while (p1.getlifePoint() > 0 && wrong) {
                cls();
                current_riddle.drawRoom();
                screen.drawStatus(p1, p2);
                wrong = riddle_answers(riddles[currentLevel], p1);
            }
            if (p1.getlifePoint() == 0) return;
            solved_Riddle = true;
            screen.setChar(p1.getPoint(), ' ');
            p1.setStepChar(' ');
            cls(); screen.drawRoom(); p1.draw_player(); p2.draw_player();
        }
        if (p2.getStepChar() == '?') {
            wrong = true;
            p1.freeze(); p2.freeze();
            while (p2.getlifePoint() > 0 && wrong) {
                cls();
                current_riddle.drawRoom();
                screen.drawStatus(p1, p2);
                wrong = riddle_answers(riddles[currentLevel], p2);
            }
            if (p2.getlifePoint() == 0) return;
            solved_Riddle = true;
            screen.setChar(p2.getPoint(), ' ');
            p2.setStepChar(' ');
            cls(); screen.drawRoom(); p1.draw_player(); p2.draw_player();
        }

        screen.drawStatus(p1, p2);

        if ((screen.isDoor(p1.getPoint()) || screen.isDoor(p2.getPoint())) && clearPass) {
            if (currentLevel + 1 < NUMLEVELS) enterRoom();
            else { running = false; break; }
        }

        Sleep(100);
    }
}

void Game::moveLevel(int index) {
    currentLevel = index;
    screen = Screen(levels[index]);
    cls();
    screen.drawRoom();
    p1.setPoint(2, 2, Direction::directions[Direction::STAY]);
    p2.setPoint(3, 3, Direction::directions[Direction::STAY]);
}

void Game::Menu() {
    bool gameOver = false;
    while (!gameOver) {
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
            return;
        }
    }
}

bool Game::pauseMenu() {
    pauseScreen.drawRoom();
    char choice = _getch();
    switch (choice) {
    case 'h':
    case 'H':
        return true;
    case 27:
        return false;
    default:
        return false;
    }
}

void Game::on_or_off_switch(Point& p, Screen& s) {
    char currentContext = s.charAt(p);
    if (currentContext == '/') {
        press_switches++;
        s.setChar(p, '\\');
    }
    else if (currentContext == '\\') {
        press_switches--;
        s.setChar(p, '/');
    }
}

bool Game::switchesOn(Screen& screen) {
    return press_switches == screen.get_switch_counters();
}

void Game::enterRoom() {
    if (switchesOn(screen)) {
        if ((p1.getinventory() == 'K') || (p2.getinventory() == 'K')) {
            p1.drop_item(p1.getPoint(), screen);
            cls();
            moveLevel(currentLevel + 1);
            current_riddle = Screen(riddles_chars[currentLevel]);
            screen.drawRoom();
        }
    }
}

bool Game::riddle_answers(Riddle r, Player& p) {
    char answer = _getch();
    answer = toupper(answer);
    if (answer == r.getAnswer()) {
        return false;
    }
    else {
        p.setLifePoints(p.getlifePoint() - 1);
        return true;
    }
}

void Game::resetGame() {
    currentLevel = 0;
    screen = Screen(levels[currentLevel]);
    current_riddle = Screen(riddles_chars[currentLevel]);
    press_switches = 0;
    p1.setPoint(1, 1, Direction::directions[Direction::STAY]);
    p2.setPoint(2, 2, Direction::directions[Direction::STAY]);
    p1.setLifePoints(3);
    p2.setLifePoints(3);
}

bool Game::Push(Screen& screen, Player& p, int bonus_power) {
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

void Game::handleMovement(Player& p, Player& other, bool clearPass) {
    Point nextPos = p.getPoint().next();
    char target = screen.charAt(nextPos);
    bool canMove = true;
    char charToStepOn = ' ';

    if (screen.isWall(nextPos))
    {
        canMove = false;
    }
    else if (screen.isDoor(nextPos) && !clearPass) {
        canMove = false;
    }
    else if (target == '*') {
        Point otherNext = other.getPoint().next();
        if (nextPos == otherNext) {
            int dxP = p.getdirection().getdirx();
            int dyP = p.getdirection().getdiry();
            int dxO = other.getdirection().getdirx();
            int dyO = other.getdirection().getdiry();
            if ((dxP == -dxO && dxP != 0) || (dyP == -dyO && dyP != 0)) canMove = false;
        }
        if (canMove) {
            if (pushing_together(p, other, screen) || Push(screen, p)) charToStepOn = ' ';
            else canMove = false;
        }
    }
    else {
        canMove = true;
        charToStepOn = target;
    }

    if (p.move_player_(screen, canMove, charToStepOn)) {
        char tile = p.getStepChar();
        if (tile == 'K' || tile == '@' || tile == '!') {
            if (!p.isFullInventory()) {
                p.pick_item(screen, tile);
                p.setStepChar(' ');
            }
        }
    }
}
void Game::boom(Circle c,Screen& screen)
{
    int startX = max(0, c.getCenter().getX() - c.getRadius());
    int endX = min(Screen::MAX_X - 4, c.getCenter().getX() + c.getRadius());

    int startY = max(0, c.getCenter().getY() - c.getRadius());
    int endY = min(Screen::MAX_Y - 4, c.getCenter().getY() + c.getRadius());


    Point pc = c.getCenter();
    for(int i=startY;i<=endY;i++)
    {
        for (int j = startX; j <=endX; j++)
        {
            Point p(j, i);
           
            if(pc.distance(p)<=c.getRadius())
            {
                if(!screen.antiBoom(p))
                {
                    if (screen.isPlayer(p))
                    {
                        if(p==p1.getPoint())
                        {
                            p1.setLifePoints(p1.getlifePoint() - 1);
                        }
                        else if(p == p2.getPoint())
                        {
                            p2.setLifePoints(p2.getlifePoint() - 1);
                        }
                    }
                    else
                    {
                        screen.setChar(p, ' ');

                    }
                 
                }
               
            }
        }
    }
}
bool Game::fileToArray(const std::string& filename,
    char dest[Screen::MAX_Y][Screen::MAX_X])
{
    Screen temp(filename);
    const char (*p)[Screen::MAX_X] = temp.getScreen();

    for (int y = 0; y < Screen::MAX_Y; ++y)
        for (int x = 0; x < Screen::MAX_X; ++x)
            dest[y][x] = p[y][x];

    return true;
}

bool Game::fileToLevel(const std::string& filename, Screen& target)
{
    target = Screen(filename);
    return true;
}

