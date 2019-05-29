//
//  Pixel.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 29/05/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#pragma once

#include <Vector3.hpp>
#include <Color.hpp>

class Pixel {
    Vector3 m_position;
    Color m_color;
    
public:
    Pixel(Vector3 position, Color color):
    m_position{position},
    m_color{color}
    {};
    
    inline Vector3 GetPosition() const;
    double GetPositionX() const;
    double GetPositionY() const;
    double GetPositionZ() const;
    
    inline Color GetColor() const;
    int GetColorR() const;
    int GetColorG() const;
    int GetColorB() const;
    
};
