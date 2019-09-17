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

Color Light::GetLightning(const Light& light, const Color& color, const double distance)
{
//    const double puissance = light.GetPower() * (1 / (distance * distance));
    const double puissance = light.GetPower() * (1 / (distance));
    const Color lightColor = light.GetMaterial().GetSelfIlluminColor() * puissance;
    Color newColor = (color + lightColor) / 2;// light.GetMaterial().GetSelfIlluminColor();
    
//    cout << "GetLightning" << newColor.ToString() << endl;
//    cout << "light" << light.GetMaterial().GetSelfIlluminColor().ToString() << endl;

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


