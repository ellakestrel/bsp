#include "BSPTree.h"
#include <iostream>
#include <algorithm>

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

bool BSPTree::raycast(const Point2D& origin, const Point2D& direction, float max_distance, Wall& hit) const
{
	// normalize direction
	float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	Point2D n_direction = { direction.x / magnitude, direction.y / magnitude };
	// multiply by max_distance and add origin
	Point2D endpoint = { n_direction.x * max_distance + origin.x, n_direction.y * max_distance + origin.y };

	return raycast_rec(root, origin, endpoint, hit);
}

/* Note: if endpoint is touching the wall but does not cross it, it does not count as a hit */
bool BSPTree::raycast_rec(const BSPNode* n, const Point2D& origin, const Point2D& endpoint, Wall& hit) const
{
	if (n == NULL) return false;
	const Wall& w = n->walls[0];

	Line2D path = { origin, endpoint };
	RelPos pos = w.get_relative_position(path);
	if (pos == back) return raycast_rec(n->n_back, origin, endpoint, hit);
	if (pos == front) return raycast_rec(n->n_front, origin, endpoint, hit);
	if (pos == colinear) return raycast_rec(n->n_front, origin, endpoint, hit);

	// path spans w
	Point2D p_i;
	path.get_intersection(w.get_line(), p_i);

	// check first half of path
	bool success = false;
	if (w.get_relative_position(origin) == back) {
		success = raycast_rec(n->n_back, origin, p_i, hit);
	}
	else {
		success = raycast_rec(n->n_front, origin, p_i, hit);
	}
	if (success) return true;

	// check if path hits any walls at node n
	//    we know the line intersection is at p_i, but this might not be in the wall.
	for (const Wall& wall : n->walls) {
		// check if p_i is on the line segment of wall
		float wx1 = wall.get_line().p1().x;
		float wx2 = wall.get_line().p2().x;
		float wy1 = wall.get_line().p1().y;
		float wy2 = wall.get_line().p2().y;
		if (p_i.x <= std::max(wx1, wx2) && p_i.x >= std::min(wx1, wx2)
			&& p_i.y <= std::max(wy1, wy2) && p_i.y >= std::min(wy1, wy2))
		{
			hit = wall;
			return true;
		}
	}

	// check second half of path
	success = false;
	if (w.get_relative_position(endpoint) == back) {
		success = raycast_rec(n->n_back, p_i, endpoint, hit);
	}
	else {
		success = raycast_rec(n->n_front, p_i, endpoint, hit);
	}
	return success;
}