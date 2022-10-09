#pragma once
#include "Vec3.h"

class ray
{
public:
	point3 origin;
	vec3 direction;

	ray(){}
	ray(const point3& orig, const vec3& dir) : origin(orig), direction(dir){}

	point3 at(double t) const;

};