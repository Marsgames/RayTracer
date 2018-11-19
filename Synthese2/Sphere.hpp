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

using namespace std;

class Sphere{
public:
    Vector3 origine;
    double rayon;
    Color couleur;
    string nom;
    int debugSphere;
    
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
        this->debugSphere = isLight;
    };
    
    bool IsLight() const
    {
        return 0 == this->debugSphere;
    };
    
    bool IsMirror() const
    {
        return 1 == this->debugSphere;
    };
};
