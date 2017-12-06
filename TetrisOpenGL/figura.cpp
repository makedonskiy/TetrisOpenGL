#include "figura.h"
#include "point.h"

Figura::Figura(Name name) : name_(name), angel_(0), x_(6), y_(21)
{ }

void Figura::draw(Point &p)
{
	for (auto y = 0; y < 4; ++y)
	{
		for (auto x = 0; x < 4; ++x)
		{
			if (map(x, y))
			{
				p.setColor(static_cast<Point::color>(name_));
				color_.r = p.color_.r;
				color_.g = p.color_.g;
				color_.b = p.color_.b; 
				p.rect((x + x_) * 8 + 1, (y + y_) * 8 + 1,
					(x + x_ + 1) * 8 - 1, (y + y_ + 1) * 8 - 1);
			}
		}
	}
}

bool Figura::map(int x, int y) const
{
	static const bool SHAPES_INT[7][16] =
	{
		{ 
			0,0,1,0,
			0,0,1,0,
			0,0,1,0,
			0,0,1,0
		},		
		{
			0,0,1,0,
			0,0,1,0,
			0,1,1,0,
			0,0,0,0
		},
		{
			0,1,0,0,
			0,1,0,0,
			0,1,1,0,
			0,0,0,0
		},		
		{
			0,0,0,0,
			0,1,1,0,
			0,1,1,0,
			0,0,0,0
		},
		{ 
			0,0,1,0,
			0,1,1,0,
			0,1,0,0,
			0,0,0,0 
		},		
		{ 
			0,1,0,0,
			0,1,1,0,
			0,0,1,0,
			0,0,0,0
		},
		{
			0,0,0,0,
			0,1,1,1,
			0,0,1,0,
			0,0,0,0
		}
	};

	static const int ROTATE[4][16] =
	{
		{	
			0,	4,	8,	12,
			1,	5,	9,	13,
			2,	6,	10,	14,
			3,	7,	11,	15
		},
		{	
			3,	2,	1,	0,
			7,	6,	5,	4,
			11,	10,	9,	8,
			15,	14,	13,	12
		},
		{	
			15,	11,	7,	3,
			14,	10,	6,	2,
			13,	9,	5,	1,
			12,	8,	4,	0
		},
		{	
			12,	13,	14,	15,
			8,	9,	10,	11,
			4,	5,	6,	7,
			0,	1,	2,	3
		}
	};

	auto rotate = ROTATE[angel_][y * 4 + x];
	auto shapes_int = SHAPES_INT[name_][rotate];
	return shapes_int;
}

void Figura::pos(int x, int y)
{
	x_ = x;
	y_ = y;
}

void Figura::move(int dx, int dy)
{
	x_ -= dx;
	y_ -= dy;
}

void Figura::rotate(Direction d)
{
	angel_ = (angel_ + d + 4) % 4;
}