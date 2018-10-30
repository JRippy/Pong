#pragma once
class Score
{
public:
	Score();
	~Score();

	int getScore1();
	int getScore2();

	void addScore1();
	void addScore2();

	void init();

private:
	int player1;
	int player2;
};

