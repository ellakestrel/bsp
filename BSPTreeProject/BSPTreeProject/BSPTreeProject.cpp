// BSPTreeProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "BSPTree.h"

void test1();

int main()
{
    Map test_map = Map(6, 6);
    test_map.add_wall(Wall({ 1, 6, 4, 3 }, 1, 1));
    test_map.add_wall(Wall({ 0, 3, 4, 3 }, 0, -1));
    test_map.add_wall(Wall({ 3, 1, 6, 4 }, -1, 1));
    test_map.add_wall(Wall({ 3, 1, 4, 0 }, -1, -1));

    std::vector<Wall> walls = test_map.get_walls();
    RelPos pos1 = walls[0].get_relative_position(walls[3]);
	std::cout << "Pos: " << pos1 << std::endl;
    RelPos pos2 = walls[3].get_relative_position(walls[0]);
	std::cout << "Pos: " << pos2 << std::endl;
}

void test1()
{
    Line2D line1 = Line2D(3, 4, 0, 0);
    Line2D line2 = Line2D(0, 3, 3, 0);
    Point2D i = Point2D();
    bool intersection_exists = line1.get_intersection(line2, i);
    if (!intersection_exists) {
		std::cout << "Parallel" << std::endl;
    } else {
		std::cout << "Intersection: " << i.x << ", " << i.y << std::endl;
    }

    /* Wall Test */
    Wall wall1 = Wall({ 0, 6, 3, 3 }, 1, 1);
    Wall wall2 = Wall({ 0, 3, 3, 3 }, 0, -1);
    Point2D p = { 1, 4 };
    RelPos pos1 = wall1.get_relative_position(p);
    RelPos pos2 = wall2.get_relative_position(p);
	std::cout << "Pos1: " << pos1 << std::endl;
	std::cout << "Pos2: " << pos2 << std::endl;

    p = { 3, 3 };
    pos1 = wall1.get_relative_position(p);
    pos2 = wall2.get_relative_position(p);
	std::cout << "Pos1: " << pos1 << std::endl;
	std::cout << "Pos2: " << pos2 << std::endl;

    p = { 3, 4 };
    pos1 = wall1.get_relative_position(p);
    pos2 = wall2.get_relative_position(p);
	std::cout << "Pos1: " << pos1 << std::endl;
	std::cout << "Pos2: " << pos2 << std::endl;

    p = { 4, 2 };
    pos1 = wall1.get_relative_position(p);
    pos2 = wall2.get_relative_position(p);
	std::cout << "Pos1: " << pos1 << std::endl;
	std::cout << "Pos2: " << pos2 << std::endl;
}
