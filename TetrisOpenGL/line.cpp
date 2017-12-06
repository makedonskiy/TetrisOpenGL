#include "line.h"
#include "point.h"
#include "figura.h"
#include <GL/glut.h>

Line::Line()
{
	for (auto y = 0; y < HEIGHT; ++y)
		for (auto x = 0; x < WIDTH; ++x)
		{
			map_[y][x] = false;
			color_[y][x].r = 0;
			color_[y][x].g = 0;
			color_[y][x].b = 0;
		}
}

void Line::draw(Point &p) const
{
	for (auto y = 0; y < HEIGHT; ++y)
	{
		for (auto x = 0; x < WIDTH; ++x)
		{
			if (map_[y][x])
			{
				p.setColor(color_[y][x].r, color_[y][x].g, color_[y][x].b);
				p.rect(x * 8 + 1, y * 8 + 1,
					(x + 1) * 8 - 1, (y + 1) * 8 - 1);
			}
		}
	}
	glLineWidth(5);
	glBegin(GL_LINE_STRIP);
	glColor3f(1, 1, 1);
	glVertex2f(1, HEIGHT * 8);
	glVertex2f(1, 0);
	glVertex2f(WIDTH * 8, 0);
	glVertex2f(WIDTH * 8, HEIGHT * 8);
	glEnd();
}

bool Line::isCollision(const Figura &t) const
{
	for (auto y = 0; y < 4; ++y)
	{
		for (auto x = 0; x < 4; ++x)
		{
			if (t.map(x, y))
			{
				auto wx = x + t.x();
				auto wy = y + t.y();
				if (wx < 0 || wx >= WIDTH || wy < 0 || wy > HEIGHT)
					return true;
				if (wy < HEIGHT && wx < WIDTH && map_[wy][wx])
					return true;
			}
		}
	}
	return false;
}

void Line::unite(const Figura &t)
{
	for (auto y = 0; y < 4; ++y)
	{
		for (auto x = 0; x < 4; ++x)
		{
			auto wx = x + t.x();
			auto wy = y + t.y();
			if (wx >= 0 || wx < WIDTH || wy >= 0 || wy < HEIGHT)
			{
				if (wy >= 0 && wx >= 0)
				{
					map_[wy][wx] = map_[wy][wx] || t.map(x, y);
					if (t.map(x, y))
					{
						color_[wy][wx].r = t.r();
						color_[wy][wx].g = t.g();
						color_[wy][wx].b = t.b();
					}
				}
			}
		}
	}
}

int Line::removeSolidLines()
{
	auto res = 0;
	for (auto y = HEIGHT-1; y >= 0; --y)
	{
		auto solid = true;
		for (auto x = 0; x < WIDTH; ++x)
		{
			if (!map_[y][x])
			{
				solid = false;
				break;
			}
		}
		if (solid)
		{
			++res;
			for (auto yy = y + 1; yy < HEIGHT; ++yy)
			{
				for (auto x = 0; x < WIDTH; ++x)
				{
					map_[yy - 1][x] = map_[yy][x];
					color_[yy - 1][x] = color_[yy][x];
				}
			}
		}
		for (auto x = 0; x < WIDTH; ++x)
		{
			map_[19][x] = false;
		}
	}
	return res;
}