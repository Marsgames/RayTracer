//
//  Box.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 19/11/2018.
//  Copyright © 2018 Marsgames. All rights reserved.
//

#pragma once

#include "Vector3.hpp"
#include "Sphere.hpp"
#include "Rayon.hpp"
#include <math.h>
#include <iostream>

using namespace std;

enum BoxType{
    sphereType, boundingBoxType, superBBType
};

class Box
{
public:
    Vector3 pMin;
    Vector3 pMax;
    BoxType source;
    Sphere mySphere;
//    vector<Box> boxesList;
    
    Box(){};
    Box(const Sphere& sphere){
        pMin = Vector3(sphere.origine.x - sphere.rayon, sphere.origine.y - sphere.rayon, sphere.origine.z - sphere.rayon);
        pMax = Vector3(sphere.origine.x + sphere.rayon, sphere.origine.y + sphere.rayon, sphere.origine.z + sphere.rayon);
        source = sphereType;
        mySphere = sphere;
    };
    
    Box(const Box& b1, const Box& b2)
    {
        pMin = b1.pMin < b2.pMin ? b1.pMin : b2.pMin;
        pMax = b1.pMax > b2.pMax ? b1.pMax : b2.pMax;
        source = boundingBoxType;
    };
    
//    Box(const Box& b1, const Box& b2, const vector<Box>& boxes)
//    {
//        pMin = b1.pMin < b2.pMin ? b1.pMin : b2.pMin;
//        pMax = b1.pMax > b2.pMax ? b1.pMax : b2.pMax;
//        source = boundingBoxType;
//        boxesList = boxes;
//    };
    
    void Print() const
    {
        cout << "Box : " << endl;
        cout << "\tCenter : " << ((pMax.x - pMin.x) + (pMax.y - pMin.y) + (pMax.z - pMin.z)) / 2 << endl;
        cout << "\tpMin : ";
        pMin.Print();
        cout << endl;
        cout << "\tpMax : ";
        pMax.Print();
        cout << endl;
    }
    
    // (pMax - pMin) / 2 --> centre
    
};

bool operator<(const Box& bA, const Box& bB)
{
    // Pas bon car se base sur le centre de la sphère
//    return (((bA.pMax.x - bA.pMin.x) + (bA.pMax.y - bA.pMin.y) + (bA.pMax.z - bA.pMin.z)) / 2) < (((bB.pMax.x - bB.pMin.x) + (bB.pMax.y - bB.pMin.y) + (bB.pMax.z - bB.pMin.z)) / 2);
    
    return bA.pMin < bB.pMin;
}

bool IntersectBox(const Rayon& ray, const Box& box)
{
    // Division pour éviter une multiplication plus tard
    const float rinvx = 1 / ray.direction.x;
    const float rinvy = 1 / ray.direction.y;
    const float rinvz = 1 / ray.direction.z;
    
    // X slab Max box size
    const float tx1 = (box.pMin.x - ray.origine.x) * rinvx;
    const float tx2 = (box.pMax.x - ray.origine.x) * rinvx;
    
    const float tminX = tx1 < tx2 ? tx1 : tx2;
    const float tmaxX = tx1 > tx2 ? tx1 : tx2;
    
    // Y slab
    const float ty1 = (box.pMin.y - ray.origine.y) * rinvy;
    const float ty2 = (box.pMax.y - ray.origine.y) * rinvy;
    
    const float tminY = max(tminX, (min(ty1, ty2)));
    const float tmaxY = min(tmaxX, (max(ty1, ty2)));
//    const float tminY = tminX > (ty1 < ty2 ? ty1 : ty2) ? tminX : (ty1 < ty2 ? ty1 : ty2);
//    const float tmaxY = tmaxX < (ty1 > ty2 ? ty1 : ty2) ? tmaxX : (ty1 > ty2 ? ty1 : ty2);
    
    // Z slab
    const float tz1 = (box.pMin.z - ray.origine.z) * rinvz;
    const float tz2 = (box.pMax.z - ray.origine.z) * rinvz;
    
    const float tminZ = max(tminY, (min(tz1, tz2)));
    const float tmaxZ = min(tmaxY, (max(tz1, tz2)));
//    const float tminZ = tminY > (tz1 < tz2 ? tz1 : tz2) ? tminY : (tz1 < tz2 ? tz1 : tz2);
//    const float tmaxZ = tmaxY < (tz1 > tz2 ? tz1 : tz2) ? tmaxY : (tz1 > tz2 ? tz1 : tz2);
    
    if (tmaxZ >= tminZ)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void CreateSpheresBoxes(vector<Box>& boxesScene, const vector<Sphere>& scene)
{
//    int i = 1;
    for (const Sphere& sphere : scene)
    {
        if (sphere.nom == "lampe")
        {
            break;
        }
        
        Box b = Box(sphere);
        boxesScene.push_back(b);
        
//        cout << "Box" << i << " crée. bMin = ";
//        Print(b.pMin);
//        cout << " - bMax = ";
//        Print(b.pMax);
//        cout << endl;
    }
}
