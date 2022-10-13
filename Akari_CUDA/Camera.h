#pragma once
#include "Ray.h"

class camera
{
public:
	camera();
	ray get_ray(double u, double v) const;
private:
	point3 origin;
	point3 btm_lft_crnr;
	vec3 horizontal;
	vec3 vertical;
};