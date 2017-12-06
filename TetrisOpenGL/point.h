#pragma once

class Point
{
public:
	enum color {
		GRAY, DARK_BLUE, GREEN, CYAN, RED, MAGENTA, YELLOW, WHITE
	};
	static void rect(int x1, int y1, int x2, int y2);
	void setColor(color);
	void setColor(float r, float g, float b);
	struct Color
	{
		float r, g, b;
	};
	Color color_;
};

