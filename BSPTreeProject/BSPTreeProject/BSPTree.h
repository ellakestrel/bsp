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
private:
	BSPNode* create_tree_rec(const std::vector<Wall>& walls);
	void destroy_tree_rec(BSPNode* node);
};
