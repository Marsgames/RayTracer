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
    Vector3 m_origin, m_direction;
    float m_focal;
    
public:
    Camera(const Vector3 origin, const int width, const int height, const Vector3 direction, float focal)
    {
        m_origin = origin;
        m_height = height;
        m_width = width;
//        m_direction = Normalize(direction);
        m_direction = direction.Normalize();
        if (focal < 0)
        {
            throw "Focal cannot be less than 0 !";
        }
        else
        {
            m_focal = focal;
        }
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
        return m_origin;
    }
    
    Vector3 GetDirection() const
    {
        return m_direction;
    }
    
    Vector3 GetFocalDirection(const Vector3& toThatPoint) const
    {
        const Vector3 startPoint = m_origin + Vector3(toThatPoint.GetX(), toThatPoint.GetY(), m_origin.GetZ());
        const Vector3 focalDirection = Negate(m_direction * m_focal);
        const Vector3 focalStart = m_origin + focalDirection;
        
        return (startPoint - focalStart).Normalize();
    }
};
