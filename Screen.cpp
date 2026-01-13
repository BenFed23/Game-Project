#include <iostream>
#include "Player.h"
#include "Screen.h"
#include "utils.h"
#include<Windows.h>
#include <fstream>
#include <string>
#include <string.h>
#include <algorithm>
#include "Circle.h"


Screen::Screen()
{
    memset(level, ' ', sizeof(level));
}
Screen::Screen(const char input[MAX_Y][MAX_X], bool createBottom)
{

    for (int y = 0; y < MAX_Y; y++)
    {
        for (int x = 0; x < MAX_X; x++)
        {
            level[y][x] = input[y][x];
            if (level[y][x] == '/')
            {
                SwitchCounters++;
            }
           

        }

    }

    int legendY = this->getLegendPos().getY();
    if (createBottom)
    {
        if (legendY >= 1 && legendY < 21)
        {
            for (int i = legendY - 1; i <= legendY + 3; i++)
            {
                for (int j = 15; j <= 63; j++)
                {
                    if (i >= 0 && i < MAX_Y && j >= 0 && j < MAX_X)
                    {
                        if (i == legendY - 1 || i == legendY + 3 || j == 15 || j == 63)
                        {
                            level[i][j] = 'W';
                        }
                        else
                        {
                            level[i][j] = ' ';
                        }
                    }
                }
            }
        }


    }
    if (!createBottom || legendY == 21)
    {
        this->setLegendPos(Point(0, 21));
        legendY = 21;

        for (int j = 0; j < MAX_X - 1; j++)
        {
            level[legendY - 1][j] = 'W';
        }
    }



    for (int y = 0; y < MAX_Y; y++)
    {
        for (int x = 0; x < MAX_X; x++)
        {
            if (level[y][x] == '#')
            {
                bool alreadyInSpring = false;
                for (const auto& s : springs)
                {
                    if (s.isPointOnSpring(Point(x, y)))
                    {
                        alreadyInSpring = true;
                        break;
                    }
                }


                if (!alreadyInSpring)
                {
                    std::vector<Point> springPoints = getSpringVector(Point(x, y));
                    Direction dir = Direction::directions[Direction::LEFT];

                    if (x == 1)
                    {
                        dir = Direction::directions[Direction::RIGHT];
                    }
                    else if (x == MAX_X - 2)
                    {
                        dir = Direction::directions[Direction::LEFT];
                    }
                    else if (y == MAX_Y - 2)
                    {
                        dir = Direction::directions[Direction::UP];
                    }

                    springs.emplace_back(springPoints, dir, '#');
                }
            }


        }
    }

}

void Screen::drawRoom() const
{
    for (int y = 0; y < MAX_Y; y++)
    {
        gotoxy(0, y);
        for (int x = 0; x < MAX_X; x++)
        {
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

void Screen::drawStatus(const Player& p1, const Player& p2) const
{
  

	Point legendPos = this->getLegendPos();
	int legendPos_X = legendPos.getX();
	int legendPos_Y = legendPos.getY();


    if (legendPos_Y == 21)
    {
        gotoxy(2, legendPos_Y);
        std::cout << "P1 Life: " << p1.getlifePoint();
        gotoxy(2, legendPos_Y + 1);
        std::cout << "Inventory: " << p1.getinventory();
        gotoxy(2, legendPos_Y + 2);
        std::cout << "Power: " << p1.getPower();
        if (darkmode && p1.getinventory() != '!' && p2.getinventory() != '!')
        {
            gotoxy(15, 23);
            std::cout << "Notice: you are in a dark room without a torch!";
            gotoxy(15, 24);
            std::cout << "You must to go back and get a torch to see!";
        }
		gotoxy(30, legendPos_Y);
		std::cout << "score: " << p1.getlifePoint() * 100 + p1.getPower() * 50;
        gotoxy(65, legendPos_Y);
        std::cout << "P2 Life: " << p2.getlifePoint();
        gotoxy(65, legendPos_Y + 1);
        std::cout << "Inventory: " << p2.getinventory();
        gotoxy(65, legendPos_Y + 2);
        std::cout << "Power: " << p2.getPower();
    }
    else
    {
        gotoxy(17, legendPos_Y);
        std::cout << "P1 Life: " << p1.getlifePoint();
        gotoxy(17, legendPos_Y + 1);
        std::cout << "Inventory: " << p1.getinventory();
        gotoxy(17, legendPos_Y + 2);
        std::cout << "Power: " << p1.getPower();

        gotoxy(50, legendPos_Y);
        std::cout << "P2 Life: " << p2.getlifePoint();
        gotoxy(50, legendPos_Y + 1);
        std::cout << "Inventory: " << p2.getinventory();
        gotoxy(50, legendPos_Y + 2);
        std::cout << "Power: " << p2.getPower();
    } 
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

    while (head < toCheck.size())
    {
        Point current = toCheck[head++];

        int dx[] = { 0, 0, 1, -1 };
        int dy[] = { 1, -1, 0, 0 };

        for (int i = 0; i < 4; i++)
        {
            int nextX = current.getX() + dx[i];
            int nextY = current.getY() + dy[i];

            if (nextX >= 0 && nextX < MAX_X && nextY >= 0 && nextY < MAX_Y) {

                if (level[nextY][nextX] == '*')
                {

                    if (!isPointInVector(obstaclePoints, nextX, nextY))
                    {

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
    char c = charAt(p);
    return (c >= '0' && c <= '9');
}

std::vector<Point> Screen::getSpringVector(Point startPoint) //creating the spring vector
{
    std::vector<Point> springPoints;
    std::vector<Point> toCheck;

    if (charAt(startPoint) != '#') return springPoints;

    toCheck.push_back(startPoint);
    springPoints.push_back(startPoint);

    int head = 0;

    while (head < toCheck.size())
    {
        Point current = toCheck[head++];
        int dx[] = { 0, 0, 1, -1 };
        int dy[] = { 1, -1, 0, 0 };

        for (int i = 0; i < 4; i++)
        {
            int nextX = current.getX() + dx[i];
            int nextY = current.getY() + dy[i];

            if (nextX >= 0 && nextX < MAX_X && nextY >= 0 && nextY < MAX_Y)
            {
                if (level[nextY][nextX] == '#')
                {
                    if (!isPointInVector(springPoints, nextX, nextY))
                    {
                        Point neighbor(nextX, nextY, Direction::directions[Direction::STAY], '#');
                        springPoints.push_back(neighbor);
                        toCheck.push_back(neighbor);
                    }
                }
            }
        }
    }
    return springPoints;
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
            
        }
    }
    return true;
   
}
bool Screen::loadefile(const std::string& filename, bool createBottom)
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
            if (level[y][x] == 'L')
            {
                this->setLegendPos(Point(x, y));
                level[y][x] = ' ';
            }
        }
    }
    int legendY = this->getLegendPos().getY();
    if (createBottom)
    {
        if (legendY >= 1 && legendY < 21)
        {
            for (int i = legendY - 1; i <= legendY + 3; i++)
            {
                for (int j = 15; j <= 63; j++)
                {
                    if (i >= 0 && i < MAX_Y && j >= 0 && j < MAX_X)
                    {
                        if (i == legendY - 1 || i == legendY + 3 || j == 15 || j == 63)
                        {
                            level[i][j] = 'W';
                        }
                        else
                        {
                            level[i][j] = ' ';
                        }
                    }
                }
            }
        }


    }
    if (!createBottom || legendY == 21)
    {
        this->setLegendPos(Point(0, 21));
        legendY = 21;

        for (int j = 0; j < MAX_X - 1; j++)
        {
            level[legendY - 1][j] = 'W';
        }
    }



    for (int y = 0; y < MAX_Y; y++)
    {
        for (int x = 0; x < MAX_X; x++)
        {
            if (level[y][x] == '#')
            {
                bool alreadyInSpring = false;
                for (const auto& s : springs)
                {
                    if (s.isPointOnSpring(Point(x, y)))
                    {
                        alreadyInSpring = true;
                        break;
                    }
                }


                if (!alreadyInSpring)
                {
                    std::vector<Point> springPoints = getSpringVector(Point(x, y));
                    Direction dir = Direction::directions[Direction::LEFT];

                    if (x == 1)
                    {
                        dir = Direction::directions[Direction::RIGHT];
                    }
                    else if (x == MAX_X - 2)
                    {
                        dir = Direction::directions[Direction::LEFT];
                    }
                    else if (y == MAX_Y - 2)
                    {
                        dir = Direction::directions[Direction::UP];
                    }

                    springs.emplace_back(springPoints, dir, '#');
                }
            }
            
        }
    }
    return true;
}
void Screen::buildSprings()
{
    springs.clear();

    for (int y = 0; y < MAX_Y; y++)
    {
        for (int x = 0; x < MAX_X; x++)
        {
            if (level[y][x] != '#') continue;

            bool alreadyInSpring = false;
            for (const auto& s : springs)
            {
                if (s.isPointOnSpring(Point(x, y)))
                {
                    alreadyInSpring = true;
                    break;
                }
            }
            if (alreadyInSpring) continue;

            std::vector<Point> springPoints = getSpringVector(Point(x, y));

            Direction dir = Direction::directions[Direction::LEFT];
            if (x == 1) dir = Direction::directions[Direction::RIGHT];
            else if (x == MAX_X - 2) dir = Direction::directions[Direction::LEFT];
            else if (y == MAX_Y - 2) dir = Direction::directions[Direction::UP];

            springs.emplace_back(springPoints, dir, '#');
        }
    }
}
bool Screen::isPlayer(const Point& p)
{
    if (((charAt(p)) == '$') || ((charAt(p)) == '&'))
    {
        return true;
    }
    return false;
}
bool Screen::antiBoom(const Point& p)
{
    if ((charAt(p) == 'W') || (charAt(p) == 'K' || ((charAt(p) == '@')) || ((charAt(p) == '!')) || ((charAt(p) == '#')) || charAt(p) == '?'))
    {
        return true;
    }
    return false;
}