#pragma once

#include "Map.h"

struct BSPNode
{
	BSPNode* back;
	BSPNode* front;
	std::vector<Wall> walls;
};

class BSPTree
{
	std::vector<BSPNode> nodes;
public:
	BSPTree();
	void create_tree(Map& map);
private:
	BSPNode create_tree_rec(std::vector<Wall> walls);
};
