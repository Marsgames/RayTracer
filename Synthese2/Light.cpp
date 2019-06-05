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
    const Ray ray = Ray((point + (dirFromPointToLampe * 0.5)), dirFromPointToLampe);
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

//Color Light::GetLightning(const Light& light, const Color& color, const double distance)
//{
//        const double puissance = light.GetPower() * (1 / distance);
//    Color newColor = color;
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
//    newColor = newColor * puissance;
//    }
//
//
////    if (EColor::Blue == color.GetColorName())
////    {
////        color.Print();
////        cout << "puissance : " << puissance << endl;
////        cout << "new";
////        newColor.Print();
////        cout << endl;
////    }
//
//        //        cout << "color : (" << color.GetR() << ", " << color.GetG() << ",  " << color.GetB() << ")" << endl;
//        //        cout << "light power : " << light.GetPower() << endl;
//        //        cout << "puissance : " << puissance << endl;
//
//        //        cout << "new color : (" << newColor.GetR() << ", " << newColor.GetG() << ",  " << newColor.GetB() << ")" << endl;
//
//        //        cout << endl;
//    if (newColor.GetR() <= 1 && newColor.GetG() <= 1 && newColor.GetB() <= 1)
//        {
//            cout << "Trop loin : noir" << endl;
//            return Color{200, 200, 200} * 1;
//        }
//
//        return newColor;
//}

Color Light::GetLightning(const Light& light, const Material material, const double distance)
{
    
    /*
     Methode GetLightAt(Vector3D normal, Vector3D intersection, Material matl) retourne Couleur
     Calculer le vecteur LIGHTVECTOR correspondant au vecteur partant de la source de lumiére jusqu'au point d'intersection avec l'objet (2.1)
     Normaliser LIGHTVECTOR
     
     Calculer l'angle de frappe ANGLE du rayon lumineux avec la surface en utilisant la normale au point d'intersection (2.2)
     Si ANGLE <= 0 Alors
     COULEURFINALE = Couleur de fond
     Sinon
     COULEURFINALE = mDiffuseColor(mat) * couleur lumiére * ANGLE; (2.3)
     fsi
     
     Retourne COULEURFINALE
     Fin Methode GetLightAt.
     */
    Vector3 lightDirection = Vector3::GetDirection(light.GetPower(), <#const Vector3 &to#>)
    
}
