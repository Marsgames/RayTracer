//
//  main.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 24/09/2018.
//  Copyright © 2018 Marsgames. All rights reserved.
//

#pragma once

#include <iostream>
#include "Vector3.hpp"


using namespace std;



struct Intersection{
    bool intersect;
    double distance;
    string nameInterObj;
    Vector3 point;
//    Intersection(bool intersectt, float interr){
//        intersect = intersectt;
//        inter = interr;
//    }
};

struct Color {
    float r, g, b;
};

struct Sphere{
    Vector3 origine;
    float rayon;
    Color couleur;
    string nom;
};

typedef vector<vector<Vector3>> V3Tab;

//void Intersect(const Vector3& point, const Vector3& direction, const Vector3& origineCercle, const float& rayon, Intersection& myRes);
void Intersect(const Vector3& point, const Vector3& direction, const Sphere& sphere, Intersection& myRes);
void ImageFromArray(const int& height, const int& width, const vector<vector<Color>>& pixelsArray);
void InitSpheres(vector<Sphere>& spheres);
bool CanSeeLight(const Vector3& point, const Vector3& lightPos, const vector<Sphere>& scene);
