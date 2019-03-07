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


using namespace std;

struct Intersection{
    bool intersect;
    double distance;
    string nameInterObj;
    Vector3 point;
};

//enum SphereType
//{
//    difusType, miroirType, verreType, lumiereType
//};

class Sphere{
private:
    Vector3 m_origine;
    double m_rayon;
    Material m_material;
    string m_nom;
    
public:
    Sphere(){};
    
    Sphere(const Vector3& origine, const double& rayon){
        m_origine = origine;
        m_rayon = rayon;
    };
    
    Sphere(const Vector3& origine, const double rayon, const Material& material, const string nom){
        m_origine = origine;
        m_rayon = rayon;
        m_material = material;
        m_nom = nom;
    };
    
    Sphere(const Vector3& origine, const double rayon, const Material& material, const string nom, int isLight){
        m_origine = origine;
        m_rayon = rayon;
        m_material = material;
        m_nom = nom;
//        this->type = 0 == isLight ? lumiereType : miroirType;
    };
    
    Vector3 GetOrigine() const
    {
        return m_origine;
    }
    void SetOrigine(Vector3 origine)
    {
        m_origine = origine;
    }
    
    double GetRayon() const
    {
        return m_rayon;
    }
    
    Material GetMaterial() const
    {
        return m_material;
    }
    
    string GetName() const
    {
        return m_nom;
    }
};

void Intersect(const Rayon& rayon, const Sphere& sphere, Intersection& myRes)
{
    const double B = 2 * (Vector3::Dot(rayon.GetOrigine(), rayon.GetDirection()) - Vector3::Dot(sphere.GetOrigine(), rayon.GetDirection()));
    const double C = Dist2(sphere.GetOrigine() - rayon.GetOrigine()) - (sphere.GetRayon() * sphere.GetRayon());
    const double delta = (B * B) - 4 * C;
    
    myRes.intersect = false;
    myRes.distance = 0;
    
    if (delta < 0)
    {
        myRes.intersect = false;
        return;
    }
    
    const double sqrtDelta = sqrt(delta);
    const double inter1 = (-B - sqrtDelta) / 2;
    const double inter2 = (-B + sqrtDelta) / 2;
    
    if (inter1 > 0)
    {
        myRes.intersect = true;
        myRes.distance = inter1;
    }else if (inter2 > 0)
    {
        myRes.intersect = true;
        myRes.distance = inter2;
    }

    myRes.point = rayon.GetOrigine() + rayon.GetDirection() * myRes.distance;
}
