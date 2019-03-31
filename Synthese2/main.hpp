//
//  main.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 24/09/2018.
//  Copyright © 2018 Marsgames. All rights reserved.
//

#pragma once

#include <iostream>
#include <Rayon.hpp>
#include <Vector3.hpp>
#include <Light.hpp>
#include <Sphere.hpp>
#include <Box.hpp>
#include <Pixel.hpp>

using std::vector;
using std::cout;

using Spheres = vector<Sphere>;
typedef vector<Box> Boxes;
typedef vector<Pixel> Image;

//void ImageFromArray(const Image& pixelsArray, const string source, const string nomImage, const Camera& ecran);
void InitSpheres(Spheres& spheres, const Light& lumiere);
int RunTests();
void CreateSpheresBoxes(Boxes& boxesScene, const Spheres& scene);
void MoveLight (Light& lumiere, const Vector3 direction, Sphere& lightSphere);
//void MoveLight (Light& lumiere, const Vector3 direction, Scene spheres);
//void ClearImage (Image& imageArray, const Camera& ecran);
//void GenerateImages(const int firstImage, const int lastImage, Scene spheres, Camera& ecran, const Vector3& MoveLightDirection = Vector3(0, 0, 0));
//void LaunchThreads(const int nbImages, const Scene& spheres, const Camera& ecran, const Vector3& directionLight);


void Print(const Vector3& v)
{
    cout << "vector : (" << v.GetX() << ", " << v.GetY() << ", " << v.GetZ() << ")" << std::endl;
}
void Print(const Intersection& res)
{
    cout << "--------------------" << endl;
    cout << "intersect : " << res.intersect << endl;
    cout << "distance : " << res.distance << endl;
    cout << "x : " << res.point.GetX() << endl;
    cout << "y : " << res.point.GetY() << endl;
    cout << "z : " << res.point.GetZ() << endl;
}
void Print(const Box& box)
{
    cout << "Box : " << endl;
    cout << "\tCenter : " << ((box.GetPMax().GetX() - box.GetPMin().GetX()) + (box.GetPMax().GetY() - box.GetPMin().GetY()) + (box.GetPMax().GetZ() - box.GetPMin().GetZ())) / 2 << endl;
    cout << "\tpMin : ";
    box.GetPMin().Print();
    cout << endl;
    cout << "\tpMax : ";
    box.GetPMax().Print();
    cout << endl;
}
