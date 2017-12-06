#include "point.h"
#include <GL/glut.h>

void Point::rect(int x1, int y1, int x2, int y2)
{
	glBegin(GL_QUADS);
	glVertex2f(x1, y1);
	glVertex2f(x2, y1);
	glVertex2f(x2, y2);
	glVertex2f(x1, y2);
	glEnd();
}

void Point::setColor(color color)
{
	Color colors[] =
	{
		{ 0.5, 0.5, 0.5 },{ 0, 0, 1 },{ 0, 1, 0 },{ 0, 1, 1 },
		{ 1, 0, 0 },{ 1, 0, 1 },{ 1, 1, 0 },{ 1, 1, 1 }
	};
	color_.r = colors[color].r;
	color_.g = colors[color].g;
	color_.b = colors[color].b;
	glColor3f(color_.r, color_.g, color_.b);
}

void Point::setColor(float r, float g, float b)
{
	color_.r = r;
	color_.g = g;
	color_.b = b;
	glColor3f(r, g, b);
}