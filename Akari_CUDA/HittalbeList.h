#pragma once
#include "Hittable.h"
#include <memory>
#include <vector>

class hittableList : public hittable
{
public:
	std::vector<std::shared_ptr<hittable>> objects;

	hittableList(){}
	hittableList(std::shared_ptr<hittable>object) { add(object); }

	void clear();
	void add(std::shared_ptr<hittable> object);
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;


};