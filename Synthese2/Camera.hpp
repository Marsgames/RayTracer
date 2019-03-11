//
//  Camera.h
//  Synthese2
//
//  Created by Raphaël Daumas on 08/10/2018.
//  Copyright © 2018 Marsgames. All rights reserved.
//

#pragma once

#include <math.h>
#include <Vector3.hpp>

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
    void SetPosition(Vector3 position)
    {
        m_origin = position;
    }
    
    Vector3 GetDirection() const
    {
        return m_direction;
    }
    void SetDirection(Vector3 direction)
    {
        m_direction = direction.Normalize();
    }
    
    Vector3 GetFocalDirection(const Vector3& toThatPoint) const
    {
        const Vector3 startPoint = m_origin + Vector3(toThatPoint.GetX(), toThatPoint.GetY(), m_origin.GetZ());
        const Vector3 focalDirection = Negate(m_direction * m_focal);
        const Vector3 focalStart = m_origin + focalDirection;
        
        return (startPoint - focalStart).Normalize();
    }
};

Vector3 MoveCameraOnCircle(const Vector3& circleOrigin, const double rayon, Camera& cam, const double index)
{
    Vector3 newPosition = Vector3((circleOrigin.GetX() + rayon * cos(index)), circleOrigin.GetY(), (circleOrigin.GetZ() + rayon * sin(index)));
    return newPosition;
}


double fDeX(const double petitX, const Vector3& circleOrigin, const float rayon)
{
    //  sqrt(r²-(x-xO)²)+yO
    return sqrt((rayon * rayon) - ((petitX - circleOrigin.GetX()) * (petitX - circleOrigin.GetX()))) + circleOrigin.GetZ();
}
