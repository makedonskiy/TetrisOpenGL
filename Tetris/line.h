#pragma once
#include "point.h"
#include "figura.h"

class Figura;

class Line
{
public:
	enum { WIDTH = 10, HEIGHT = 20 };
	Line();
	void draw(Point &) const;
	bool isCollision(const Figura &) const;
	void unite(const Figura &);
	int removeSolidLines();
private:
	bool map_[HEIGHT][WIDTH];
	Point::Color color_[HEIGHT][WIDTH];
};
