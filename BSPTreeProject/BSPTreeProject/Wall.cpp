#include "Wall.h"

Wall::Wall(Line2D l, float nx, float ny) : line(l), normal_x(nx), normal_y(ny) {};

RelPos Wall::get_relative_position(Point2D point) const
{
	Point2D p1 = line.p1();
	float dot = (point.x - p1.x) * normal_x + (point.y - p1.y) * normal_y;
	if (dot < 0) return back;
	if (dot > 0) return front;
	return colinear;
}

RelPos Wall::get_relative_position(const Line2D& line_segment) const
{
	RelPos pos1 = get_relative_position(line_segment.p1());
	RelPos pos2 = get_relative_position(line_segment.p2());
	if (pos1 == colinear) return pos2;
	if (pos2 == colinear) return pos1;
	if (pos1 != pos2) return spanning;
	return pos1;
}

RelPos Wall::get_relative_position(const Wall& segment) const
{
	return get_relative_position(segment.line);
}

/* Using the line formed my this wall, split another wall into
   back_wall (section behind this wall) and
   front_wall (section in front of this wall).
   (Assume wall spans this line) */
bool Wall::split(const Wall& wall, Wall& back_wall, Wall& front_wall) const
{
	Point2D p_i;
	bool has_intersection = line.get_intersection(wall.line, p_i);
	if (!has_intersection) return false;

	Point2D p_front;
	Point2D p_back;
	if (get_relative_position(wall.line.p1()) == front) {
		p_front = wall.line.p1();
		p_back = wall.line.p2();
	} else {
		p_front = wall.line.p2();
		p_back = wall.line.p1();
	}
	back_wall = Wall( { p_i, p_back }, wall.normal_x, wall.normal_y);
	front_wall = Wall( { p_i, p_front }, wall.normal_x, wall.normal_y);
	return true;
}
