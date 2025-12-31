#pragma once
#include <vector>
#include "Point.h"
#include "Direction.h"
#include <iostream>



class Spring
{
	std::vector<Point> locations; //the vector which holds the spring
	int originalSize = 0;             //the original size of the spring
	Direction releaseDir = Direction::directions[Direction::STAY]; //the direction the spring will release
	int currentCompressed = 0;        //how much the spring is currently compressed
	char symbol = '#';                  //the symbol of the spring


public:
	Spring() : originalSize(0), currentCompressed(0), symbol('#') {}
	Spring(const std::vector<Point>& locs, Direction releasedir, char sym = '#');

	void draw() const;
	bool compress();
	void releaseSpring(int& outSpeed, int& outDuration);
	bool isPointOnSpring(const Point& p) const;
	bool decompress();
	Spring* getSpringAt(const Point& p);
	void erasePoint(int index) const;//ending the spring problem once and for all

	int getcurrentCompressed() const
	{
		return currentCompressed;
	}


	Direction getReleaseDir() const
	{
		return releaseDir;
	}

	void setReleaseDir(const Direction& dir)
	{
		releaseDir = dir;
	}

	bool opposite(const Direction& dir);

	void debugPrintIndices() const;


	bool isFullyCompressed() const
	{
		return currentCompressed == originalSize;
	}


	const std::vector<Point>& getLocations() const
	{
		return locations;
	}

	void setcurrentCompressed(int val)
	{
		currentCompressed = val;
	}

	int get_original_size() const
	{
		return originalSize;
	}

};