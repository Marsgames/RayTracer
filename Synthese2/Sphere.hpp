//
//  Sphere.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 22/10/2018.
//  Copyright © 2018 Marsgames. All rights reserved.
//

#pragma once

#include "main.hpp"
#include "Color.hpp"
#include <iostream>
#include "Rayon.hpp"
#include <math.h>
#include "Vector3.hpp"

using namespace std;

struct Intersection{
    bool intersect;
    double distance;
    string nameInterObj;
    Vector3 point;
};

enum SphereType
{
    difusType, miroirType, verreType, lumiereType
};

class Sphere{
public:
    Vector3 origine;
    double rayon;
    Color couleur;
    string nom;
//    int debugSphere;
    SphereType type;
    
    Sphere(){};
    Sphere(const Vector3& origine, const double& rayon){
        this->origine = origine;
        this->rayon = rayon;
    };
    Sphere(const Vector3& origine, const double& rayon, const Color& couleur, const string& nom){
        this->origine = origine;
        this->rayon = rayon;
        this->couleur = couleur;
        this->nom = nom;
    };
    
    Sphere(const Vector3& origine, const double& rayon, const Color& couleur, const string& nom, int isLight){
        this->origine = origine;
        this->rayon = rayon;
        this->couleur = couleur;
        this->nom = nom;
        this->type = 0 == isLight ? lumiereType : miroirType;
    };
};

void Intersect(const Rayon& rayon, const Sphere& sphere, Intersection& myRes)
{
    const double B = 2 * (Dot(rayon.origine, rayon.direction) - Dot(sphere.origine, rayon.direction));
    const double C = Dist2(sphere.origine - rayon.origine) - (sphere.rayon * sphere.rayon);
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
    
    myRes.point = rayon.origine + rayon.direction * myRes.distance;
}
