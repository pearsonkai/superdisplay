#include "Colour.hpp"

Colour::Colour(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a)
{
    colour[0] = _r;
    colour[1] = _g;
    colour[2] = _b;
    colour[3] = _a;
}

uint8_t Colour::get(int index) const
{
    return colour[index];
}

uint32_t Colour::convert() const
{
    // converts the Colour class to a uint32_t format, usable with SDL3 Textures
    return ((uint32_t)colour[3] << 24) | ((uint32_t)colour[0] << 16) | ((uint32_t)colour[1] << 8) | ((uint32_t)colour[2]);
}

void Colour::print()
{
    std::cout << "(" << (int)colour[0] << "," << (int)colour[1] << "," << (int)colour[2] << "," << (int)colour[3] << ")" << std::endl;
}