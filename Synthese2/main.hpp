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
#include "Sphere.hpp"
#include "Box.hpp"

using namespace std;

void DebugIntersect(const Intersection res)
{
    cout << "--------------------" << endl;
    cout << "intersect : " << res.intersect << endl;
    cout << "distance : " << res.distance << endl;
    cout << "x : " << res.point.x << endl;
    cout << "y : " << res.point.y << endl;
    cout << "z : " << res.point.z << endl;

}

//typedef vector<vector<Vector3>> V3Tab;
typedef vector<Sphere> Scene;
typedef vector<Box> Boxes;
typedef vector<Color> Image;

void Intersect(const Rayon& rayon, const Sphere& sphere, Intersection& myRes);
void ImageFromArray(const int& height, const int& width, const Image& pixelsArray);
void InitSpheres(Scene& spheres);
bool CanSeeLight(const Vector3& point, const Light& lightPos, const Scene& scene);
void SetLightning(const Vector3& point, const Light& light,  Image& image);
int RunTests();
double GetDistance(const Vector3& pointA, const Vector3& pointB);
void CreateSpheresBoxes(Boxes& boxesScene, const Scene& scene);
