//
//  Ray.hpp
//  Synthese2
//
//  Created by Raphaël Daumas on 29/05/2019.
//  Copyright © 2019 Marsgames. All rights reserved.
//

#pragma once

#include <Vector3.hpp>

class Ray {
    Vector3 m_origin, m_dir;
    
public:
    Ray(Vector3 origin, Vector3 direction) :
    m_origin{origin},
    m_dir{direction.Normalize()}
    {};
    
    inline Vector3 GetOrigin() const
    {
        return m_origin;
    };
    inline Vector3 GetDirection() const
    {
        return m_dir;
    };
};
