//
//  Box.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 19/11/2018.
//  Copyright © 2018 Marsgames. All rights reserved.
//

#pragma once

#include <Vector3.hpp>
#include <Sphere.hpp>
#include <Rayon.hpp>
#include <math.h>
#include <iostream>

using namespace std;

enum BoxType{
    sphereType, boundingBoxType, superBBType
};

class Box
{
protected:
    Vector3 m_pMin, m_pMax;
    BoxType m_source;
    Sphere m_mySphere;
    
public:
    Box(){};
    Box(const Sphere& sphere){
        m_pMin = Vector3(sphere.GetCenter().GetX() - sphere.GetRayon(), sphere.GetCenter().GetY() - sphere.GetRayon(), sphere.GetCenter().GetZ() - sphere.GetRayon());
        m_pMax = Vector3(sphere.GetCenter().GetX() + sphere.GetRayon(), sphere.GetCenter().GetY() + sphere.GetRayon(), sphere.GetCenter().GetZ() + sphere.GetRayon());
        m_source = sphereType;
        m_mySphere = sphere;
    };
    
    Box(const Box& b1, const Box& b2)
    {
        m_pMin = b1.m_pMin < b2.m_pMin ? b1.m_pMin : b2.m_pMin;
        m_pMax = b1.m_pMax > b2.m_pMax ? b1.m_pMax : b2.m_pMax;
        m_source = boundingBoxType;
    };
    
    // (pMax - pMin) / 2 --> centre
    Vector3 GetPMin() const
    {
        return m_pMin;
    }
    void SetPMin(Vector3 pMin)
    {
        m_pMin = pMin;
    }
    
    Vector3 GetPMax() const
    {
        return m_pMax;
    }
    void SetPMax(Vector3 pMax)
    {
        m_pMax = pMax;
    }
    
    BoxType GetSource() const
    {
        return m_source;
    }
    void SetSource(BoxType source)
    {
        m_source = source;
    }
    
    Sphere GetMySphere() const
    {
        return m_mySphere;
    }
    void SetMySphere(Sphere mySphere)
    {
        m_mySphere = mySphere;
    }
    
    friend bool operator<(Box bA, const Box& bB)
    {
        // Pas bon car se base sur le centre de la sphère
        //    return (((bA.pMax.x - bA.pMin.x) + (bA.pMax.y - bA.pMin.y) + (bA.pMax.z - bA.pMin.z)) / 2) < (((bB.pMax.x - bB.pMin.x) + (bB.pMax.y - bB.pMin.y) + (bB.pMax.z - bB.pMin.z)) / 2);
        
        return bA.GetPMin() < bB.GetPMin();
    }
};



bool IntersectBox(const Rayon& ray, const Box& box)
{
    // Division pour éviter une multiplication plus tard
    const float rinvx = 1 / ray.GetDirection().GetX();
    const float rinvy = 1 / ray.GetDirection().GetY();
    const float rinvz = 1 / ray.GetDirection().GetZ();
    
    // X slab Max box size
    const float tx1 = (box.GetPMin().GetX() - ray.GetOrigin().GetX()) * rinvx;
    const float tx2 = (box.GetPMax().GetX() - ray.GetOrigin().GetX()) * rinvx;
    
    const float tminX = tx1 < tx2 ? tx1 : tx2;
    const float tmaxX = tx1 > tx2 ? tx1 : tx2;
    
    // Y slab
    const float ty1 = (box.GetPMin().GetY() - ray.GetOrigin().GetY()) * rinvy;
    const float ty2 = (box.GetPMax().GetY() - ray.GetOrigin().GetY()) * rinvy;
    
    const float tminY = max(tminX, (min(ty1, ty2)));
    const float tmaxY = min(tmaxX, (max(ty1, ty2)));
//    const float tminY = tminX > (ty1 < ty2 ? ty1 : ty2) ? tminX : (ty1 < ty2 ? ty1 : ty2);
//    const float tmaxY = tmaxX < (ty1 > ty2 ? ty1 : ty2) ? tmaxX : (ty1 > ty2 ? ty1 : ty2);
    
    // Z slab
    const float tz1 = (box.GetPMin().GetZ() - ray.GetOrigin().GetZ()) * rinvz;
    const float tz2 = (box.GetPMax().GetZ() - ray.GetOrigin().GetZ()) * rinvz;
    
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
        if (sphere.GetName() == "lampe")
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
