//
//  Light.cpp
//  Synthese2
//
//  Created by Raphaël Daumas on 30/05/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#include "Light.hpp"
#include <Sphere.hpp>
#include <Vector3.hpp>
#include <vector>

Vector3 Light::GetPosition() const
{
    return m_position;
}

double Light::GetPower() const
{
    return m_power;
}

bool Light::CanSeeLight(const Vector3& point, const Light& light, const vector<Sphere>& spheres) {
    
    const Vector3 dirFromPointToLampe = (Vector3::GetDirection(point, light.GetPosition()));
    const Ray ray = Ray((point + (dirFromPointToLampe * 0)), dirFromPointToLampe);
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

Color Light::GetLightning(const Light& light, const Color& color, const double distance)
{
        const double puissance = light.GetPower() * (1 / distance);
    Color newColor = color;
    
    
    { // Check 0
    if (0 == newColor.GetR())
    {
        newColor.SetR(1);
    }
    if (0 == newColor.GetG())
    {
        newColor.SetG(1);
    }
    if (0 == newColor.GetB())
    {
        newColor.SetB(1);
    }
    newColor = newColor * puissance;
    }
    
    
//    if (EColor::Blue == color.GetColorName())
//    {
//        color.Print();
//        cout << "puissance : " << puissance << endl;
//        cout << "new";
//        newColor.Print();
//        cout << endl;
//    }

        //        cout << "color : (" << color.GetR() << ", " << color.GetG() << ",  " << color.GetB() << ")" << endl;
        //        cout << "light power : " << light.GetPower() << endl;
        //        cout << "puissance : " << puissance << endl;
        
        //        cout << "new color : (" << newColor.GetR() << ", " << newColor.GetG() << ",  " << newColor.GetB() << ")" << endl;
        
        //        cout << endl;
    if (newColor.GetR() <= 1 && newColor.GetG() <= 1 && newColor.GetB() <= 1)
        {
            cout << "Trop loin : noir" << endl;
            return Color{200, 200, 200} * 1;
        }
        
        return newColor;
}
