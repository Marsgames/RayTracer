//
//  Sphere.cpp
//  Synthese2
//
//  Created by Raphaël Daumas on 29/05/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#include <iostream>
#include <math.h>
#include "Sphere.hpp"

using std::cout;
using std::endl;

void Intersection::PrintSphereState() const {
    switch(nbIntersect)
    {
        case 0:
            cout << "Pas d'intersection" << endl;
            break;
        case 1:
            cout << "1 intersection, on est dans la sphère" << endl;
            break;
        case 2:
            cout << "2 intersections, la sphère est devant le rayon" << endl;
            break;
            
        default:
            cout << "erreur" << endl;
    }
}

Vector3 Sphere::GetCenter() const {
    return  m_center;
}

double Sphere::GetPositionX() const {
    return  m_center.GetX();
}

double Sphere::GetPositionY() const {
    return  m_center.GetY();
}

double Sphere::GetPositionZ() const {
    return  m_center.GetZ();
}

int Sphere::GetRayon() const {
    return m_rayon;
}

Color Sphere::GetColor() const {
    return m_color;
}

int Sphere::GetColorR() const {
    return m_color.GetR();
}

int Sphere::GetColorG() const {
    return m_color.GetG();
}

int Sphere::GetColorB() const {
    return m_color.GetB();
}

// Repris de l'ancien code
Intersection Sphere::IntersectRaySphere(Ray ray, Sphere sphere) {
    Intersection myRes;// = Intersection(false, -1, Vector3(0, 0, 0));
    
    const double B = 2 * (Vector3::Dot(ray.GetOrigin(), ray.GetDirection()) - Vector3::Dot(sphere.GetCenter(), ray.GetDirection()));
    const double C = Vector3::Dist2(sphere.GetCenter() - ray.GetOrigin()) - (sphere.GetRayon() * sphere.GetRayon());
    const double delta = (B * B) - 4 * C;
    
    myRes.intersect = false;
    myRes.distance = 0;
    
    if (delta < 0)
    {
        myRes.intersect = false;
        return myRes;
    }
    
    const double sqrtDelta = sqrt(delta);
    const double inter1 = (-B - sqrtDelta) / 2;
    const double inter2 = (-B + sqrtDelta) / 2;
    
    if (inter1 > 0)
    {
        myRes.nbIntersect++;
    }
    if (inter2 > 0)
    {
        myRes.nbIntersect++;
    }
    
//    if (inter1 <= 0 && inter2 <= 0)
//    {
//        myRes.nbIntersect = 0;
//    }
//    else if (inter1 <= 0 && inter2 > 0)
//    {
//        myRes.nbIntersect = 1;
//    }
//    else if (inter1 > 0 && inter2 > 0)
    
    if (inter1 > 0)
    {
        myRes.intersect = true;
        myRes.distance = inter1;
    }else if (inter2 > 0)
    {
        myRes.intersect = true;
        myRes.distance = inter2;
    }
    
    myRes.pointCoordonate = ray.GetOrigin() + ray.GetDirection() * myRes.distance;
    
    return myRes;
}




void Sphere::SetCenter(Vector3 position) {
    m_center = position;
}

void Sphere::SetCenter(int x, int y, int z) {
    m_center = Vector3(x, y, z);
}

