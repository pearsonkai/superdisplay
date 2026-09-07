#include "World.hpp"

/*  
    Status Codes:
100 - changes successfully applied

200 - mesh does not exist in this world
201 - mesh already exists in this world (duplicate add)
202 - mesh has no polygons
203 - mesh has another problem (scale of 0,0,0)
300 - mesh passed is a nullptr  
*/

World::World()
{
    visible = std::vector<Mesh*>();
    hidden = std::vector<Mesh*>();
}

int World::checkProblems(Mesh* check)
{
    if(check == nullptr)
    {
        return 300;
    }

    if(check->numTri() == 0)
    {
        return 202;
    }

    Vec3 scale = check->getScale();
    if(scale.get(0) == 0 && scale.get(1) == 0 && scale.get(2) == 0)
    {
        return 203;
    }

    return 100;
}

int World::numObj(bool visibility)
{
    if(visibility)
    {
        return visible.size();
    }
    
    return hidden.size();
}

Mesh* World::getObj(bool visibility, int index)
{
    if(visibility)
    {
        return visible.at(index);
    }
    
    return hidden.at(index);
}

void World::setAllVisibility(bool visibility)
{
    // Move all meshes from the source list to the destination list.
    if (visibility)
    {
        // make everything visible
        if (!hidden.empty())
        {
            visible.insert(visible.end(), hidden.begin(), hidden.end());
            hidden.clear();
        }
    }
    else
    {
        // make everything hidden
        if (!visible.empty())
        {
            hidden.insert(hidden.end(), visible.begin(), visible.end());
            visible.clear();
        }
    }
}

int World::setVisibility(bool visibility, Mesh* obj)
{
    if (obj == nullptr)
    {
        return 300;
    }

    if (visibility)
    {
        // target: make visible
        // already visible?
        for (Mesh* m : visible)
        {
            if (m == obj) return 201;
        }

        // find in hidden and move
        for (size_t i = 0; i < hidden.size(); ++i)
        {
            if (hidden.at(i) == obj)
            {
                visible.push_back(obj);
                hidden.erase(hidden.begin() + i);
                return 100;
            }
        }
    }
    else
    {
        // target: make hidden
        for (Mesh* m : hidden)
        {
            if (m == obj) return 201;
        }

        for (size_t i = 0; i < visible.size(); ++i)
        {
            if (visible.at(i) == obj)
            {
                hidden.push_back(obj);
                visible.erase(visible.begin() + i);
                return 100;
            }
        }
    }

    // mesh doesn't exist in the world
    return 200;
}

int World::add(Mesh* obj, bool visibility)
{
    int hiddensize = hidden.size();
    for(int i = 0; i < hiddensize; i++)
    {
        if(hidden.at(i) == obj)
        {
            return 201;
        }
    }

    int visiblesize = visible.size();
    for(int i = 0; i < visiblesize; i++)
    {
        if(visible.at(i) == obj)
        {
            return 201;
        }
    }


    if(visibility)
    {
        visible.push_back(obj);
    }
    else
    {
        hidden.push_back(obj);
    }

    return 100;
}

int World::remove(bool visibility, int index)
{
    if (index < 0) return 200;

    if (visibility)
    {
        if (index >= (int)visible.size()) return 200;
        delete visible.at(index);
        visible.erase(visible.begin() + index);
        return 100;
    }
    else
    {
        if (index >= (int)hidden.size()) return 200;
        delete hidden.at(index);
        hidden.erase(hidden.begin() + index);
        return 100;
    }
} // deletes a mesh of a visibility at an index

int World::remove(Mesh* obj)
{
    int size = visible.size();
    for(int i = 0; i < size; i++)
    {
        if(visible.at(i) == obj)
        {
            delete visible.at(i);
            visible.erase(visible.begin() + i);
            return 100;
        }
    }
    size = hidden.size();
    for(int i = 0; i < size; i++)
    {
        if(hidden.at(i) == obj)
        {
            delete hidden.at(i);
            hidden.erase(hidden.begin() + i);
            return 100;
        }
    }

    return 200;
} // deletes a specific mesh

int World::sweep()
{
    int size = visible.size();
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            if(i != j && visible.at(i) == visible.at(j))
            {
                delete visible.at(j);
                visible.erase(visible.begin() + j);
                j--;
            }
        }
    }

    size = hidden.size();
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            if(i != j && hidden.at(i) == hidden.at(j))
            {
                delete hidden.at(j);
                hidden.erase(hidden.begin() + j);
                j--;
            }
        }
    }

    return 100;
}

// deletes all meshes safely
void World::explode()
{
    for(int i = visible.size() - 1; 0 <= i; i--)
    {
        delete visible.at(i);
        visible.erase(visible.begin() + i);
    }

    for(int i = hidden.size() - 1; 0 <= i; i--)
    {
        delete hidden.at(0);
        hidden.erase(hidden.begin() + i);
    }
}