//
//  Light.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 30/05/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#pragma once

#include <Color.hpp>
#include <iostream>
#include <Material.hpp>
#include <Sphere.hpp>
#include <Sphere.hpp>
#include <Vector3.hpp>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

class Light {
    Vector3 m_position;
    double m_power;
    Color m_color;
    Material m_material;
    
    
    
public:
    Light() = delete;
    
    Light(const Vector3& position, const double power):
    m_position{position},
    m_power{power},
    m_material{MaterialList::BlancMat},
    m_color{Color{1, 1, 1}}
    {};
    
    Light(const Vector3& position, const double power, const Material material):
    m_position{position},
    m_power{power},
    m_color{Color(1)},
    m_material{material}
    {};
    
    Vector3 GetPosition() const;
    double GetPower() const;
//    Color GetColor() const;
    Material GetMaterial() const;
    
    
//    static Color GetLightning(const Light& light, const Color& color, const double distance, Vector3 normal);
    static Color GetLighting(const Light& light, const Intersection& intersection, const float distanceToAdd = 0);
};
