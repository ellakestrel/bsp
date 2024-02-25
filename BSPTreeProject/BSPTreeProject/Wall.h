#pragma once

#include "Line2D.h"

enum RelPos {back = -1, front = 1, colinear = 0, spanning = 2};

class Wall
{
	Line2D line;
	float normal_x;
	float normal_y;
public:
	Wall(const Line2D& line, float normal_x, float normal_y);
	RelPos get_relative_position(const Point2D& point) const;
	RelPos get_relative_position(const Line2D& line_segment) const;
	RelPos get_relative_position(const Wall& segment) const;
	bool split(const Wall& wall, Wall& back_wall, Wall& front_wall) const;
};

