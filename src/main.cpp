#include <iostream>
#include <filesystem>
#include <algorithm>
#include <ctime>

#include "Mesh.hpp"
#include "World.hpp"
#include "Camera.hpp"
#include "Input.hpp"
#include "Screen.hpp"

int main()
{
    srand(time(NULL));
	SDL_Init(SDL_INIT_VIDEO);

    int HEIGHT = 600;
    int WIDTH = 800;
    float FOV = 60.0f;

    std::ifstream loadfrom("./settings/settings.txt");
    std::string line = "";

    while(std::getline(loadfrom,line))
    {
        if(line.size() < 3)
        {
            continue;
        }
    };

    // create screen
	Screen screen = Screen("superdisplay",WIDTH,HEIGHT);
    
    loadfrom.close();
    loadfrom.clear();
    loadfrom.open("./settings/importfile.txt");

    Input game = Input();
    
    Camera camera = Camera();
	game.setWorldCamera(&camera);

    World world = World();
    camera.setWorld(&world);

    Mesh* tempMesh = nullptr;
    
    while(std::getline(loadfrom,line))
    {
        if(line.size() == 0)
        {
            continue;
        }
        else if(line.at(0) == '/' && line.at(1) != '/')
        {
            continue;
        }

        if(line.substr(0,line.find(' ')) == "import")
        {
            fs::path path = line.substr(line.find(' ') + 1,line.size());

            if(fs::is_directory(path))
            {
                for (const fs::path & entry : fs::directory_iterator(path)) 
                {
                    if(entry.extension() != ".obj")
                    {
                        continue;
                    }

                    std::cout << entry << ": found mesh file." << std::endl;
                    tempMesh = Mesh::meshMaker(entry);
                    world.add(tempMesh,0);
                }
            }
            else if(path.extension() == ".obj")
            {
                std::cout << path << ": found mesh file." << std::endl;
                tempMesh = Mesh::meshMaker(path);
                world.add(tempMesh,0);
            }
        }
        else if(line.substr(0,line.find(' ')) == "scale")
        {
            if(!tempMesh)
            {
                continue;
            }
            
            line = line.substr(line.find(' ') + 1,line.size());
            tempMesh->setScale(0,std::stof(line.substr(0,line.find(' '))));

            line = line.substr(line.find(' ') + 1,line.size());
            tempMesh->setScale(1,std::stof(line.substr(0,line.find(' '))));

            line = line.substr(line.find(' ') + 1,line.size());
            tempMesh->setScale(2,std::stof(line));
        }
        else if(line.substr(0,line.find(' ')) == "rotation")
        {
            if(!tempMesh)
            {
                continue;
            }

            line = line.substr(line.find(' ') + 1,line.size());
            tempMesh->setRotation(0,std::stof(line.substr(0,line.find(' '))));

            line = line.substr(line.find(' ') + 1,line.size());
            tempMesh->setRotation(1,std::stof(line.substr(0,line.find(' '))));

            line = line.substr(line.find(' ') + 1,line.size());
            tempMesh->setRotation(2,std::stof(line));
            //tempMesh->normalizeRotation();
        }
        else if(line.substr(0,line.find(' ')) == "position")
        {
            if(!tempMesh)
            {
                continue;
            }

            line = line.substr(line.find(' ') + 1,line.size());
            tempMesh->setPos(0,std::stof(line.substr(0,line.find(' '))));

            line = line.substr(line.find(' ') + 1,line.size());
            tempMesh->setPos(1,std::stof(line.substr(0,line.find(' '))));

            line = line.substr(line.find(' ') + 1,line.size());
            tempMesh->setPos(2,std::stof(line));
        }
        else if(line.substr(0,line.find(' ')) == "setup")
        {
            if(!tempMesh)
            {
                continue;
            }

            line = line.substr(line.find(' ') + 1,line.size());
            if(line == "player")
            {
                std::cout << tempMesh << std::endl;
                game.setPlayerMesh(tempMesh);
            }
        }
    };

    world.setAllVisibility(true);
    std::cout << "Loaded " << world.numObj(true) << " visible meshes\n";
    
	// instantiate camera
	

	camera.setPos(0, 0);
	camera.setPos(1, 3);
	camera.setPos(2, 4); 
	camera.setForward(0, 0);
	camera.setForward(1, 0);
	camera.setForward(2, -1); 

    camera.setFov(FOV);

	bool running = true;
    SDL_Event event;
    bool keys[SDL_SCANCODE_COUNT] = {};
    bool trigger[SDL_SCANCODE_COUNT] = {};

    // delta time stuff
    Uint64 lastCounter = SDL_GetPerformanceCounter();
    float deltaTime = (SDL_GetPerformanceCounter() - lastCounter) / (float)SDL_GetPerformanceFrequency();

	while (running)
	{
		while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }

            if (event.type == SDL_EVENT_KEY_DOWN && !event.key.repeat)
            {
                keys[event.key.scancode] = true;
            }

            if (event.type == SDL_EVENT_KEY_UP)
            {
                keys[event.key.scancode] = false;
                trigger[event.key.scancode] = false;
            }
        }\
        game.input(keys,trigger,deltaTime);
        game.updateState(deltaTime);
        
        if (keys[SDL_SCANCODE_ESCAPE])
        {
            running = false;
        }
        
        
        // render every frame
        screen.buildBuffer(camera);
        screen.printBuffer();
        
        // update delta time
        Uint64 currentCounter = SDL_GetPerformanceCounter();
        deltaTime = (currentCounter - lastCounter) / (float)SDL_GetPerformanceFrequency();
        lastCounter = currentCounter;
	}

	screen.explode();
	world.explode();

	return 0;
}