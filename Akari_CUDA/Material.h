#pragma once
#include "Ray.h"
#include "Hittable.h"

struct hit_record;

class material
{
public:
	virtual bool scatter(
		const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
	) const = 0;

};


class lambertian : public material
{
public:
	color albedo;
	lambertian(const color& a) : albedo(a) {}
	
	virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override
	{
		auto scatter_direction = rec.normal + get_unitVector(random_in_unit_sphere());
		if (scatter_direction.near_zero())
			scatter_direction = rec.normal;

		scattered = ray(rec.p, scatter_direction);
		attenuation = albedo;
		return true;
	}
};

class metal : public material
{
public:
	color albedo;
	double fuzz;
	metal(const color& a, double f) : albedo(a), fuzz(f<1?f:1) {}

	virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const  override
	{
		
		vec3 reflected = reflect(get_unitVector(r_in.direction), rec.normal);
		scattered = ray(rec.p, reflected + random_in_unit_sphere()*fuzz);
		attenuation = albedo;
		return (dot(scattered.direction, rec.normal) > 0);
	}
};