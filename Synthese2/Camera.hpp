//
//  Camera.h
//  Synthese2
//
//  Created by Raphaël Daumas on 08/10/2018.
//  Copyright © 2018 Marsgames. All rights reserved.
//

#pragma once

#include <iostream>
#include <math.h>
#include <Pixel.hpp>
#include <Vector3.hpp>
#include <vector>

using std::vector;

class Camera
{
private:
    int m_height, m_width;
    Vector3 m_origin, m_direction;
    float m_focal;
    vector<Pixel> m_image;
    
    void InitImage();
    void ResetImagePosition();

    
public:
    inline Camera(const Vector3& origin, const int width, const int height, Vector3& direction, float focal) :
    m_origin{origin},
    m_height{height},
    m_width{width},
    m_direction{direction.Normalize()}
    {
        if (focal < 0)
        {
            throw "Focal cannot be less than 0 !";
        }
        else
        {
            m_focal = focal;
        }
        
        InitImage();
    };
    
    inline int GetHeight() const
    {
        return m_height;
    }
    
    inline int GetWidth() const
    {
        return m_width;
    }
    
    inline Vector3 GetPosition() const
    {
        return m_origin;
    }
    inline void SetPosition(const Vector3& position)
    {
        if (position == m_origin)
        {
            return;
        }
        
        m_origin = position;
        
        ResetImagePosition();
    }
    
    inline Vector3 GetDirection() const
    {
        return m_direction;
    }
    inline void SetDirection(Vector3& direction)
    {
        m_direction = direction.Normalize();
        InitImage();
    }
    
    Vector3 GetFocalDirection(const Vector3& toThatPoint) const;
    
    inline vector<Pixel>& GetImage()
    {
        return m_image;
    }
    
    void ResetImage()
    {
        m_image.clear();
    }
};
