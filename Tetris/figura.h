#pragma once
#include "point.h"

class Figura
{
public:
	enum Direction { LEFT = -1, RIGHT = 1 };
	enum Name { I, J, L, O, S, Z, T };
	Figura(Name);
	void draw(Point &);
	void move(int dx, int dy);
	void rotate(Direction);
	bool map(int x, int y) const;
	int x() const { return x_; }	
	int y() const { return y_; }
	void pos(int x, int y);
	float r() const { return color_.r; }
	float g() const { return color_.g; }
	float b() const { return color_.b; }
private:
	Name name_;
	int angel_;
	int x_;
	int y_;
	Point::Color color_;
};