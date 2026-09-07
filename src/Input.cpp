#include "Input.hpp"
#include <cmath>

Input::Input()
{
    pV = Vec3(0,0,0,COLOUR_BLACK);
    playerMesh = nullptr;
    trainMesh = nullptr;
}

void Input::setWorldCamera(Camera* _camera)
{
    worldCamera = _camera;
}

void Input::setPlayerMesh(Mesh* _player)
{
    playerMesh = _player;
}

void Input::setTrainMesh(Mesh* _train)
{
    trainMesh = _train;
}

void Input::updateState(float _deltaTime)
{
    if(!playerMesh)
    {
        return;
    }

    playerMesh->setPos(0,playerMesh->getPos().get(0) + pV.get(0) * _deltaTime);
    playerMesh->setPos(1,playerMesh->getPos().get(1) + pV.get(1) * _deltaTime);
    playerMesh->setPos(2,playerMesh->getPos().get(2) + pV.get(2) * _deltaTime);
    
    if(playerMesh->getPos().get(1) < 0)
    {
        playerMesh->setPos(1,0);
        pV.set(1,0);
    }
    else
    {
        pV.set(1,pV.get(1) - 6 * _deltaTime);
    }


    if(abs(pV.get(0)) < 0.005 || playerMesh->getPos().get(1) == 0)
    {
        pV.set(0,0);
    }
    else
    {
        pV.set(0,pV.get(0) * SLOW_RATE);
    }

    if(abs(pV.get(2)) < 0.005 || playerMesh->getPos().get(1) == 0)
    {
        pV.set(2,0);
    }
    else
    {
        pV.set(2,pV.get(2) * SLOW_RATE);
    }
}

void Input::input(bool _key[], bool _trigger[], float _deltaTime)
{
    if (_key[SDL_SCANCODE_W] || _key[SDL_SCANCODE_S] || _key[SDL_SCANCODE_A] || _key[SDL_SCANCODE_D])
    {
        Vec3 camPos = worldCamera->getPos();
        Vec3 forward = worldCamera->getForward().normalize();
        Vec3 right = worldCamera->getRight().normalize();
        Vec3 moveDelta(0, 0, 0);
        float speed = 3.0f * _deltaTime;

        if (_key[SDL_SCANCODE_W])
        {
            moveDelta = moveDelta.add(forward.multiply(speed));
        }
        if (_key[SDL_SCANCODE_S])
        {
            moveDelta = moveDelta.add(forward.multiply(-speed));
        }
        if (_key[SDL_SCANCODE_A])
        {
            moveDelta = moveDelta.add(right.multiply(-speed));
        }
        if (_key[SDL_SCANCODE_D])
        {
            moveDelta = moveDelta.add(right.multiply(speed));
        }

        camPos = camPos.add(moveDelta);
        worldCamera->setPos(0, camPos.get(0));
        worldCamera->setPos(1, camPos.get(1));
        worldCamera->setPos(2, camPos.get(2));
    }
    if (_key[SDL_SCANCODE_V] || _key[SDL_SCANCODE_B])
    {
        Vec3 forward = worldCamera->getForward().normalize();
        Vec3 up = worldCamera->getUp().normalize();
        Vec3 right = up.cross(forward).normalize();
        float yawSpeed = 60.0f * _deltaTime;
        float yawDirection = 0.0f;

        if (_key[SDL_SCANCODE_V])
        {
            yawDirection += 1.0f;
        }
        if (_key[SDL_SCANCODE_B])
        {
            yawDirection -= 1.0f;
        }

        float cosA = std::cos(yawSpeed * std::acos(-1) / 180.0f);
        float sinA = std::sin(yawSpeed * std::acos(-1) / 180.0f);

        Vec3 newForward = forward.multiply(cosA).add(right.multiply(yawDirection * sinA)).normalize();
        Vec3 newRight = up.cross(newForward).normalize();

        worldCamera->setForward(0, newForward.get(0));
        worldCamera->setForward(1, newForward.get(1));
        worldCamera->setForward(2, newForward.get(2));
        worldCamera->setRight(0, newRight.get(0));
        worldCamera->setRight(1, newRight.get(1));
        worldCamera->setRight(2, newRight.get(2));
    }

    if (_key[SDL_SCANCODE_X])
    {
        worldCamera->moveTowards(worldCamera->getForward(),-2 * _deltaTime);
    }
    if (_key[SDL_SCANCODE_C])
    {
        worldCamera->moveTowards(worldCamera->getForward(),2 * _deltaTime);
    }
    if (_key[SDL_SCANCODE_G] && !_trigger[SDL_SCANCODE_G])
    {
        _trigger[SDL_SCANCODE_G] = true;
        worldCamera->setCulling(!worldCamera->getCulling());
    }
    if (_key[SDL_SCANCODE_U] && !_trigger[SDL_SCANCODE_G])
    {
        _trigger[SDL_SCANCODE_G] = true;
        std::cout << playerMesh << std::endl;
    }
    if(_key[SDL_SCANCODE_J])
    {
        pV.set(0,-7);
    }
    if(_key[SDL_SCANCODE_H])
    {
        pV.set(0,7);
    }
}