#ifndef COLOUR_H
#define COLOUR_H

#include <cstdint>
#include <iostream>

class Colour
{
    private: 
        uint8_t colour[4];
    public:
        Colour(uint8_t _r = 0, uint8_t _g = 0, uint8_t _b = 0, uint8_t _a = 255);
        uint8_t get(int index) const;

        uint32_t convert() const;

        void print();
};

const Colour COLOUR_BLANK = Colour(0,0,0,0);
const Colour COLOUR_BLACK = Colour(0,0,0,255);
const Colour COLOUR_WHITE = Colour(255,255,255,255);
const Colour COLOUR_GREY = Colour(128,128,128,255);
const Colour COLOUR_RED = Colour(255,0,0,255);
const Colour COLOUR_GREEN = Colour(0,255,0,255);
const Colour COLOUR_BLUE = Colour(0,0,255,255);
const Colour COLOUR_MAGENTA = Colour(255,0,255,255);

#endif