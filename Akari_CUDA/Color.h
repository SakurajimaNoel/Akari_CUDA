#pragma once

#include "Vec3.h"
#include "Ray.h"
#include "Hittable.h"
#include "Util.h"


int color_value(double pixelColor, int sample_size)
{
	auto scale = 1.0 / sample_size;
	pixelColor *= scale;
	return static_cast<int>(256 * clamp(pixelColor, 0.0, 0.999));
}

color ray_color(const ray& r, const hittable& world)
{
	hit_record rec;
	if (world.hit(r, 0, infinity, rec))
	{
		return (rec.normal + color(1, 1, 1)) * 0.5;
	}

	vec3 unit_direction = get_unitVector(r.direction);
	auto t = 0.5 * (unit_direction.y + 1.0);
	return color(1.0, 1.0, 1.0) * (1.0 - t) + color(0.5, 0.7, 1.0) * t;
}