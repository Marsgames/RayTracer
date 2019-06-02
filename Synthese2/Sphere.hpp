//
//  Sphere.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 29/05/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#pragma once

#include <Color.hpp>
#include <Light.hpp>
#include <Ray.hpp>
#include <string>
#include <Vector3.hpp>
#include <vector>

using std::vector;
using std::string;

struct Intersection {
    bool intersect = false;
    double distance = -1;
    Vector3 pointCoordonate = Vector3{0, 0, 0};
    int nbIntersect = 0;
    
    Intersection() {};
    
    Intersection(bool theIntersect, double theDistance, Vector3 thePointCoordonate):
    intersect{theIntersect},
    distance{theDistance},
    pointCoordonate{thePointCoordonate}
    {};
    
    void PrintSphereState() const;
};

class Sphere
{
    Vector3 m_center;
    int m_rayon;
    Color m_color;
    string m_name = "";
    
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
    
    Sphere(Vector3 position, int rayon, Color color, string name) :
    m_center{position},
    m_rayon{rayon},
    m_color{color},
    m_name{name}
    {}
    
    Vector3 GetCenter() const;
    void SetCenter(Vector3 position);
    double GetPositionX() const;
    double GetPositionY() const;
    double GetPositionZ() const;
    
    int GetRayon() const;
    
    Color GetColor() const;
    int GetColorR() const;
    int GetColorG() const;
    int GetColorB() const;
    
    static Intersection IntersectRaySphere(Ray ray, Sphere sphere);
    static bool CanSeeLight(Vector3 point, Light light, vector<Sphere> spheres);
    
};
