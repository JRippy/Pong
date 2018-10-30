#include "pch.h"
#include "Score.h"


Score::Score() :
	player1(0),
	player2(0)
{
}


Score::~Score()
{
}

int Score::getScore1()
{
	return player1;
}

int Score::getScore2()
{
	return player2;
}

void Score::addScore1()
{
	player1++;
}

void Score::addScore2()
{
	player2++;
}

void Score::init()
{
	player1 = 0;
	player2 = 0;
}
