#pragma once

#include <cmath>
#include <iostream>

class vec3
{
public:
	double x, y, z;

	//vec3() : v{0,0,0} {}                                                 
	//vec3(double v0, double v1, double v2) : v{v0,v1,v2} {}

	vec3() : x(0), y(0), z(0) {}
	vec3(double xc, double yc, double zc) : x(xc), y(yc), z(zc) {}


	vec3 operator-() const { return vec3(-x, -y, -z); };
	//double operator[] (int i) const { return v[i]; }
	//double& operator[] (int i) { return v[i]; }
	
	//arithmetic functions
	vec3 operator+(const vec3& u) const;
	vec3& operator+=(const vec3& u);
	vec3 operator-(const vec3& u) const;
	vec3 operator*(const vec3& u) const;
	vec3 operator*(double t) const;       // multiply by scalar
	vec3 operator/(double t) const;
	
	vec3& operator*=(double t);

	double length() const;
	double length_square() const;

	void normalize();
	
};

using point3 = vec3;
using color = vec3;

double dot(const vec3& u, const vec3& v) ;
vec3 cross(const vec3& u, const vec3& v) ;
vec3 get_unitVector(const vec3& u);
