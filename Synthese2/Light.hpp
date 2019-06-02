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
#include <Vector3.hpp>

using std::cout;
using std::endl;

class Light {
    Vector3 m_position;
    double m_power;
    Color m_color;
    
public:
    Light(const Vector3& position, const double power):
    m_position{position},
    m_power{power},
    m_color{Color{255, 255, 255}}
    {};
    
    Light(const Vector3& position, const double power, const Color& color):
    m_position{position},
    m_power{power},
    m_color{color}
    {};
    
    Vector3 GetPosition() const;
    double GetPower() const;
//    Color GetColor() const;
    
    static Color GetLightning(const Light& light, const Color& color, const double distance);    
};
