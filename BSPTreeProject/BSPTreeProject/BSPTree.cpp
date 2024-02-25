#include "BSPTree.h"
#include <iostream>

BSPTree::BSPTree() { root = NULL; };
BSPTree::~BSPTree()
{
	destroy_tree_rec(root);
	root = NULL;
}
void BSPTree::destroy_tree_rec(BSPNode* node)
{
	if (node == NULL) return;
	destroy_tree_rec(node->n_back);
	destroy_tree_rec(node->n_front);
	delete node;
}

void BSPTree::create_tree(const Map& map)
{
	root = create_tree_rec(map.get_walls());
}

BSPNode* BSPTree::create_tree_rec(const std::vector<Wall>& walls)
{
	// 1. choose a wall w from list and add it to node n
	if (walls.empty()) return NULL;
	Wall w = walls[0];
	BSPNode* n = new BSPNode { NULL, NULL, {w} };

	std::vector<Wall> front_walls;
	std::vector<Wall> back_walls;
	// 2. sort remaining walls by position relative to w
	for (int i = 1; i < walls.size(); ++i) {
		RelPos pos = w.get_relative_position(walls[i]);
		switch (pos)
		{
			case front:
				front_walls.push_back(walls[i]);
				break;
			case back:
				back_walls.push_back(walls[i]);
				break;
			case colinear:
				n->walls.push_back(walls[i]);
				break;
			case spanning:
				Wall front_wall ({ 0,0,0,0 }, 0, 0);
				Wall back_wall ({ 0,0,0,0 }, 0, 0);
				w.split(walls[i], back_wall, front_wall);
				back_walls.push_back(back_wall);
				front_walls.push_back(front_wall);
		}
	}
	// 3. use wall lists to create front and back subtrees
	n->n_back = create_tree_rec(back_walls);
	n->n_front = create_tree_rec(front_walls);
	return n;
}