#include "point.h"

bool point_is_equal(point_t p1, point_t p2)
{
    return ((p1.x == p2.x) && (p1.y == p2.y));
}
