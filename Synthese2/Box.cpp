//
//  Box.cpp
//  Synthese2
//
//  Created by Raphaël Daumas on 08/10/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#include "Box.hpp"
#include <math.h>
#include <Ray.hpp>
#include <Sphere.hpp>
#include <TreeBox.hpp>
#include <vector>
#include <Vector3.hpp>


Vector3 Box::GetPMin() const
{
    return m_pMin;
}

void Box::SetPMin(const Vector3& pMin)
{
    m_pMin = pMin;
}

Vector3 Box::GetPMax() const
{
    return m_pMax;
}

void Box::SetPMax(const Vector3& pMax)
{
    m_pMax = pMax;
}

//EBoxType Box::GetSource() const
//{
//    return m_source;
//}
//
//void Box::SetSource(EBoxType source)
//{
//    m_source = source;
//}
//
//Sphere Box::GetMySphere() const
//{
//    return m_mySphere;
//}
//
//void Box::SetMySphere(Sphere mySphere)
//{
//    m_mySphere = mySphere;
//}

bool Box::operator<(const Box& other) const
{
    // Pas bon car se base sur le centre de la sphère
    //    return (((bA.pMax.x - bA.pMin.x) + (bA.pMax.y - bA.pMin.y) + (bA.pMax.z - bA.pMin.z)) / 2) < (((bB.pMax.x - bB.pMin.x) + (bB.pMax.y - bB.pMin.y) + (bB.pMax.z - bB.pMin.z)) / 2);
    
    return m_pMin < other.GetPMin();
}

bool Box::IntersectBox(const Ray &ray, const Box &box)
{
//    Box box = tb.GetBox();
    
    // Division pour éviter une multiplication plus tard
    const double rinvx = 1 / ray.GetDirection().GetX();
    const double rinvy = 1 / ray.GetDirection().GetY();
    const double rinvz = 1 / ray.GetDirection().GetZ();
    
    // X slab Max box size
    const double tx1 = (box.GetPMin().GetX() - ray.GetOrigin().GetX()) * rinvx;
    const double tx2 = (box.GetPMax().GetX() - ray.GetOrigin().GetX()) * rinvx;
    
    const double tminX = tx1 < tx2 ? tx1 : tx2;
    const double tmaxX = tx1 > tx2 ? tx1 : tx2;
    
    // Y slab
    const double ty1 = (box.GetPMin().GetY() - ray.GetOrigin().GetY()) * rinvy;
    const double ty2 = (box.GetPMax().GetY() - ray.GetOrigin().GetY()) * rinvy;
    
    const double tminY = fmax(tminX, (fmin(ty1, ty2)));
    const double tmaxY = fmin(tmaxX, (fmax(ty1, ty2)));
//    const float tminY = tminX > (ty1 < ty2 ? ty1 : ty2) ? tminX : (ty1 < ty2 ? ty1 : ty2);
//    const float tmaxY = tmaxX < (ty1 > ty2 ? ty1 : ty2) ? tmaxX : (ty1 > ty2 ? ty1 : ty2);
    
    // Z slab
    const double tz1 = (box.GetPMin().GetZ() - ray.GetOrigin().GetZ()) * rinvz;
    const double tz2 = (box.GetPMax().GetZ() - ray.GetOrigin().GetZ()) * rinvz;
    
    const double tminZ = fmax(tminY, (fmin(tz1, tz2)));
    const double tmaxZ = fmin(tmaxY, (fmax(tz1, tz2)));
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
