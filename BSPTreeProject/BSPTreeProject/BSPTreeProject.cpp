// BSPTreeProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "BSPTree.h"

void test_raycast(const BSPTree& tree, const Point2D& origin, const Point2D& direction, float max_distance);

int main()
{
    Map test_map = Map(6, 6);
    test_map.add_wall(Wall({ 1, 6, 4, 3 }, 1, 1));
    test_map.add_wall(Wall({ 0, 3, 4, 3 }, 0, -1));
    test_map.add_wall(Wall({ 3, 1, 6, 4 }, -1, 1));
    test_map.add_wall(Wall({ 3, 1, 4, 0 }, -1, -1));

    BSPTree tree = BSPTree();
    tree.create_tree(test_map);
    test_raycast(tree, { 1,1 }, { 1,1 }, 100);
    test_raycast(tree, { 2,0 }, { 2,1 }, 100);
    test_raycast(tree, { 1.25,0 }, { 1,1 }, 100);
    test_raycast(tree, { 3.5,0 }, { 0,1 }, 100);
    test_raycast(tree, { 3.5,6 }, { 0,-1 }, 100);
    test_raycast(tree, { 5,5 }, { 0,-1 }, 100);
}

void test_raycast(const BSPTree& tree, const Point2D& origin, const Point2D& direction, float max_distance)
{
    std::cout << "Raycast with origin " << origin << " and direction " << direction << ":" << std::endl;
    std::cout << "   ";
    Wall hit;
    bool success = tree.raycast(origin, direction, max_distance, hit);
    if (success) {
        std::cout << "Hit Wall: " << hit << std::endl;
    }
    else {
        std::cout << "No Hit" << std::endl;
    }
    std::cout << std::endl;
}
