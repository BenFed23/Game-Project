#pragma once
#include "Screen.h"
class Riddle
{
	char correctAnswer;
public:
	char getAnswer()
	{
		return correctAnswer;
	}
	Riddle(){}
	Riddle(char c)
	{
		if((c<='D')&&('A'<=c))
		{
			correctAnswer = c;
		}
		else
		{
			return;
		}
		
	}
};
