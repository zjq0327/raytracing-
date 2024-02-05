#pragma once

#include "Ray.hpp"
#include"Object.hpp"

class Sphere:public Object
{
public:
	Sphere(Vector3f c, float r):center(c),radius(r)
	{}

	virtual bool hit(const Ray& r, float& tnear,hit_record& hitRecord)const
	{
		Vector3f oc = r.origin() - center;
		float a = dotProduct(r.direction(), r.direction());
		float b = 2.0 * dotProduct(r.direction(), oc);
		float c = dotProduct(oc, oc) - radius * radius;

		float t0, t1;
		if (!solveQuadratic(a, b, c, t0, t1))
			return false;
		if (t0 < 0)
			t0 = t1;
		if (t0 < 0)
			return false;
		tnear = t0;

		hitRecord.point = tnear * r.direction() + r.origin();
		hitRecord.normal = (hitRecord.point - center) / radius;

		return true;

	}

private:
	Vector3f center;
	float radius;
};