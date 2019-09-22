//
//  Light.cpp
//  Synthese2
//
//  Created by Raphaël Daumas on 30/05/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#include "Light.hpp"
#include <random>
#include <Sphere.hpp>
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

//Color Light::GetLightning(const Light& light, const Color& color, const double distance, Vector3 normal)
//{
//
//
//
//
//
//    const double puissance = light.GetPower() * (1 / (distance));
//    const Color lightColor = light.GetMaterial().GetSelfIlluminColor();// * puissance;
//    Color newColor = (color + lightColor) / 2;
//
//
//
//
////    const double intensity = light.GetPower() * (1 / (distance)) * Vector3::Dist2(normal);
//////     Color newColor = color * intensity;
////    const Color lightColor = light.GetMaterial().GetSelfIlluminColor() * intensity;
////    Color newColor = (color + lightColor) / 2;
////
////    cout << "intensity : " << intensity << endl;
//
//
//
//
//    { // Check 0
//    if (0 == newColor.GetR())
//    {
//        newColor.SetR(1);
//    }
//    if (0 == newColor.GetG())
//    {
//        newColor.SetG(1);
//    }
//    if (0 == newColor.GetB())
//    {
//        newColor.SetB(1);
//    }
//    }
//
//    newColor = newColor * puissance;
////    newColor = newColor * intensity;
//
//
//
//
//
//
//
//
//    if (newColor.GetR() <= 1 && newColor.GetG() <= 1 && newColor.GetB() <= 1)
//        {
////            cout << "Trop loin : noir" << endl;
////            return Color{255, 200, 255} * 1;
//            return Color{0, 0, 0} * 1;
//        }
//
//        return newColor;
//}

//Color Light::GetLightning(const Light& light, const Intersection& intersection)
//{
//    const Vector3 normal = intersection.touchedSphere.GetNormal(intersection.pointCoordonate);
//    const Vector3 lightVector = Vector3::GetDirection(light.GetPosition(), intersection.pointCoordonate);
//    const double angle = Vector3::Dot(normal, lightVector);
//
//    if (angle <= 0)
//    {
//        return Color(0, 0, 0);
//    }
//    else
//    {
//        return intersection.touchedSphere.GetMaterial().GetDiffuseColor() * light.GetMaterial().GetSelfIlluminColor() * angle;
//    }
//
//}

Color Light::GetLightning(const Light& light, const Intersection& intersection)
{
    const double distance = Vector3::GetDistance(light.GetPosition(), intersection.pointCoordonate);
   const double puissance = light.GetPower() * (1 / (distance));
    const Color lightColor = light.GetMaterial().GetSelfIlluminColor() * puissance;
    Color newColor = (intersection.touchedSphere.GetMaterial().GetDiffuseColor() + lightColor) / 2;
    
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
    //    newColor = newColor * intensity;








        if (newColor.GetR() <= 1 && newColor.GetG() <= 1 && newColor.GetB() <= 1)
            {
    //            cout << "Trop loin : noir" << endl;
    //            return Color{255, 200, 255} * 1;
                return Color{0, 0, 0} * 1;
            }

            return newColor;
}






//Color Light::GetLightning(const Light& light, const Intersection& intersection, const Sphere& actualSphere)
//{
//    const Vector3 lightDirection = Vector3::GetDirection(light.GetPosition(), intersection.pointCoordonate);
//
//    const double angle = Vector3::Dot(actualSphere.GetNormal(intersection.pointCoordonate), lightDirection);
//
//    if (angle <= 0)
//    {
//        return Color(0, 0, 0);
//    }
//
//    return  actualSphere.GetMaterial().GetDiffuseColor() * light.GetMaterial().GetSelfIlluminColor() * angle;
//
//    /*
//     Calculer l'angle de frappe ANGLE du rayon lumineux avec la surface en utilisant la normale au point d'intersection (2.2)
//     Si ANGLE <= 0 Alors
//     COULEURFINALE = Couleur de fond
//     Sinon
//     COULEURFINALE = mDiffuseColor(mat) * couleur lumiére * ANGLE; (2.3)
//     fsi
//
//     Retourne COULEURFINALE
//     Fin Methode GetLightAt.
//     */
//
//}


