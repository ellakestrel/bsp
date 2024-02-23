#include "Line2D.h"

Line2D::Line2D(float x1, float y1, float x2, float y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}

bool Line2D::get_intersection(const Line2D& line, Point2D& intersection)
{
	float ud = (line.y2 - line.y1) * (x2 - x1)
		     - (line.x2 - line.x1) * (y2 - y1);
	if (ud == 0) return false;

	float un = (line.x2 - line.x1) * (y1 - line.y1)
	         - (line.y2 - line.y1) * (x1 - line.x1);

	float u = un / ud;
	intersection.x = x1 + u * (x2 - x1);
	intersection.y = y1 + u * (y2 - y1);
	return true;
}
