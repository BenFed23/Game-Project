#include "Game.h"
#include <conio.h>
#include "Screen.h"
#include <Windows.h>
#include "utils.h"
#include <iostream>
#include "Riddle.h"

Game::Game() : currentLevel(0), p1('$', 1, 1, "wdxas", 'e'), p2('&', 2, 2, "ilmjk", 'o')
{

    const char level0[Screen::MAX_Y][Screen::MAX_X] =
    {
        "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                1                                            W",
        "W                                                   K                         W",
        "W                                                                             W",
        "W                                                                             W",
        "W                        ?                                                    W",
        "W                                                                             W",
        "W                                                               /             W",
        "W                                    2                                        W",
        "W                         K                         *                         W",
        "W                                                                             W",
        "W                         K                                                   W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
        "                                                                               ",
        "                                                                               ",
        "                                                                               ",
        "                                                                               "
    };

    const char level1[Screen::MAX_Y][Screen::MAX_X] =
    {
        "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
        "W                                                                        ?    W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                             2               W",
        "W                                                                             W",
        "W                                                   /                         W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                 K                                           W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
        "                                                                               ",
        "                                                                               ",
        "                                                                               ",
        "                                                                               "
    };

    const char level2[Screen::MAX_Y][Screen::MAX_X] =
    {
        "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
        "W                                                                             W",
        "W           WWWWWWWWWW      W           W          WWWWWWWWWWWWWW             W",
        "W                W          W           W          W                          W",
        "W                W          W           W          W                          W",
        "W                W          WWWWWWWWWWWW          WWWWWWWWWWWWWW             W",
        "W                W          W           W          W                          W",
        "W                W          W           W          W                          W",
        "W                W          W           W          WWWWWWWWWWWWWWW            W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "W              WWWWWWWWWWWWWWW    W            W      WWWWWW                  W",
        "W              W                  WW           W      W     W                 W",
        "W              W                  W  W         W      W      W                W",
        "W              WWWWWWWWWWWWWWW    W    W       W      W     W                 W",
        "W              W                  W      W     W      W    W                  W",
        "W              W                  W        W   W      W   W                   W",
        "W              WWWWWWWWWWWWWWW    W           WW      WWWW                    W",
        "W                                                                             W",
        "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
        "                                                                               ",
        "                                                                               ",
        "                                                                               ",
        "                                                                               "
    };

    const char opening[Screen::MAX_Y][Screen::MAX_X] =
    {
        "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
        "W                                                                             W",
        "W                             MENU:                                           W",
        "W          --------------------------------------------                       W",
        "W                                                                             W",
        "W                   TO PLAY THE GAME PRESS [1]                                W",
        "W                                                                             W",
        "W                   FOR INSTRUCTIONS PRESS [8]                                W",
        "W                                                                             W",
        "W                   TO EXIT PRESS [9]                                         W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
    };

    const char instructionsScreen[Screen::MAX_Y][Screen::MAX_X] =
    {
        "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
        "W                                                                             W",
        "W                                                                             W",
        "W                               INTRUCTIONS                                   W",
        "W                  ----------------------------------                         W",
        "W                      PLAYER 1 KEYS:                                         W",
        "W               W - UP                                                        W",
        "W               A - LEFT                                                      W",
        "W               D - RIGHT                                                     W",
        "W               X - DOWN                                                      W",
        "W               S - STAY                                                      W",
        "W               E - DROP ITEM                                                 W",
        "W                                                                             W",
        "W                                                                             W",
        "W                        PLAYER 2 KEYS:                                       W",
        "W               I - UP                                                        W",
        "W               J - LEFT                                                      W",
        "W               L - RIGHT                                                     W",
        "W               M - DOWN                                                      W",
        "W               K - STAY                                                      W",
        "W               O - DROP ITEM                                                 W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
    };

    const char pauseMenuArr[Screen::MAX_Y][Screen::MAX_X] =
    {
        "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
        "W                                                                             W",
        "W                                                                             W",
        "W                           GAME PAUSED                                       W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "W              PRESS ESC TO CONTINUE, OR H TO EXIT THE GAME                   W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
    };

    const char riddle1[Screen::MAX_Y][Screen::MAX_X] =
    {
        "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
        "W                                                                             W",
        "W                            RIDDLE NUMBER 1:                                 W",
        "W                ----------------------------------------                     W",
        "W                                                                             W",
        "W           in which battle the normans conquered england?                    W",
        "W                                                                             W",
        "W            1. the battle of cannae  - press A                               W",
        "W                                                                             W",
        "W            2. the battle of pavia - press B                                 W",
        "W                                                                             W",
        "W            3. the battle of the somme - press C                             W",
        "W                                                                             W",
        "W            4. the battle of hastings - press D                              W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
        "                                                                               ",
        "                                                                               ",
        "                                                                               ",
        "                                                                               "
    };

    const char riddle2[Screen::MAX_Y][Screen::MAX_X] = {
        "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
        "W                                                                             W",
        "W                            RIDDLE NUMBER 2:                                 W",
        "W                ----------------------------------------                     W",
        "W                                                                             W",
        "W              what is the name of the sword of king arthur                   W",
        "W                                                                             W",
        "W            1. Joseph Shlomi  - press A                                      W",
        "W                                                                             W",
        "W            2. the dwarf's slayer - press B                                  W",
        "W                                                                             W",
        "W            3. excalibur - press C                                           W",
        "W                                                                             W",
        "W            4. amir hetsroni  - press D                                      W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "W                                                                             W",
        "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
        "                                                                               ",
        "                                                                               ",
        "                                                                               ",
        "                                                                               "
    };

    for (int y = 0; y < Screen::MAX_Y; y++)
    {
        for (int x = 0; x < Screen::MAX_X; x++)
        {
            levels[0][y][x] = level0[y][x];
            levels[1][y][x] = level1[y][x];
            levels[2][y][x] = level2[y][x];
        }
    }
    for (int y = 0; y < Screen::MAX_Y; y++)
    {
        for (int x = 0; x < Screen::MAX_X; x++)
        {
            riddles_chars[0][y][x] = riddle1[y][x];
            riddles_chars[1][y][x] = riddle2[y][x];
        }
    }

    current_riddle = Screen(riddles_chars[currentLevel]);
    screen = Screen(levels[currentLevel]);
    gameMenu = Screen(opening);
    instructions = Screen(instructionsScreen);
    pauseScreen = Screen(pauseMenuArr);
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
                if (result) return; // Exit to main menu
                else {
                    cls();
                    screen.drawRoom();
                    key = 0;
                    continue;
                }
            }

            if (tolower(key) == 'e' && p1.isFullInventory()) {
                char itemInHand1 = p1.getinventory();
                p1.drop_item(p1.getPoint(), screen);
                p1.setStepChar(itemInHand1);
                continue;
            }

            // שחקן 2 זורק חפץ
            if (tolower(key) == 'o' && p2.isFullInventory()) {
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

        handleMovement(p1, p2, clearPass);
        handleMovement(p2, p1, clearPass);

            if (p1_next_char == '#')
            {

                 Spring* s = getSpringAt(p1.getPoint().next());
            
                 bool isCompressingKey = match_directions(s, p1);

                if (s != nullptr)
                {
                    if (isCompressingKey && !s->isFullyCompressed()) {
                        s->compress(); //

                        // מחיקה וציור ידני כדי לא להשתמש ב-move_player שדורס את ה-level
                        gotoxy(p1.getPoint().getX(), p1.getPoint().getY());
                        std::cout << ' ';

                        // עדכון המיקום הלוגי של השחקן - חובה!
                        p1.setPoint(nextP1.getX(), nextP1.getY(), p1.getdirection()); 

                        s->draw(); // מצייר את הקפיץ המכווץ
                        p1.draw_player();

                        p1_activeSpring = s;
                    
                    }
                    else if (s->isFullyCompressed())
                    {
                        release_spring(p1, s, screen);
                    }
                    else if (!isCompressingKey && s->getcurrentCompressed() > 0)
                    {
                        release_spring(p1, s, screen);
                    }
                    else if (!isCompressingKey)
                    {
                        p1.freeze();
                    }
                }
                else
                {
					p1.freeze();
                }
            }
            else
            {
                handleMovement(p1, p2, p1canpass);
            }
        }
       
        if (p2.getRoom() == currentLevel) 
            handleMovement(p2, p1, p2canpass);

        if (p1.getRoom() == currentLevel && !(p1.getPoint() == prev_p1))
        {
            if (screen.isPlatform_on(prev_p1) || screen.isPlatform_off(prev_p1)) 
            {
                on_or_off_switch(prev_p1, screen);
            }
        }
        if (!(p2.getPoint() == prev_p2)) {
            if (screen.isPlatform_on(prev_p2) || screen.isPlatform_off(prev_p2)) {
                on_or_off_switch(prev_p2, screen);
            }
        }

        // טיפול בחידות
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

    if (screen.isWall(nextPos)) {
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