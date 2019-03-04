//
//  Camera.h
//  Synthese2
//
//  Created by Raphaël Daumas on 08/10/2018.
//  Copyright © 2018 Marsgames. All rights reserved.
//

#pragma once

#include "Vector3.hpp"

class Camera
{
private:
    int m_height, m_width;
    Vector3 m_position, m_direction;
    
public:
    Camera(const Vector3 position, const int width, const int height, const Vector3 direction)
    {
        m_position = position;
        m_height = height;
        m_width = width;
        m_direction = direction;
    };
    
    int GetHeight() const
    {
        return m_height;
    }
    
    int GetWidth() const
    {
        return m_width;
    }
    
    Vector3 GetPosition() const
    {
        return m_position;
    }
    
    Vector3 GetDirection() const
    {
        return m_direction;
    }
    
};
