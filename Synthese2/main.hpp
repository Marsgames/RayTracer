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
    cout << "x : " << res.point.GetX() << endl;
    cout << "y : " << res.point.GetY() << endl;
    cout << "z : " << res.point.GetZ() << endl;
}

//typedef vector<vector<Vector3>> V3Tab;
typedef vector<Sphere> Scene;
typedef vector<Box> Boxes;
typedef vector<Color> Image;

void Intersect(const Rayon& rayon, const Sphere& sphere, Intersection& myRes);
void ImageFromArray(const Image& pixelsArray, const string source, const string nomImage);
void InitSpheres(Scene& spheres);
bool CanSeeLight(const Vector3& point, const Light& lightPos, const Scene& scene);
void SetLightning(const Vector3& point, const int index, const Light& light,  Image& image);
int RunTests();
double GetDistance(const Vector3& pointA, const Vector3& pointB);
void CreateSpheresBoxes(Boxes& boxesScene, const Scene& scene);
void MoveLight (Light& lumiere, const Vector3 direction);
void MoveLight (Light& lumiere, const Vector3 direction, Scene spheres);
void ClearImage (Image& imageArray, const Camera& ecran);
void GenerateImages(const int firstImage, const int lastImage, Scene spheres, const Camera& ecran, const Vector3& MoveLightDirection);
void LaunchThreads(const int nbImages, Scene& spheres, const Camera& ecran, const float facteurLumiere);
