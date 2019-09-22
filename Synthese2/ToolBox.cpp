//
//  Toolbox.cpp
//  Synthese2
//
//  Created by Raphaël Daumas on 17/09/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#include <iostream>
#include <Light.hpp>
#include <math.h>
#include <random>
#include <Ray.hpp>
#include <Sphere.hpp>
#include <Toolbox.hpp>
#include <vector>
#include <Vector3.hpp>

using std::cout;
using std::endl;

/// Generate a random uniform double between min and max
/// @param min min value of the random generated number
/// @param max max value of the random generated number
double Toolbox::GenerateRandomNumber(const double min, const double max) {
    const unsigned seed = 0;
    std::default_random_engine generator(seed);
    std::uniform_real_distribution<double> distribution(min, max);
    
//    cout << endl << endl;
//    for (int i = 0; i < 10; i++)
//    {
//        cout << "random number : " << distribution(generator) << endl;
//    }
//    cout << endl;
    
    return distribution(generator);
}

/// Return a random direction from a Point(x, y, z)
/// @param origin Point from where random direction will be generated
Vector3 Toolbox::GetRandomDirectionOnHemisphere(const Vector3& origin, const Vector3& normal) {
    const double random1 = GenerateRandomNumber();
    double random2 = GenerateRandomNumber();
    
    const double x = cos(2 * M_PI * random1) * (sqrt((1 - random2 * random2)));
    const double y = sin(2 * M_PI * random1) * (sqrt((1 - random2 * random2)));
    
    if (normal.GetZ() < 0)
    {
        random2 *= -1;
    }
    
    Vector3 theNormal = normal.Normalize();
    
//    return Vector3(x, y, random2);// * normal;
    return Vector3(x + theNormal.GetX(), y + theNormal.GetY(), random2 + theNormal.GetZ()).Normalize();

}

/// Return true if a point is lighted by the light
/// @param point Point we want to test
/// @param light Light that have to enlight the point
/// @param spheres Spheres prensents in the scene
bool Toolbox::CanSeeLight(const Vector3& point, const Light& light, const vector<Sphere>& spheres) {
    
    const Vector3 dirFromPointToLampe = (Vector3::GetDirection(point, light.GetPosition()));
    const Ray ray = Ray((point + (dirFromPointToLampe * 1.5)), dirFromPointToLampe);
    const double distFromPointToLight = Vector3::GetDistance(point, light.GetPosition());
    
    //    point = point + (.5 * Vector3::GetDirection(point, light.GetPosition()));
    
    //    dirLampe.Print();
    
    Intersection intersection;
    
    for (const Sphere& sphere : spheres)
    {
//        cout << "sphere " << sphere.GetName() << endl;
//        cout << "point : " << point.ToString() << endl;
//        cout << "rayOrigin : " << ray.GetOrigin().ToString() << endl;
//        cout << "rayDirection : " << ray.GetDirection().ToString() << endl;
        intersection = Sphere::IntersectRaySphere(ray, sphere);
//        cout << "intersection : " << intersection.intersect << endl << endl;
        
        
        if (intersection.intersect)
        {
            double distFromPointToIntersect = Vector3::GetDistance(point, intersection.pointCoordonate);
            
//            cout << "distFromPointToIntersect : " << distFromPointToIntersect << endl;
//            cout << "distFromPointToLight : " << distFromPointToLight << endl << endl;
            
            if (distFromPointToIntersect < distFromPointToLight)
            {
//                cout << "y'a intersection" << endl;
                return false;
            }
            
        }
    }
//    cout << endl << endl;
    
    return true;
}

