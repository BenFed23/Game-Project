#pragma once
#include "Circle.h"

class BOMB
{
	Circle bombCircle; //the circle representing the bomb's explosion range
	int timer; //the timer until explosion
	int internalCycles; //internal cycles to count the time



public:
	BOMB(Point p, int r = 4) : bombCircle(r, p), timer(5), internalCycles(0) {}


    bool update(); //the time until explosion
    

    int getTimer() const 
    { 
        return timer; 
    }
    Point getPos() const 
    { 
        return bombCircle.getCenter(); 
    }
    Circle getCircle() const
    { 
        return bombCircle; 
    }
};

