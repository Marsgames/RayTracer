//
//  Rayon.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 08/10/2018.
//  Copyright © 2018 Marsgames. All rights reserved.
//

#pragma once

#include <Vector3.hpp>

class Rayon
{
private:
    Vector3 m_origin, m_direction;
public:
    Rayon(const Vector3& origin, Vector3& direction)
    {
        m_origin = origin;
//        m_direction = Normalize(direction);
        m_direction = direction.Normalize();
    };
    
    const Vector3& GetOrigin() const
    {
        return m_origin;
    }
    
    const Vector3& GetDirection() const
    {
        return m_direction;
    }
};
