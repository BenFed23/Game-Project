#include <iostream>
#include "Player.h"
#include "Screen.h"
#include "utils.h"
#include<Windows.h>
#include <fstream>
#include <string>
Screen::Screen()
{
    memset(level, ' ', sizeof(level));
}
Screen::Screen(const char input[MAX_Y][MAX_X])
{
    for (int y = 0; y < MAX_Y; y++) {
        for (int x = 0; x < MAX_X; x++) {
            level[y][x] = input[y][x];
            if (level[y][x] == '/')
            {
                SwitchCounters++;
            }
        }

    }

}

void Screen::drawRoom() const {
    for (int y = 0; y < MAX_Y; y++) {
        gotoxy(0, y);
        for (int x = 0; x < MAX_X; x++) {
            char c = level[y][x];
            if (c == '\0') c = ' '; 
            std::cout << c;
        }
    }
    std::cout << std::flush;
}



void Screen::clearItem(const Point& p)
{
    level[p.getY()][p.getX()] = ' ';
    gotoxy(p.getX(), p.getY());
    std::cout << ' ';
}

void Screen::drawStatus(const Player& p1, const Player& p2) const {
    int baseRow = Screen::MAX_Y - 4;


    gotoxy(0, baseRow);
    std::cout << "Player1 Life: " << p1.getlifePoint();
    gotoxy(0, baseRow + 1);
    std::cout << "Inventory: " << p1.getinventory();
    gotoxy(0, baseRow + 2);
    std::cout << "Power: " << p1.getPower();


    std::string p2Life = "Player2 Life: " + std::to_string(p2.getlifePoint());
    std::string p2Inv = "Inventory: " + std::string(1, p2.getinventory());
    std::string p2Pw = "Power: " + std::to_string(p2.getPower());

    int colRightLife = Screen::MAX_X - p2Life.length();
    int colRightInv = Screen::MAX_X - p2Inv.length();
    int colRightPw = Screen::MAX_X - p2Pw.length();

    gotoxy(colRightLife, baseRow);
    std::cout << p2Life;
    gotoxy(colRightInv, baseRow + 1);
    std::cout << p2Inv;
    gotoxy(colRightPw, baseRow + 2);
    std::cout << p2Pw;

    std::cout << std::flush;
}


bool Screen::isPointInVector(const std::vector<Point>& vec, int x, int y) const//checking if point is in vector
{
    for (const Point& p : vec)
    {
        if (p.getX() == x && p.getY() == y)
        {
            return true;
        }
    }
    return false;
}

std::vector<Point> Screen::getObstacleVector(Point startPoint) //creating the obstacle vector
{
    std::vector<Point> obstaclePoints;
    std::vector<Point> toCheck;

    if (charAt(startPoint) != '*') //if the char is not *, return empty vector
    {
        return obstaclePoints;
    }

    toCheck.push_back(startPoint);
    obstaclePoints.push_back(startPoint);

    int head = 0;

    while (head < toCheck.size()) {
        Point current = toCheck[head++];

        int dx[] = { 0, 0, 1, -1 };
        int dy[] = { 1, -1, 0, 0 };

        for (int i = 0; i < 4; i++) {
            int nextX = current.getX() + dx[i];
            int nextY = current.getY() + dy[i];

            if (nextX >= 0 && nextX < MAX_X && nextY >= 0 && nextY < MAX_Y) {

                if (level[nextY][nextX] == '*') {

                    if (!isPointInVector(obstaclePoints, nextX, nextY)) {

                        Point neighbor(nextX, nextY, Direction::directions[Direction::STAY], '*');

                        obstaclePoints.push_back(neighbor);
                        toCheck.push_back(neighbor);
                    }
                }
            }
        }
    }

    return obstaclePoints;
}

bool Screen::isPointPartOfObstacle(const std::vector<Point>& obstacle, const Point& p) const  //covering the function isPointInVector to get it outside the class
{
    return isPointInVector(obstacle, p.getX(), p.getY());
}

void Screen::setChar(const Point& p, char ch)
{
    level[p.getY()][p.getX()] = ch;
    gotoxy(p.getX(), p.getY());
    std::cout << ch << std::flush;
}

bool Screen::isDoor(const Point& p) const
{
    int num = charAt(p) - '0';

    if ((num > 4) || (num < 1))
    {
        return false;
    }
    return true;
}
bool Screen::loadefile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file) return false;

    SwitchCounters = 0;
    std::string line;

    for (int y = 0; y < Screen::MAX_Y; y++)
    {
        if (!std::getline(file, line)) line.clear();

        if (!line.empty() && line.back() == '\r')  
            line.pop_back();

        for (int x = 0; x < Screen::MAX_X; x++)
        {
            char c = (x < (int)line.size()) ? line[x] : ' ';
            level[y][x] = c;
            if (c == '/') SwitchCounters++;
        }
    }
    return true;
}


