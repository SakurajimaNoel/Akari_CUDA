#include "Ray.h"

point3 ray::at(double t) const
{
    return origin + direction * t;
}
