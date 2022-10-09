#pragma once

#include "Vec3.h"
#include "Ray.h"

int color_value(double pixelColor)
{
	return static_cast<int>(255.999 * pixelColor);
}

color ray_color(const ray& r)
{
	vec3 unit_direction = get_unitVector(r.direction);
	auto t = 0.5 * (unit_direction.y + 1.0);
	return color(1.0, 1.0, 1.0) * (1.0 - t) + color(0.5, 0.7, 1.0) * t;
}