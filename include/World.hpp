#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "Mesh.hpp"



class World
{
    private: 
        std::vector<Mesh*> visible;
        std::vector<Mesh*> hidden;

        int checkProblems(Mesh*);

    public:
        
        /*  Status Codes:
        100 - changes successfully applied
        200 - mesh does not exist in this world
        201 - mesh already exists in this world (duplicate add)
        202 - mesh has no polygons
        203 - mesh has another problem (scale of 0,0,0)
        300 - mesh passed is a nullptr  */

        World();

        int numObj(bool visibility = true); // returns the number of objects in the hidden or visible vector
        Mesh* getObj(bool visibility, int index);
        
        void setAllVisibility(bool visibility = false);
        int setVisibility(bool visibility = false, Mesh* obj = nullptr);

        int add(Mesh* obj = nullptr, bool visibility = false); // adds a mesh to a visibility
        int remove(bool visibility = false, int index = 0); // deletes a mesh of a visibility at an index
        int remove(Mesh* obj = nullptr); // deletes a specific mesh
        int sweep(); // deletes meshes containing faulty behaviour

        void explode(); // deletes all meshes safely
};

#endif