#ifndef SCREEN_H
#define SCREEN_H

#include <string>
#include <filesystem>
#include <fstream>
#include <cmath>

#include "SDL3/SDL.h"
#include "SDL3/SDL_gpu.h"
#include "Camera.hpp"

const int DIST_CONST = 200;

class Screen
{
    private:
        std::string name;
        int width;
        int height;
        SDL_Renderer* renderer;
        SDL_Window* window;
        SDL_Texture* texture;

        std::vector<float> zBuffer;

        void clearBuffer();
        void setColour(Colour colour);
    public:
        
        std::vector<uint32_t> frameBuffer;
        Screen(std::string _name = "superdisplay", int _width = 800, int _height = 600);


        static void print(std::string myString);

        int getWidth();
        int getHeight();

        
        void coatColour(Colour colour);

        void resizeBuffer();

        void buildBuffer(Camera& camera);
        void rasterizer(const Vec3& v0, const Vec3& v1, const Vec3& v2);

        void displaySplash(SDL_Surface* _splash);
        void printBuffer();
        
        void explode(); // deletes SDL3 window and renderer safely
};

#endif