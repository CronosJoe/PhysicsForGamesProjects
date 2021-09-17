#include "shape.h"

bool circleCircleCollision()
{
	return false;
}
AABB :: operator Rectangle() const
{
	return Rectangle{min.x, min.y, max.x - min.x, max.y - min.y};
}
