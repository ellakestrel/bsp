#pragma once

struct Point2D
{
	float x, y;
};

class Line2D
{
	float x1, y1, x2, y2;
public:
	Line2D(float x1, float y1, float x2, float y2);
	bool get_intersection(const Line2D& line, Point2D& intersection);
};

