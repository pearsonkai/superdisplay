#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>

#include "Vec3.hpp"
#include "World.hpp"

/*
NOTE:

X+ right
Y+ up
Z+ forward

*/

class Camera
{
    private:
        World* world;

        Vec3 pos;
        Vec3 forward;
        Vec3 up;
        Vec3 right;

        float fov;

        bool culling;
        bool lock; // lock forward vector (stable capture of a single point)
    public:
        Camera(World* _world = nullptr, Vec3 _pos = Vec3(0,0,0,COLOUR_BLANK),Vec3 _forward = Vec3(1,0,0,COLOUR_BLANK), Vec3 _up = Vec3(0,1,0,COLOUR_BLANK),Vec3 _right = Vec3(0,0,1,COLOUR_BLANK),float _fov = 90);

        World* getWorld();
        void setWorld(World* _world);

        Vec3 getPos();
        void setPos(int index, float value);
        void moveTowards(Vec3 point, float distance);

        Vec3 getForward();
        void setForward(int index, float value);
        
        Vec3 getUp();
        void setUp(int index, float value);

        Vec3 getRight();
        void setRight(int index, float value);

        float getFov();
        void setFov(float _fov);

        bool getCulling();
        void setCulling(bool _culling);

        bool getLock();
        void setLock(bool _lock);

        void normalizeForward();
        void normalizeRight();
        void normalizeUp();
        void updateRight();

        Vec3 project(float scale, Vec3 point);
};

#endif