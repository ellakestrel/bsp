#pragma once

#include "Map.h"

struct BSPNode
{
	BSPNode* n_back;
	BSPNode* n_front;
	std::vector<Wall> walls;
};

class BSPTree
{
	BSPNode* root;
public:
	BSPTree();
	~BSPTree();
	void create_tree(const Map& map);
	bool raycast(const Point2D& origin, const Point2D& direction, float max_distance, Wall& hit) const;
private:
	BSPNode* create_tree_rec(const std::vector<Wall>& walls);
	void destroy_tree_rec(BSPNode* node);
	bool raycast_rec(const BSPNode* node, const Point2D& origin, const Point2D& endpoint, Wall& hit) const;
};
