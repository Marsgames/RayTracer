//
//  Pixel.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 30/03/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#pragma once

#include <Color.hpp>
#include <Vector3.hpp>

class Pixel {
    Vector3 m_position;
    Color m_color;
    
public:
    Pixel(const Vector3& position, const Color& color)
    {
        m_position = position;
        m_color = color;
    }
    
    Vector3 GetPosition() const
    {
        return m_position;
    }
    void SetPosition(const Vector3& position)
    {
        m_position = position;
    }
    
    Color GetColor() const
    {
        return m_color;
    }
    void SetColor(const Color& color)
    {
        m_color = color;
    }
};
