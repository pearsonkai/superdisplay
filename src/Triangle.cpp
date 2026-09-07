#include "Triangle.hpp"

Triangle::Triangle(Vec3 _a, Vec3 _b, Vec3 _c)
{
    points[0] = _a;
    points[1] = _b;
    points[2] = _c;
}

Vec3 Triangle::get(int index) const
{
    return points[index];
}