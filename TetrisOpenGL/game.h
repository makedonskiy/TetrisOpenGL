#pragma once
#include "figura.h"
#include "line.h"

class Game
{
public:
	enum KeyState { UP, DOWN, LEFT, RIGHT, F1 };
	Game();
	bool start_;
	int time_;
	int point_game_;
	int level_;
	int next_level_ = 1000;
	void draw(Point &);
	void tick();
	void restart();
	void keyEvent(KeyState);
private:	
	Line line_;
	Figura figura_;
	Figura next_;
	const int points_line_ = 100;
};