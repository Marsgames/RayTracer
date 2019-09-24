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
    Color newColor;
        
        const double distance = Vector3::GetDistance(light.GetPosition(), intersection.pointCoordonate);
        const double puissance = light.GetPower() * (1 / (distance));
    
//    cout << "puissance : " << puissance << endl;
    
//         const Color lightColor = light.GetMaterial().GetSelfIlluminColor();
        
    newColor = intersection.touchedSphere.GetMaterial().GetDiffuseColor() * puissance;// * lightColor;// ((intersection.touchedSphere.GetMaterial().GetDiffuseColor() + lightColor) / 2) * puissance;
    

//        newColor = newColor * puissance;

            return newColor;
}
