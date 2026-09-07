#ifndef INPUT_H
#define INPUT_H

#include "Camera.hpp"
#include "Mesh.hpp"
#include "SDL3/SDL.h"

const float SLOW_RATE = 0.97;

class Input
{
    private:
        Camera* worldCamera;
        
        Mesh* playerMesh;
        Vec3 pV;

        Mesh* trainMesh;
        
    public:
        Input();
        
        void setWorldCamera(Camera* _camera);
        void setPlayerMesh(Mesh* _player);
        void setTrainMesh(Mesh* _train);

        void updateState(float _deltaTime);
        void input(bool _key[], bool _trigger[], float _deltaTime);
};

#endif