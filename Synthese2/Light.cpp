//
//  Light.cpp
//  Synthese2
//
//  Created by Raphaël Daumas on 30/05/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#include <iostream>
#include "Light.hpp"
#include <random>
#include <Sphere.hpp>
#include <Toolbox.hpp>
#include <Vector3.hpp>
#include <vector>

using std::cout;
using std::endl;

Vector3 Light::GetPosition() const
{
    return m_position;
}

double Light::GetPower() const
{
    return m_power;
}

Material Light::GetMaterial() const {
    return m_material;
}

Color Light::GetLightning(const Light& light, const Intersection& intersection)
{
//    const int nbSurfacic = 5;
    
    Color newColor;
//    Vector3 position;
//
//#pragma omp parallel for
//    for (int i = 0; i < nbSurfacic; i++)
//    {
//        position = Toolbox::GetRandomPointOnSphere(Sphere(light.GetPosition(), 10));
        
        const double distance = Vector3::GetDistance(light.GetPosition(), intersection.pointCoordonate);
        const double puissance = light.GetPower() * (1 / (distance));
         const Color lightColor = light.GetMaterial().GetSelfIlluminColor();
        
        newColor += ((intersection.touchedSphere.GetMaterial().GetDiffuseColor() + lightColor) / 2) * puissance;
//    }
    
    
    
    
//    newColor = newColor / nbSurfacic;
    
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
        }

        newColor = newColor * puissance;








        if (newColor.GetR() <= 1 && newColor.GetG() <= 1 && newColor.GetB() <= 1)
            {
    //            cout << "Trop loin : noir" << endl;
    //            return Color{255, 200, 255} * 1;
                return Color{0, 0, 0} * 1;
            }

            return newColor;
}
