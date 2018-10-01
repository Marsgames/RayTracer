//
//  main.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 24/09/2018.
//  Copyright © 2018 Marsgames. All rights reserved.
//

#pragma once

#include <iostream>

using namespace std;

struct Vector3 {
    //const Vector3 One = Vector3(1, 1, 1);
    float x, y, z;
};

struct Intersection{
    bool intersect;
    double inter;
//    Intersection(bool intersectt, float interr){
//        intersect = intersectt;
//        inter = interr;
//    }
};

struct Color {
    int r, g, b;
};

struct Sphere{
    Vector3 position;
    float rayon;
    Color couleur;
    string nom;
    float alpha = 1;
};

double Dot(Vector3 pA, Vector3 pB)
{
    return pA.x * pB.x + pA.y * pB.y + pA.z * pB.z;
}

double Dist2(Vector3 pA)
{
    return Dot(pA, pA);
}

Vector3 Minus(Vector3 A, Vector3 B)
{
    return Vector3{A.x - B.x, A.y - B.y, A.z - B.z};
}

typedef vector<vector<Vector3>> V3Tab;

void Intersect(const Vector3& point, const Vector3& direction, const Vector3& origineCercle, const float rayon, Intersection& myRes);
void ImageFromArray(int height, int width, vector<vector<Color>> pixelsArray);
