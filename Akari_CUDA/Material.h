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

class dielectric : public material
{
public:
	double ir;

	dielectric(double refraction_index) : ir(refraction_index){}
	virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const  override
	{
		attenuation = color(1.0, 1.0, 1.0);
		double refraction_ratio = rec.front_face ? (1.0 / ir) : ir;
		vec3 unit_dir = get_unitVector(r_in.direction);

		double cos_theta = fmin(dot(-unit_dir, rec.normal), 1.0);
		double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

		bool cant_refract = refraction_ratio * sin_theta > 1.0;
		vec3 dir;

		if (cant_refract || reflectance(cos_theta,refraction_ratio) > random_double())
			dir = reflect(unit_dir, rec.normal);
		else
			dir = refract(unit_dir, rec.normal, refraction_ratio);

		scattered = ray(rec.p, dir);
		return true;
	}
private:
	static double reflectance(double cosine, double ref_idx)
	{
		auto r0 = (1 - ref_idx) / (1 + ref_idx);
		r0 = r0 * r0;
		return r0 + (1 - r0) * pow((1 - cosine), 5);
	}
};