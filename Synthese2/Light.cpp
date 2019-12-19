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

Color Light::GetLighting(const Light& light, const Intersection& intersection, const float distanceToAdd)
{
    Color newColor = Color(0);
        
        const double distance = Vector3::GetDistance(light.GetPosition(), intersection.pointCoordonate) + distanceToAdd;
        const double puissance = light.GetPower() * (1 / (distance * distance));
    
    const Color lightColor = light.GetMaterial().GetSelfIlluminColor() * puissance;
    
    const Vector3 normale = intersection.touchedSphere.GetNormal(intersection.pointCoordonate);
    const double angle = acos((Vector3::Dot(normale, Vector3::GetDirection(light.GetPosition(), intersection.pointCoordonate))));
    
    
    
    newColor = (intersection.touchedSphere.GetMaterial().GetDiffuseColor() * lightColor) * (angle / M_PI);
    


            return newColor;
}
