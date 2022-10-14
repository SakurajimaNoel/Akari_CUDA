#pragma once

#include "Vec3.h"
#include "Ray.h"
#include "Hittable.h"
#include "Util.h"


int color_value(double pixelColor, int sample_size)
{
	auto scale = 1.0 / sample_size;
	pixelColor = sqrt(pixelColor * scale);           //gamma correction
	return static_cast<int>(256 * clamp(pixelColor, 0.0, 0.999));
}

color ray_color(const ray& r, const hittable& world, uint16_t depth)
{
	hit_record rec;

	if (depth <= 0) return color(0, 0, 0);

	if (world.hit(r, 0.0001, infinity, rec))
	{
		point3 target = rec.p + rec.normal + get_unitVector(random_in_unit_sphere());
		return ray_color(ray(rec.p, target - rec.p), world, depth-1) * 0.5;
		//return (rec.normal + color(1, 1, 1)) * 0.5;
	}

	vec3 unit_direction = get_unitVector(r.direction);
	auto t = 0.5 * (unit_direction.y + 1.0);
	return color(1.0, 1.0, 1.0) * (1.0 - t) + color(0.5, 0.7, 1.0) * t;
}