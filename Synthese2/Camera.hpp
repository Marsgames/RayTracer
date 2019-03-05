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
    float m_focal;
    
public:
    Camera(const Vector3 position, const int width, const int height, const Vector3 direction, float focal)
    {
        m_position = position;
        m_height = height;
        m_width = width;
        m_direction = direction;
        
//        static_assert(focal < 0., "Focal cannot be less than 0 !");
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
        return m_position;
    }
    
    Vector3 GetDirection() const
    {
        return m_direction;
    }
    
//    float GetFocal() const
//    {
//        return m_focal;
//    }
    
    Vector3 GetFocalDirection(const Vector3& toThatPoint) const
    {
        const Vector3 startPoint = m_position + Vector3(toThatPoint.GetX(), toThatPoint.GetY(), m_position.GetZ());
        const Vector3 focalDirection = Negate(m_direction * m_focal);
        const Vector3 focalStart = m_position + focalDirection;
        return Normalize(startPoint - focalStart);
    }
};
