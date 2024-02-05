#pragma once

#include "Vector.hpp"
#include "global.hpp"
#include "Ray.hpp"

struct hit_record;


class Object
{
public:

	Object()
		: materialType(DIFFUSE_AND_GLOSSY)
		, ior(1.3)
		, Kd(0.8)
		, Ks(0.2)
		, diffuseColor(0.2)
		, specularExponent(25)
	{}

	virtual bool hit(const Ray& r, float& tnear,hit_record& hitRecord)const = 0;

	virtual virtual ~Object() = default;

	virtual Vector3f evalDiffuseColor() const
	{
		return diffuseColor;
	}


	MaterialType materialType;
	float ior;
	float Kd, Ks;
	Vector3f diffuseColor;
	float specularExponent;
};



struct hit_record
{
	Vector3f point;
	Vector3f normal;
	shared_ptr<Object> hit_obj;
};