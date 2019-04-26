//
//  Sphere.cpp
//  Synthese2
//
//  Created by Raphaël Daumas on 31/03/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#include "Sphere.hpp"

void Sphere::Intersect(const Rayon& rayon, const Sphere& sphere, Intersection& myRes)
{
    const double B = 2 * (Vector3::Dot(rayon.GetOrigin(), rayon.GetDirection()) - Vector3::Dot(sphere.GetCenter(), rayon.GetDirection()));
    const double C = Vector3::Dist2(sphere.GetCenter() - rayon.GetOrigin()) - (sphere.GetRayon() * sphere.GetRayon());
    const double delta = (B * B) - 4 * C;
    
    myRes.intersect = false;
    myRes.distance = 0;
    
    if (delta < 0)
    {
        myRes.intersect = false;
        return;
    }
    
    const double sqrtDelta = sqrt(delta);
    const double inter1 = (-B - sqrtDelta) / 2;
    const double inter2 = (-B + sqrtDelta) / 2;
    
    if (inter1 > 0)
    {
        myRes.intersect = true;
        myRes.distance = inter1;
    }else if (inter2 > 0)
    {
        myRes.intersect = true;
        myRes.distance = inter2;
    }
    
    myRes.point = rayon.GetOrigin() + rayon.GetDirection() * myRes.distance;
}
