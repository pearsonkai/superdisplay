#include "../include/Vec3.hpp"

Vec3::Vec3(float _x, float _y, float _z, Colour _colour)
{
    values[0] = _x;
    values[1] = _y;
    values[2] = _z;

    colour = Colour(_colour);
}

float Vec3::get(int index) const
{
    return values[index];
}

void Vec3::set(Vec3 _set)
{
    for(int i = 0; i < 3; i++)
    {
        values[i] = _set.values[i];
    }
    return;
}

void Vec3::set(int index, float value)
{
    values[index] = value;
    return;
}







// basic manipulation
Vec3 Vec3::add(Vec3 _other)
{
    return Vec3(values[0] + _other.get(0), values[1] + _other.get(1), values[2] + _other.get(2), colour);
}

Vec3 Vec3::subtract(Vec3 _other)
{
    return Vec3(values[0] - _other.get(0), values[1] - _other.get(1), values[2] - _other.get(2), colour);
}

Vec3 Vec3::multiply(float scalar)
{
    return Vec3(values[0] * scalar, values[1] * scalar, values[2] * scalar, colour);
}

Vec3 Vec3::divide(float scalar)
{
    return Vec3(values[0] / scalar, values[1] / scalar, values[2] / scalar, colour);
}





// vector math
Vec3 Vec3::cross(Vec3 _other)
{
    float a = values[1] * _other.get(2) - values[2] * _other.get(1);
    float b = values[0] * _other.get(2) - values[2] * _other.get(0);
    float c = values[0] * _other.get(1) - values[1] * _other.get(0);
    
    return Vec3(a,b,c,COLOUR_BLANK);
}

float Vec3::dot(Vec3 _other)
{
    return values[0] * _other.get(0) + values[1] * _other.get(1) + values[2] * _other.get(2);
}

float Vec3::magnitude()
{
    return std::sqrt(dot( (*this) ));
}

Vec3 Vec3::normalize()
{
    float value = magnitude();

    if(value == 0)
    {
        return Vec3();
    }

    Vec3 normalizedVec = Vec3(values[0] / value, values[1] / value, values[2] / value);

    return normalizedVec;
}

Vec3 Vec3::project(Vec3 onto)
{
    float scalar = dot(onto) / dot((*this));

    return onto.multiply(scalar);
}

Vec3 Vec3::applyRotation(Vec3 forward, Vec3 up, Vec3 right)
{
    // Transform this point into the camera's local coordinate system.
    // The right vector is the X axis, up is the Y axis, and forward is the Z axis.
    float x = dot(right);
    float y = dot(up);
    float z = dot(forward);

    return Vec3(x, y, z, colour);
}

float Vec3::edge(Vec3 a, Vec3 b, Vec3 c)
{
    return (c.get(0) - a.get(0))*(b.get(1) - a.get(1)) - (c.get(1) - a.get(1))*(b.get(0) - a.get(0));
}










Colour Vec3::getColour() const
{
    return colour;
}

void Vec3::setColour(Colour _colour)
{
    colour = _colour;
    return;
}

void Vec3::printInfo()
{
    std::cout << "Vec3: (" << (float)values[0] << "," << (float)values[1] << "," << (float)values[2] << ") Colour: ";
    colour.print();
}