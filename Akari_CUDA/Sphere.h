#pragma once
#include "Hittable.h"

class sphere : public hittable
{
public:
	point3 center;
	double radius;

	sphere() {}
	sphere(point3 cen, double r) : center(cen), radius(r) {};

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

};
