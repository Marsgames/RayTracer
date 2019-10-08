//
//  Sphere.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 29/05/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#pragma once

#include <Color.hpp>
#include <Material.hpp>
#include <Ray.hpp>
#include <string>
#include <Vector3.hpp>

using std::string;

class Sphere
{
    Vector3 m_center;
    int m_rayon;
    Material m_material ;
    string m_name = "";
    
public:
//    Sphere() = delete;
    Sphere() :
    m_material{MaterialList::NoirMat}
    {};
    
    Sphere(Vector3 position, int rayon, Material material) :
    m_center{position},
    m_rayon{rayon},
    m_material{material}
    {};
    
    Sphere(Vector3 position, int rayon) :
    m_center{position},
    m_rayon{rayon},
    m_material{Material(Color{1, 0, 0})}
    {};
    
    Sphere(Vector3 position, int rayon, Material material, string name) :
    m_center{position},
    m_rayon{rayon},
    m_material{material},
    m_name{name}
    {};
    
    Vector3 GetCenter() const;
    void SetCenter(Vector3 position);
    void SetCenter(int x, int y, int z);
    double GetPositionX() const;
    double GetPositionY() const;
    double GetPositionZ() const;
    
    bool operator<(const Sphere& other) const;
    
    int GetRayon() const;
    
    Material GetMaterial() const;
    int GetColorR() const;
    int GetColorG() const;
    int GetColorB() const;
    
    Vector3 GetNormal(Vector3 point) const;
    
    string GetName() const;
    
    static class Intersection IntersectRaySphere(class Ray ray, Sphere sphere);
};

struct Intersection {
    bool intersect = false;
    double distance = -1;
    Vector3 pointCoordonate = Vector3{0, 0, 0};
    int nbIntersect = 0;
    class Sphere touchedSphere = Sphere(Vector3(0), -1);
    
    Intersection() {};
    
    Intersection(bool theIntersect, double theDistance, Vector3 thePointCoordonate):
    intersect{theIntersect},
    distance{theDistance},
    pointCoordonate{thePointCoordonate}
    {};
    
    void PrintSphereState() const;
};
