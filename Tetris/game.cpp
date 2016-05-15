#include "game.h"
#include <cstdlib>

Game::Game() : figura_(static_cast<Figura::Name>(rand() % 7)), next_(static_cast<Figura::Name>(rand() % 7))
{
	start_ = false;
	figura_.pos(3, 17);
	next_.pos(6, 21);
	point_game_ = 0;
	time_ = 1000;
	next_level_ = 1000;
	level_ = 1;
}

void Game::draw(Point &p)
{
	line_.draw(p);
	figura_.draw(p);
	next_.draw(p);
}

void Game::tick()
{
	auto f = figura_;
	f.move(0, 1);
	if (!line_.isCollision(f))
		figura_ = f;
	else
	{
		line_.unite(figura_);
		auto removeLines = line_.removeSolidLines();
		point_game_ = point_game_ + removeLines * points_line_;
		if (point_game_ >= next_level_)
		{
			next_level_ = next_level_ + 1000 * level_;
			level_++;
			if (time_ > 100)
				time_ -= 100;
		}
		figura_ = next_;
		figura_.pos(3, 17);
		next_ = Figura(static_cast<Figura::Name>(rand() % 7));
		next_.pos(6, 21);
		if (line_.isCollision(figura_))
		{
			point_game_ = 0;
			next_level_ = 1000;
			level_ = 1;
			time_ = 1000;
			restart();
			start_ = false;
		}
	}
}

void Game::restart()
{
	line_ = Line();
}

void Game::keyEvent(KeyState d)
{
	auto t = figura_;
	switch (d)
	{
	case UP: if(start_) t.rotate(Figura::RIGHT);
		break;
	case DOWN: if (start_) t.move(0, 1);
		break;
	case LEFT: if (start_) t.move(1, 0);
		break;
	case RIGHT: if (start_) t.move(-1, 0);
		break;
	case F1: start_ = !start_;
		break;
	}
	if (!line_.isCollision(t))
		figura_ = t;
}