#pragma once

#include "Line2D.h"

class Wall
{
	Line2D line;
	float normal_x;
	float normal_y;
public:
	Wall(Line2D line, float normal_x, float normal_y);
};

