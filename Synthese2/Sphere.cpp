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

bool Sphere::CanSeeLight(Vector3 point, Light light, vector<Sphere> spheres) {
    
    const Vector3 dirLampe = (Vector3::GetDirection(point, light.GetPosition()));
    const Ray ray = Ray((point + (dirLampe * .1)), dirLampe);
    const double distFromPointToLight = Vector3::GetDistance(point, light.GetPosition());
    
//    point = point + (.5 * Vector3::GetDirection(point, light.GetPosition()));
    
//    dirLampe.Print();

    Intersection intersection;

    for (const Sphere& sphere : spheres)
    {
        intersection = Sphere::IntersectRaySphere(ray, sphere);
        
        if (intersection.intersect)
        {
            double distFromPointToIntersect = Vector3::GetDistance(point, intersection.pointCoordonate);
            if (distFromPointToIntersect < distFromPointToLight)
            {
                return false;
            }
//            double distFromPointToIntersect = Vector3::GetDistance(point, intersection.pointCoordonate);
//            cout << "distFromPointToIntersect : " << distFromPointToIntersect << endl;
//            cout << "intersection.distance : " << intersection.distance << endl << endl;
//            cout << "distFromPointToLight : " << distFromPointToLight << endl << endl;
            
        }
    }

    return true;
}

void Sphere::SetCenter(Vector3 position) {
    m_center = position;
}


