#pragma once

#include"Vector.hpp"

class Ray {
public:
    Ray() {}

    Ray(const Vector3f& origin, const Vector3f& direction) : orig(origin), dir(direction) {}

    Vector3f origin() const { return orig; }
    Vector3f direction() const { return dir; }

    Vector3f at(float t) const {
        return orig + t * dir;
    }

private:
    Vector3f orig;
    Vector3f dir;
};