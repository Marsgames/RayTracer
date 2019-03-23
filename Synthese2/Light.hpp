//
//  Light.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 08/10/2018.
//  Copyright © 2018 Marsgames. All rights reserved.
//

#pragma once

#include <Color.hpp>
#include <Sphere.hpp>
#include <Vector3.hpp>

using std::vector;

class Light
{
private:
    Vector3 m_position;
    int m_puissance;
    
public:
    Light() {}
    
    Light(Vector3 position)
    {
        m_position = position;
    }
    
    Light(Vector3 position, int puissance)
    {
        m_position = position;
        m_puissance = puissance;
    }
    
    Vector3 GetPosition() const
    {
        return m_position;
    }
    void SetPosition(Vector3 position)
    {
        m_position = position;
    }
    
    int GetPuissance() const
    {
        return m_puissance;
    }
    void SetPuissance(int puissance)
    {
        m_puissance = puissance;
    }
};

bool CanSeeLight(const Vector3& point, const Light& light, const vector<Sphere>& scene)
{
    const Vector3 dirLampe = (light.GetPosition() - point).Normalize();
    //    const Vector3 dirCam = (ecran.GetPosition() - point).Normalize();
    const double distPL = GetDistance(point, light.GetPosition());
    
    for (const Sphere& sphere : scene)
    {
        
        if (EMaterialType::LightType == sphere.GetMaterial().m_materialType)
        {
            continue;
        }
        
        Intersection result;
        
        //        const Rayon rayon = Rayon((point + (dirCam * .01)), dirCam);
        const Rayon rayon = Rayon((point + (dirLampe * .5)), dirLampe);
        //        const Rayon rayon = Rayon(point, dirLampe);
        Intersect(rayon, sphere, result);
        
        if (result.intersect)
        {
            const double distPI = GetDistance(point, result.point);
            
            // Si l'objet est devant la lumière return false.
            if (distPI <= distPL)
            {
                return false;
            }
        }
    }
    
    // Si l'objet est derrière la lumière return true.
    return true;
}

void SetLightning(const Vector3& point, const int index, const Light& light,  vector<Color>& image)
{
    const double puissance = light.GetPuissance() * (1 / (abs((light.GetPosition().GetX() - point.GetX()) + (light.GetPosition().GetY() - point.GetY()) + (light.GetPosition().GetZ() - point.GetZ()))));
    
    image[index].SetR(image[index].GetR() * puissance);
    image[index].SetG(image[index].GetG() * puissance);
    image[index].SetB(image[index].GetB() * puissance);
}
