#include "Spring.h"
#include <iostream>
#include <vector>
#include "utils.h"




Spring::Spring(const std::vector<Point>& locs, Direction releasedir, char sym)
    : locations(locs), symbol(sym), currentCompressed(0)
{
    originalSize = (int)locs.size();

    if (originalSize > 1) 
    {
        if (locations[0].getX() == locations[1].getX()) 
        {
            releaseDir = Direction::directions[Direction::STAY];
        }
        else {
            releaseDir = Direction::directions[Direction::STAY];
        }
    }
    else
    {
        releaseDir = releasedir;
    }
}


bool Spring::isPointOnSpring(const Point& p) const
{
    for (const auto& loc : locations)
    {
        if (loc.getX() == p.getX() && loc.getY() == p.getY()) //checks if the player is on the spring
        {
            return true;
        }
    }
    return false;
}

bool Spring::compress()
{
    if (currentCompressed < originalSize)
    {
        int indexToErase = 0;

        if (releaseDir == Direction::directions[Direction::LEFT] ||
            releaseDir == Direction::directions[Direction::UP]) {
            indexToErase = currentCompressed;
        }
        else
        {
            indexToErase = (originalSize - 1) - currentCompressed;
        }

        erasePoint(indexToErase);
        currentCompressed++;
        return true;
    }
    return false;
}
void Spring::draw() const
{
    for (int i = 0; i < originalSize; i++)
    {
        bool isCompressed = false;

        if (releaseDir == Direction::directions[Direction::DOWN] ||
            releaseDir == Direction::directions[Direction::RIGHT])
        {
            if (i < currentCompressed) isCompressed = true;
        }
        else {
            if (i >= originalSize - currentCompressed) isCompressed = true;
        }

        if (!isCompressed) {
            gotoxy(locations[i].getX(), locations[i].getY());
            std::cout << symbol;
        }
    }
}
void Spring::erasePoint(int index) const //erasing a specific point of the spring, used when the spring is pressed
{
    if (index >= 0 && index < locations.size())
    {
        gotoxy(locations[index].getX(), locations[index].getY());
        std::cout << ' ';
    }
}

void Spring::releaseSpring(int& outSpeed, int& outDuration)
{
    outSpeed = currentCompressed;
    outDuration = currentCompressed * currentCompressed;

    currentCompressed = 0;

    for (const auto& loc : locations)
    {
        gotoxy(loc.getX(), loc.getY());
        std::cout << "";
    }
}
bool Spring::decompress() //reducing the compressed size of the spring
{
    if (currentCompressed > 0)
    {
        currentCompressed--;
        return true;
    }
    return false; //spring is back to original size after being released
}

bool Spring::opposite(const Direction& dir) //checking if the direction of the player is opposite to the release direction
{
    if ((this->releaseDir.getdirx() == -dir.getdirx()) && (this->releaseDir.getdiry() == -dir.getdiry()))
    {
        return true;
    }
    return false;
}


