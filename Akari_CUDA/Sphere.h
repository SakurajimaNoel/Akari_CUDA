#pragma once
#include "Hittable.h"

class sphere : public hittable
{
public:
	point3 center;
	double radius;
	std::shared_ptr<material> mat_ptr;
	sphere() {}
	sphere(point3 cen, double r, std::shared_ptr<material> m) : center(cen), radius(r), mat_ptr(m) {};

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

};
