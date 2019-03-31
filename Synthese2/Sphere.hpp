//
//  Sphere.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 22/10/2018.
//  Copyright © 2018 Marsgames. All rights reserved.
//

#pragma once

#include <iostream>
#include <math.h>
#include <Material.hpp>
#include <Rayon.hpp>
#include <Vector3.hpp>

using std::string;

struct Intersection{
    bool intersect;
    double distance;
    string nameInterObj;
    Vector3 point;
};

class Sphere{
private:
    Vector3 m_center;
    double m_rayon;
    Material m_material;
    string m_nom;
    
public:
    inline Sphere(){};
    
    inline Sphere(const Vector3& origin, const double& rayon) :
    m_center{origin},
    m_rayon{rayon}
    {};
    
    inline Sphere(const Vector3& origin, const double rayon, const Material& material, const string nom) :
    m_center{origin},
    m_rayon{rayon},
    m_material{material},
    m_nom{nom}
    {};
    
//    inline Sphere(const Vector3& origine, const double rayon, const Material& material, const string nom, int isLight){
//        m_center = origine;
//        m_rayon = rayon;
//        m_material = material;
//        m_nom = nom;
//    };
    
    inline Vector3 GetCenter() const
    {
        return m_center;
    }
    inline void SetCenter(Vector3 center)
    {
        m_center = center;
    }
    
    inline double GetRayon() const
    {
        return m_rayon;
    }
    
    inline Material GetMaterial() const
    {
        return m_material;
    }
    
    inline string GetName() const
    {
        return m_nom;
    }
    
    static void Intersect(const Rayon& rayon, const Sphere& sphere, Intersection& myRes);
};


