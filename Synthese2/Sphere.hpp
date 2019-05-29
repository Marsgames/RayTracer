//
//  Sphere.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 29/05/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#pragma once

#include <Color.hpp>
#include <Ray.hpp>
#include <Vector3.hpp>

struct Intersection {
    bool intersect;
    double distance;
    Vector3 pointCoordonate;
};

class Sphere
{
    Vector3 m_center;
    int m_rayon;
    Color m_color;
    
public:
    Sphere(Vector3 position, int rayon, Color color) :
    m_center{position},
    m_rayon{rayon},
    m_color{color}
    {}
    
    Sphere(Vector3 position, int rayon) :
    m_center{position},
    m_rayon{rayon}
    {
        m_color = Color{255, 0, 0};
    }
    
    inline Vector3 GetCenter() const;
    double GetPositionX() const;
    double GetPositionY() const;
    double GetPositionZ() const;
    
    inline int GetRayon() const;
    
    inline Color GetColor() const;
    int GetColorR() const;
    int GetColorG() const;
    int GetColorB() const;
    
    static Intersection IntersectRaySphere(Ray ray, Sphere sphere);
    
};
