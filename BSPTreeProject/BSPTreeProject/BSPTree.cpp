#include "BSPTree.h"

BSPTree::BSPTree() {};

void BSPTree::create_tree(Map& map) {
	

}

BSPNode BSPTree::create_tree_rec(std::vector<Wall> walls) {
	// 1. choose a wall w from list
	// 2. create node n with wall=w
	// 3. create lists of walls front and back
	// 4. for each remaining wall in walls:
	//    1. if wall is in front of w, move to front list
	//    2. if wall is behind w, move to back list
	//    3. if wall is intersected by the line of w, split wall into two and
	//       add to appropriate lists
	//    4. if wall is on the same line as w, add wall to n
	// 5. n.back = create_tree_rec(back)
	// 6. n.front = create_tree_rec(front)
	// 7. return n
	return { NULL, NULL, {} };
}
