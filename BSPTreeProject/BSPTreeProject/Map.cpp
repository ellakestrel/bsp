#include "Map.h"

Map::Map(float w, float h) : width(w), height(h) {}

void Map::add_wall(Wall wall) {
	walls.push_back(wall);
}
