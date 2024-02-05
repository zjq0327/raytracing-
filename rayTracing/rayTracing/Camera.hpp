#pragma once

#include"Vector.hpp"

class Camera
{
public:
	Vector3f eyePos = Vector3f(0, 0, -1);
	Vector3f lookAt = Vector3f(0, 0, 0);
	Vector3f lookUp = Vector3f(0, 1, 0);
	float vfov = 90;
};