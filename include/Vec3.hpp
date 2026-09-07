#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <cstdint>
#include <cmath>

#include "Colour.hpp"

class Vec3
{
    private:
        float values[3];
        Colour colour;
    public:
        Vec3(float _x = 0, float _y = 0, float _z = 0, Colour _colour = COLOUR_BLACK);
        float get(int index) const;
        void set(Vec3 _set);
        void set(int index, float value);


        // basic manipulation
        Vec3 add(Vec3 _other);
        Vec3 subtract(Vec3 _other);
        Vec3 multiply(float scalar);
        Vec3 divide(float scalar);

        //vector math
        Vec3 cross(Vec3 _other);
        float dot(Vec3 _other);
        float magnitude();
        Vec3 normalize();
        Vec3 project(Vec3 onto);
        Vec3 applyRotation(Vec3 forward, Vec3 up, Vec3 right);
        static float edge(Vec3 a, Vec3 b, Vec3 c);
        
        Colour getColour() const;
        void setColour(Colour _colour = COLOUR_BLANK);

        void printInfo();
};

#endif