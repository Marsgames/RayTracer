//
//  Light.cpp
//  Synthese2
//
//  Created by Raphaël Daumas on 31/03/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#include <Light.hpp>
#include <Pixel.hpp>
#include <Sphere.hpp>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

bool Light::CanSeeLight(const Vector3& point, const Light& light, const vector<Sphere>* scene)
{
    Vector3 dirLampe = Vector3::GetDirection(point, light.GetPosition());
    //    const Vector3 dirCam = (ecran.GetPosition() - point).Normalize();
    const double distPointToLight = Vector3::GetDistance(point, light.GetPosition());
    
    for (const Sphere& sphere : *scene)
    {
        if (EMaterialType::LightType == sphere.GetMaterial().m_materialType)
        {
            continue;
        }
        
        Intersection result;
        
//        const Rayon rayon = Rayon((point + (dirLampe * .01)), dirLampe);
        const Rayon rayon = Rayon((point + (dirLampe * .5)), dirLampe);
        //        const Rayon rayon = Rayon((point + (dirLampe * .5)), dirLampe);
        //        const Rayon rayon = Rayon(point, dirLampe);
        Sphere::Intersect(rayon, sphere, result);
        
        if (result.intersect)
        {
            const double distPI = Vector3::GetDistance(point, result.point);
            
            // Si l'objet est devant la lumière return false.
            if (distPI <= distPointToLight)
            {
                return false;
            }
        }
    }
    
    // Si l'objet est derrière la lumière return true.
    return true;
}

void Light::SetLightning(const Vector3& point, const int index, const Light& light, vector<Pixel>& image)
{
    const double puissance = light.GetPuissance() * (1 / ((Vector3::GetDistance(light.GetPosition(), point))));
    
    Color col = image[index].GetColor() * puissance;
    
    image[index].SetColor(col);
}
