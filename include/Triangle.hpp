#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Vec3.hpp"

class Triangle
{
    private:
        Vec3 points[3];
    public:
        Triangle(Vec3 _a = Vec3(), Vec3 _b = Vec3(), Vec3 _c = Vec3());
        Vec3 get(int index) const;
};

#endif