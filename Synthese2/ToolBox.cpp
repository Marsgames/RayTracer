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
//    const unsigned seed = K_SEED;
//    std::default_random_engine generator(static_cast<unsigned>(t);
    
//    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(min, max);
        
//    cout << endl << endl;
//    for (int i = 0; i < 10; i++)
//    {
//        cout << "random number : " << distribution(generator) << endl;
//    }
//    cout << endl;
    
    return distribution(K_GENERATOR);
}

/// Return a random direction from a Point(x, y, z)
/// @param normal The center of the hemisphere will be perpendicular with this direction
Vector3 Toolbox::GetRandomDirectionOnHemisphere(const Vector3& normal) {
    const double random1 = GenerateRandomNumber();
    double random2 = GenerateRandomNumber();

    const float x = cos(2 * M_PI * random1) * (sqrt(1 - (random2 * random2)));
    const float y = sin(2 * M_PI * random1) * (sqrt(1 - (random2 * random2)));

    if (normal.GetZ() < 0)
    {
        random2 *= -1;
    }

    const Vector3 axeX = Vector3::CrossProduct(Vector3(GenerateRandomNumber(-1, 1), GenerateRandomNumber(-1, 1), GenerateRandomNumber(-1, 1)), normal);
    const Vector3 axeY = Vector3::CrossProduct(axeX, normal);
    
    return (axeX * x) + (axeY * y) + (normal * random2);
}

Vector3 Toolbox::GetRandomDirectionInAngle(const Vector3& normal, const float angleMax)
{
    float theAngle = ((angleMax * M_PI) / 180) / 2;

    const double random1 = GenerateRandomNumber();
    double random2 = GenerateRandomNumber();

    const float racine = 1 - random2 * (1 - cos(theAngle));

    const float x = cos(2 * M_PI * random1) * (sqrt(1 - (racine * racine)));
    const float y = sin(2 * M_PI * random1) * (sqrt(1 - (racine * racine)));
    const float z = 1 - random2 * (1 - cos(theAngle));

    const Vector3 axeX = Vector3::CrossProduct(Vector3(GenerateRandomNumber(-1, 1), GenerateRandomNumber(-1, 1), GenerateRandomNumber(-1, 1)), normal);
    const Vector3 axeY = Vector3::CrossProduct(axeX, normal);
    
    return (axeX * x) + (axeY * y) + (normal * z);
}

Vector3 Toolbox::GetRandomPointOnSphere(const Sphere& sphere)
{
    const Vector3 position = sphere.GetCenter();
    const int rayon = sphere.GetRayon();
    
    const double random1 = GenerateRandomNumber();
    const double random2 = GenerateRandomNumber();
    
    const double x = position.GetX() + 2 * rayon * cos(2 * M_PI * random1) * random2 * (1 - random2);
    const double y = position.GetY() + 2 * rayon * sin(2 * M_PI * random1) * random2 * (1 - random2);
    const double z = position.GetZ() + rayon * (1 - 2 * random2);
    
    return Vector3(x, y, z);
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
    
//    #pragma omp parallel for
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

default_random_engine Toolbox::K_GENERATOR = default_random_engine(K_SEED);

