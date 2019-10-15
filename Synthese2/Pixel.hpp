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
    Vector3 m_position = Vector3{0, 0, 0};
    Color m_color = Color{0, 0, 0};
    
public:
    int index;
    
//    Pixel() {};
    Pixel() = delete;
    
    Pixel(const Vector3& position, const Color& color, const int index):
    m_position{position},
    m_color{color},
    index{index}
    {};
    
    Vector3 GetPosition() const;
    double GetPositionX() const;
    double GetPositionY() const;
    double GetPositionZ() const;
    
    Color GetColor() const;
    double GetColorR() const;
    double GetColorG() const;
    double GetColorB() const;
    
    void SetColor(const Color& color);
    
};
