#pragma once
#include <fstream>

using namespace std;

#define M_PI 3.14159265358979323846

constexpr float kInfinity = std::numeric_limits<float>::max();


inline float clamp(const float& lo, const float& hi, const float& v)
{
    return std::max(lo, std::min(hi, v));
}

inline float deg2rad(const float& deg)
{
    return deg * M_PI / 180.0;
}   


// 1元2次方程组
inline bool solveQuadratic(const float& a, const float& b, const float& c, float& x0, float& x1)
{
    float discr = b * b - 4 * a * c;
    if (discr < 0)
        return false;
    else if (discr == 0)
        x0 = x1 = -0.5 * b / a;
    else
    {
        float q = (b > 0) ? -0.5 * (b + sqrt(discr)) : -0.5 * (b - sqrt(discr));
        x0 = q / a;
        x1 = c / q;
    }
    if (x0 > x1)
        std::swap(x0, x1);
    return true;
}


enum MaterialType
{
    DIFFUSE_AND_GLOSSY,
    REFLECTION_AND_REFRACTION,
    REFLECTION
};



// Compute reflection direction
inline Vector3f reflect(const Vector3f& I, const Vector3f& N)
{
    return I - 2 * dotProduct(I, N) * N;
}
