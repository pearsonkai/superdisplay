#include <iostream>
#include <cmath>
#include <numbers>

#include "Mesh.hpp"

Mesh::Mesh()
{
    name = "default name";
    triangles = std::vector<Triangle>();
    pos = new Vec3(0,0,0);
    scale = new Vec3(1,1,1);
    rotation = new Vec3(0,0,0);
    
    for(int i = 0; i < 3; i++)
    {
        ownsMembers[i] = true;
    }
    computeCentroid();
}

Mesh::Mesh(std::string _name, Vec3& _pos, Vec3& _scale, Vec3& _rotation, bool _ownsMembers[3])
{
    name = _name;
    triangles = std::vector<Triangle>();
    if(ownsMembers[0])
    {
        pos = new Vec3(_pos);
    }
    else
    {
        pos = &_pos;
    }

    if(ownsMembers[1])
    {
        scale = new Vec3(_scale);
    }
    else
    {
        scale = &_scale;
    }

    if(ownsMembers[2])
    {
        rotation = new Vec3(_rotation);
    }
    else
    {
        rotation = &_rotation;
    }

    for(int i = 0; i < 3; i++)
    {
        ownsMembers[i] = _ownsMembers[i];
    }
    computeCentroid();
}

Mesh::~Mesh()
{
    if(ownsMembers[0])
    {
        delete pos;
    }

    if(ownsMembers[1])
    {
        delete scale;
    }

    if(ownsMembers[2])
    {
        delete rotation;
    }
}

int Mesh::numTri()
{
    return triangles.size();
}

Triangle Mesh::getTri(int index)
{
    return triangles.at(index);
}

void Mesh::add(Triangle _tri)
{
    triangles.push_back(_tri);
    return;
}

Triangle Mesh::remove(int index)
{
    Triangle myTriangle = triangles.at(index);
    triangles.erase(triangles.begin() + index);
    return myTriangle;
}

std::string Mesh::getName()
{
    return name;
}

void Mesh::setName(std::string _name)
{
    name = _name;
}
    
Vec3 Mesh::getPos()
{
    return (*pos);
}

void Mesh::setPos(int index, float value)
{
    pos->set(index, value);
}

void Mesh::setPos(Vec3 set)
{
    pos->set(set);
}

Vec3 Mesh::applyPos(Vec3 apply)
{
    apply.add((*pos));

    return apply;
}

void Mesh::overridePos(Vec3* set, bool ownPos)
{
    if(set == nullptr)
    {
        return;
    }

    if(ownsMembers[0])
    {
        delete pos;
    }

    ownsMembers[0] = ownPos;
    pos = set;
}

Vec3 Mesh::getScale()
{
    return (*scale);
}

void Mesh::setScale(int index, float value)
{
    scale->set(index, value);
}

void Mesh::setScale(Vec3 set)
{
    scale->set(set);
}

Vec3 Mesh::applyScale(Vec3 apply)
{
    apply = apply.subtract(centroid);

    apply.set(0, apply.get(0) * scale->get(0));
    apply.set(1, apply.get(1) * scale->get(1));
    apply.set(2, apply.get(2) * scale->get(2));

    apply = apply.add(centroid);

    return apply;
}

void Mesh::overrideScale(Vec3* set, bool ownScale)
{
    if(set == nullptr)
    {
        return;
    }

    if(ownsMembers[1])
    {
        delete scale;
    }
    
    ownsMembers[1] = ownScale;
    scale = set;
}

Vec3 Mesh::getRotation()
{
    return (*rotation);
}

void Mesh::setRotation(int index, float value)
{
    rotation->set(index,value);
}

void Mesh::setRotation(Vec3 set)
{
    rotation->set(set);
}

void Mesh::normalizeRotation()
{
    for(int i = 0; i < 3; i++)
    {
        float angle = rotation->get(i);

        angle = fmod(angle, 360.0f);

        if(angle < 0)
        {
            angle += 360.0f;
        }

        rotation->set(i, angle);
    }
    
    return;
}

void Mesh::overrideRotation(Vec3* set, bool ownRotation)
{
    if(set == nullptr)
    {
        return;
    }

    if(ownsMembers[2])
    {
        delete rotation;
    }
    
    ownsMembers[2] = ownRotation;
    pos = set;
}


double Mesh::computeAverageVertex(int index)
{
    if(index > 3 || index < 0)
    {
        return 0;
    }

    double sum;
    int count = 0;
    int size = triangles.size();
    for(int i = 0; i < size; i++) 
    {
        for(int j = 0; j < 3; j++)
        {
            sum += triangles.at(i).get(j).get(index);
            count++;
        }
    }

    if(count == 0)
    {
        return 0;
    }

    return (sum / count);
}

Vec3 Mesh::computeCentroid()
{
    centroid.set(Vec3(computeAverageVertex(0),computeAverageVertex(1),computeAverageVertex(2)));
    return centroid;
}

Vec3 Mesh::getCentroid()
{
    return centroid;
}

void Mesh::overrideCenteroid(Vec3 set)
{
    centroid.set(set);
}



Vec3 Mesh::applyRotation(Vec3 apply)
{
    float x = apply.get(0);
    float y = apply.get(1);
    float z = apply.get(2);

    float xRot = rotation->get(0) + 270.0f;
    float cx = std::cos(xRot * std::acos(-1) / 180.0f);
    float sx = std::sin(xRot * std::acos(-1) / 180.0f);
    float cy = std::cos(rotation->get(1) * std::acos(-1) / 180.0f);
    float sy = std::sin(rotation->get(1) * std::acos(-1) / 180.0f);
    float cz = std::cos(rotation->get(2) * std::acos(-1) / 180.0f);
    float sz = std::sin(rotation->get(2) * std::acos(-1) / 180.0f);

    float newX = x * (cy * cz) + y * (sx * sy * cz - cx * sz) + z * (cx * sy * cz + sx * sz);
    float newY = x * (cy * sz) + y * (sx * sy * sz + cx * cz) + z * (cx * sy * sz - sx * cz);
    float newZ = x * (-sy) + y * (sx * cy) + z * (cx * cy);

    apply.set(0, newX);
    apply.set(1, newY);
    apply.set(2, newZ);

    return apply;
}

Vec3 Mesh::localize(Vec3 apply)
{
    apply = applyScale(apply);
    apply = applyRotation(apply);
    apply = applyPos(apply);

    return apply;
}











Mesh* Mesh::meshMaker(fs::path _meshfile)
{
	std::ifstream in(_meshfile);
	std::ifstream other;

    if(!in)
    {
        std::cout << "Cannot open file: " << _meshfile;
        getch();
        return nullptr;
    }
    
	std::vector<Vec3> points;
    
    fs::path path;
	std::vector<std::string> mtlnames;
    std::vector<Colour> material;
    int currentMaterial = 0;


    
    
    Mesh* mesh = new Mesh();
    std::string name = "";

    std::string line = "";
    float p[3];
    int t[4];
    Vec3 v[3];
    Triangle myTri;

    while (std::getline(in,line))
	{
        switch(line[0])
        {
            case '#':
                continue;
            
            case 'm':
                if(line.substr(0,line.find(' ')) != "mtllib")
                {
                    continue;
                }
                line = line.substr(line.find(' ') + 1,line.size());
                path = _meshfile.parent_path() / line;
                if(path.extension() != ".mtl")
                {
                    continue;
                }
                std::cout << _meshfile << ": found material file: " << line << std::endl;
                
                other = std::ifstream (path);

                while(std::getline(other,line))
                {
                    if(line.substr(0,line.find(' ')) == "newmtl")
                    {
                        line = line.substr(line.find(' ') + 1,line.size());
                        std::cout << "Defined material: " + line << std::endl;
                        mtlnames.resize(mtlnames.size() + 1);
                        material.resize(material.size() + 1);
                        mtlnames.at(mtlnames.size() - 1) = line;
                        
                    }
                    else if(line.substr(0,line.find(' ')) == "Kd")
                    {
                        line = line.substr(line.find(' ') + 1,line.size());

                        p[0] = std::stof(line.substr(0,line.find(' ')));
                        line = line.substr(line.find(' ') + 1,line.size());

                        p[1] = std::stof(line.substr(0,line.find(' ')));
                        line = line.substr(line.find(' ') + 1,line.size());
                        
                        p[2] = std::stof(line);
                        
                        material.at(material.size() - 1) = Colour(255.0f*p[0],255.0f*p[1],255.0f*p[2],255);
                        std::cout << "Updated material: " << mtlnames.at(material.size() - 1) << " to ";
                        material.at(material.size() - 1).print();


                    }
                }

                break;

            case 'u':
                if(line.substr(0,line.find(' ')) != "usemtl")
                {
                    continue;
                }
                
                line = line.substr(line.find(' ') + 1,line.size());
                std::cout << "Looking for material: " + line << std::endl;
                t[0] = mtlnames.size();
                for(t[1] = 0; t[1] < t[0]; t[1]++)
                {
                    if(mtlnames.at(t[1]) == line)
                    {
                        currentMaterial = t[1];
                        
                        std::cout << "Found and set current material: " << mtlnames.at(currentMaterial) << " ";
                        material.at(currentMaterial).print();
                        
                        break;
                    }
                }

                break;

            case 'v':
                line = line.substr(line.find(' ') + 1,line.size());

                p[0] = std::stof(line.substr(0,line.find(' ')));
                line = line.substr(line.find(' ') + 1, line.size());

                p[1] = std::stof(line.substr(0,line.find(' ')));
                line = line.substr(line.find(' ') + 1, line.size());

                p[2] = std::stof(line);

                points.push_back(Vec3(p[0],p[1],p[2],COLOUR_MAGENTA));
                break;
            
            case 'f':
                line = line.substr(line.find(' ') + 1,line.size());

                t[0] = std::stoi(line.substr(0,line.find(' ')));
                line = line.substr(line.find(' ') + 1, line.size());

                t[1] = std::stoi(line.substr(0,line.find(' ')));
                line = line.substr(line.find(' ') + 1, line.size());

                if(line.find(' ') != std::string::npos)
                {
                    t[2] = std::stoi(line.substr(0,line.find(' ')));
                    line = line.substr(line.find(' ') + 1, line.size());

                    t[3] = std::stoi(line);
                    
                    // triangles 1,2,3
                    v[0] = points[t[0] - 1];
                    v[0].setColour(material.at(currentMaterial));
                    v[1] = points[t[1] - 1];
                    v[1].setColour(material.at(currentMaterial));
                    v[2] = points[t[2] - 1];
                    v[2].setColour(material.at(currentMaterial));

                    myTri = Triangle(v[0], v[1], v[2]);
                    mesh->add(myTri);

                    // triangles 1,3,4
                    v[0] = points[t[0] - 1];
                    v[0].setColour(material.at(currentMaterial));
                    v[1] = points[t[2] - 1];
                    v[1].setColour(material.at(currentMaterial));
                    v[2] = points[t[3] - 1];
                    v[2].setColour(material.at(currentMaterial));

                    myTri = Triangle(v[0], v[1], v[2]);
                    mesh->add(myTri);
                }
                else
                {
                    t[2] = std::stoi(line);

                    // set colour based on current material
                    v[0] = points[t[0] - 1];
                    v[0].setColour(material.at(currentMaterial));
                    v[1] = points[t[1] - 1];
                    v[1].setColour(material.at(currentMaterial));
                    v[2] = points[t[2] - 1];
                    v[2].setColour(material.at(currentMaterial));

                    myTri = Triangle(v[0], v[1], v[2]);
                    mesh->add(myTri);
                }
                
                break;
        }
    }

    std::cout << "Finished " << _meshfile << " with " << mesh->numTri() << " triangles." << std::endl;
    mesh->computeCentroid();
	return mesh;
}