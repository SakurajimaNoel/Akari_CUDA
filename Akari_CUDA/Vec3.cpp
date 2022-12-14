#include "Vec3.h"

vec3 vec3::operator+(const vec3& u) const
{
	return vec3(x + u.x, y + u.y, z + u.z);
}
vec3& vec3::operator+=(const vec3& u)
{
	x += u.x;	y += u.y;	z += u.z;
	return *this;
}
vec3 vec3::operator-(const vec3& u) const
{
	return vec3(x - u.x, y - u.y, z - u.z);
}
vec3 vec3::operator*(const vec3& u) const
{
	return vec3(x * u.x, y * u.y, z * u.z);
}
vec3 vec3::operator*(double t) const
{
	return vec3(x * t, y * t, z * t);
}
vec3 vec3::operator/(double t) const
{
	return vec3(x * 1 / t, y * 1 / t, z * 1 / t);
}
vec3& vec3::operator*=(double t)
{
	x *= t; y *= t; z *= t; 
	return *this;
}
double dot(const vec3 & u, const vec3& v)
{
	return v.x * u.x + v.y * u.y + v.z * u.z;
}
vec3 cross(const vec3& u, const vec3& v) 
{
	return vec3(v.y * u.z - v.z * u.y, v.z * u.x - v.x * u.z, v.x * u.y - v.y * u.x);
}

double vec3::length() const
{
	return std::sqrt(x * x + y * y + z * z);
}

double vec3::length_square() const
{
	return (x * x + y * y + z * z);
}

void vec3::normalize() 
{
	double l = 1.0 / length();
	x *= l; y *= l; z *= l;
}

vec3 get_unitVector(const vec3& u)
{
	double l = 1.0 / u.length();
	return vec3(u.x * l, u.y * l, u.z * l);
}

vec3 vec3::random()
{
	return vec3(random_double(), random_double(), random_double());
}

vec3 vec3::random(double min, double max)
{
	return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
}

vec3 random_in_unit_sphere()
{
	while (true)
	{
		auto p = vec3::random(-1, 1);
		if (p.length_square() >= 1) continue;
		return p;
	}
}

vec3 reflect(const vec3& v, const vec3& n)
{
	return v - n * dot(v, n) * 2 ;
}

vec3 refract(const vec3& v, const vec3& n, double eta)
{
	auto cos_theta = fmin(dot(-v, n), 1.0);
	vec3 r_perp = (v + n * cos_theta) * eta;
	vec3 r_parallel = n * -sqrt(fabs(1.0 - r_perp.length_square()));
	return r_perp + r_parallel;
}

const bool vec3::near_zero() 
{
	const auto s = 1e-8;
	return(fabs(x < s) && fabs(y < s) && fabs(z < s));
}
