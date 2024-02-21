#pragma once

#include <vector>
#include "Wall.h"

class Map
{
	float width, height;
	std::vector<Wall> walls;
public:
	Map(float width, float height);
	void add_wall(Wall wall);
};

