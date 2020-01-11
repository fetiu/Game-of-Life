#ifndef POINT_H
#define POINT_H

#include <stdbool.h>

typedef struct
{
    int x;
    int y;
} point_t;

bool point_is_equal(point_t p1, point_t p2);

#endif // POINT_H
