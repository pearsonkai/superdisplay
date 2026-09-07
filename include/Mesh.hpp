#ifndef MESH_H
#define MESH_H

#include <vector>
#include <filesystem>
#include <fstream>
#include <string>
#include <conio.h>
#include <ctime>

#include "Triangle.hpp"

namespace fs = std::filesystem;

class Mesh
{
    private:
        std::string name;
        std::vector<Triangle> triangles;
        Vec3 * pos; // world position
        Vec3 * scale; // scale (baseline is (1,1,1))
        Vec3 * rotation; // rotation is in degrees
        Vec3 centroid;
        bool ownsMembers[3]; // represents if this mesh is responsible for its own pos, scale, and rotation (and has to delete them)
    public:
        Mesh();
        Mesh(std::string _name, Vec3 &_pos, Vec3 &_scale, Vec3 &_rotation, bool _ownsMember[3]);

        ~Mesh();

        int numTri(); // returns number of triangles in vector
        Triangle getTri(int index); // returns triangle at index in vector

        std::string getName();
        void setName(std::string _name);

        void add(Triangle _tri);
        Triangle remove(int index = 0);

        Vec3 getPos();
        void setPos(int index, float value);
        void setPos(Vec3 set);
        Vec3 applyPos(Vec3 apply);
        void overridePos(Vec3* set, bool ownPos);

        Vec3 getScale();
        void setScale(int index, float value);
        void setScale(Vec3 set);
        Vec3 applyScale(Vec3 apply);
        void overrideScale(Vec3* set, bool ownScale);

        
        
        Vec3 getRotation();
        void setRotation(int index, float value);
        void setRotation(Vec3 set);
        void overrideRotation(Vec3* set, bool ownRotation);

        void normalizeRotation();
        Vec3 applyRotation(Vec3 apply);

        double computeAverageVertex(int index); // find the average x (0), y (1), or z (2) position in a mesh
        Vec3 computeCentroid();
        Vec3 getCentroid();
        void overrideCenteroid(Vec3 set);

        Vec3 localize(Vec3 apply);

        static Mesh* meshMaker(fs::path _meshfile);
};

#endif