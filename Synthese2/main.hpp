//
//  main.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 24/09/2018.
//  Copyright © 2018 Marsgames. All rights reserved.
//

#pragma once

#include <iostream>
#include "Rayon.hpp"
#include "Vector3.hpp"
#include "Light.hpp"


using namespace std;



struct Intersection{
    bool intersect;
    double distance;
    string nameInterObj;
    Vector3 point;
};

struct Color {
    double r, g, b;
};

struct Sphere{
    Vector3 origine;
    float rayon;
    Color couleur;
    string nom;
};

//typedef vector<vector<Vector3>> V3Tab;
typedef vector<Sphere> Scene;
typedef vector<vector<Color>> Image;

void Intersect(const Rayon& rayon, const Sphere& sphere, Intersection& myRes);
void ImageFromArray(const int& height, const int& width, const vector<vector<Color>>& pixelsArray);
void InitSpheres(vector<Sphere>& spheres);
bool CanSeeLight(const Vector3& point, const Light& lightPos, const vector<Sphere>& scene);
void SetLightning(const Vector3& point, const Light& light,  vector<vector<Color>>& image);
int RunTests();

